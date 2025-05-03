#include "database_manager.hpp"
#include <iostream>
#include <sstream>
#include <chrono>

DatabaseManager::DatabaseManager(const std::string& dbPath) : m_dbPath(dbPath), m_db(nullptr) {}

DatabaseManager::~DatabaseManager()
{
    if (m_db) {
        sqlite3_close(m_db);
    }
}

bool DatabaseManager::initialize()
{
    int rc = sqlite3_open(m_dbPath.c_str(), &m_db);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_close(m_db);
        return false;
    }

    return createTablesIfNotExists();
}

bool DatabaseManager::createTablesIfNotExists()
{
    std::string createDriversTable = 
        "CREATE TABLE IF NOT EXISTS drivers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "date_of_birth INTEGER NOT NULL, "
        "nationality TEXT NOT NULL, "
        "career_points INTEGER NOT NULL, "
        "career_wins INTEGER NOT NULL, "
        "career_podiums INTEGER NOT NULL, "
        "career_pole_positions INTEGER NOT NULL, "
        "status INTEGER NOT NULL);";

        std::string createTeamsTable = 
        "CREATE TABLE IF NOT EXISTS teams ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "nationality TEXT NOT NULL, "
        "founded_year INTEGER NOT NULL, "
        "championships INTEGER NOT NULL, "
        "yearly_budget REAL NOT NULL, "
        "driver_budget REAL NOT NULL);";

        std::string createContractsTable = 
        "CREATE TABLE IF NOT EXISTS contracts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "driver_id INTEGER NOT NULL, "
        "team_id INTEGER NOT NULL, "
        "role INTEGER NOT NULL, "
        "start_year INTEGER NOT NULL, "
        "end_year INTEGER NOT NULL, "
        "yearly_salary REAL NOT NULL, "
        "performance_bonus REAL NOT NULL, "
        "FOREIGN KEY (driver_id) REFERENCES drivers (id), "
        "FOREIGN KEY (team_id) REFERENCES teams (id));";

        std::string createRaceResultsTable = 
        "CREATE TABLE IF NOT EXISTS race_results ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "driver_id INTEGER NOT NULL, "
        "team_id INTEGER NOT NULL, "
        "race_name TEXT NOT NULL, "
        "season INTEGER NOT NULL, "
        "race_date INTEGER NOT NULL, "
        "position INTEGER NOT NULL, "
        "points INTEGER NOT NULL, "
        "fastest_lap INTEGER NOT NULL, "
        "grid_position INTEGER NOT NULL, "
        "FOREIGN KEY (driver_id) REFERENCES drivers (id), "
        "FOREIGN KEY (team_id) REFERENCES teams (id));";

        return executeQuery(createDriversTable) && 
           executeQuery(createTeamsTable) && 
           executeQuery(createContractsTable) &&
           executeQuery(createRaceResultsTable);
}

bool DatabaseManager::executeQuery(const std::string& query)
{
    char* errMsg = nullptr;
    int rc = sqlite3_exec(m_db, query.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool DatabaseManager::addDriver(DriverPtr driver) {
    std::stringstream query;
    query << "INSERT INTO drivers (name, date_of_birth, nationality, career_points, "
          << "career_wins, career_podiums, career_pole_positions, status) "
          << "VALUES ('" << driver -> getName() << "', "
          << std::chrono::system_clock::to_time_t(driver -> getDateOfBirth()) << ", '"
          << driver -> getNationality() << "', "
          << driver -> getCareerPoints() << ", "
          << driver -> getCareerWins() << ", "
          << driver -> getCareerPodiums() << ", "
          << driver -> getCareerPolePositions() << ", "
          << static_cast<int>(driver -> getStatus()) << ");";
    
    if (!executeQuery(query.str())) {
        return false;
    }

    driver -> setId(sqlite3_last_insert_rowid(m_db));
    return true;
}

bool DatabaseManager::updateContract(const ContractPtr& contract)
{
    std::stringstream query;
    query << "UPDATE contracts SET "
          << "driver_id = " << contract -> getDriverId() << ", "
          << "team_id = " << contract -> getTeamId() << ", "
          << "role = " << static_cast<int>(contract -> getRole()) << ", "
          << "start_year = " << static_cast<int>(contract -> getStartDate()) << ", "
          << "end_year = " << static_cast<int>(contract -> getEndDate()) << ", "
          << "yearly_salary = " << contract -> getYearlySalary() << ", "
          << "performance_bonus = " << contract -> getPerformanceBonus()
          << " WHERE id = " << contract -> getId() << ";";
    
    return executeQuery(query.str());
}

bool DatabaseManager::deleteContract(int id) 
{
    std::stringstream query;
    query << "DELETE FROM contracts WHERE id = " << id << ";";
    return executeQuery(query.str());
}

bool DatabaseManager::deleteDriver(int id) 
{
    std::stringstream query;
    query << "DELETE FROM drivers WHERE id = " << id << ";";
    return executeQuery(query.str());
}

