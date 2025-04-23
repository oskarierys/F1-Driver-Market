#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>

class Team
{
public:
    Team(int id, 
        const std::string& name, 
        const std::string& nationality, 
        int foundedYear, 
        int championships, 
        double yearlyBudget,
        double driverBudget);

    Team(const std::string& name, 
        const std::string& nationality,
        int foundedYear,
        int championships = 0,
        double yearlyBudget = 0.0,
        double driverBudget = 0.0);

    // Getters
    int getId() const { return m_id; }
    const std::string& getName() const { return m_name; }
    const std::string& getNationality() const { return m_nationality; }
    int getFoundedYear() const { return m_foundedYear; }
    int getChampionships() const { return m_championships; }
    double getYearlyBudget() const { return m_yearlyBudget; }
    double getDriverBudget() const { return m_driverBudget; }

    // Setters
    void setName(const std::string& name) { m_name = name; }
    void setNationality(const std::string& nationality) { m_nationality = nationality; }
    void setFoundedYear(int year) { m_foundedYear = year; }
    void setChampionships(int championships) { m_championships = championships; }
    void setYearlyBudget(double budget) { m_yearlyBudget = budget; }
    void setDriverBudget(double budget) { m_driverBudget = budget; }

    // Other methods
    int getAge() const;
    double getDriverBudgetPercwentage() const;

private:
    int m_id = -1;
    std::string m_name;
    std::string m_nationality;  
    int m_foundedYear;
    int m_championships;
    double m_yearlyBudget;
    double m_driverBudget;
};

using TeamPtr = std::shared_ptr<Team>;