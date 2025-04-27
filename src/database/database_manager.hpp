#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <sqlite3.h>
#include "../models/driver.hpp"
#include "../models/team.hpp"
#include "../models/contract.hpp"
#include "../models/race_result.hpp"

class DatabaseManager
{
public: 
    DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    // Initializing database
    bool initialize();

    // Driver methods
    bool addDriver(DriverPtr driver);
    bool updateDriver(const DriverPtr& driver);
    bool deleteDriver(int id);
    std::optional<DriverPtr> getDriver(int id);
    std::vector<DriverPtr> getAllDrivers();
    std::vector<DriverPtr> getDriversByStatus(Driver::Status status);
    std::vector<DriverPtr> getDriversByTeam(int teamId);

    // Team methods
    bool addTeam(TeamPtr team);
    bool updateTeam(const TeamPtr& team);
    bool deleteTeam(int id);
    std::optional<TeamPtr> getTeam(int id);
    std::vector<TeamPtr> getAllTeams();

    // Contract methods
    bool addContract(ContractPtr contract);
    bool updateContract(const ContractPtr& contract);
    bool deleteContract(int id);
    std::optional<ContractPtr> getContract(int id);
    std::vector<ContractPtr> getAllContracts();
    std::vector<ContractPtr> getActiveContracts();
    std::vector<ContractPtr> getContractsForDriver(int driverId);
    std::vector<ContractPtr> getContractsForTeam(int teamId);
    std::vector<ContractPtr> getExpiringContracts();

    // Race result methods
    bool addRaceResult(RaceResultPtr result);
    bool updateRaceResult(const RaceResultPtr& result);
    bool deleteRaceResult(int id);
    std::optional<RaceResultPtr> getRaceResult(int id);
    std::vector<RaceResultPtr> getAllRaceResults();
    std::vector<RaceResultPtr> getRaceResultsByDriver(int driverId);
    std::vector<RaceResultPtr> getRaceResultsByTeam(int teamId);
    std::vector<RaceResultPtr> getRaceResultsBySeason(int season);

private:
    sqlite3* m_db;
    std::string m_dbPath;

    // Helper methods
    bool executeQuery(const std::string& query);
    bool createTablesIfNotExists();
};

