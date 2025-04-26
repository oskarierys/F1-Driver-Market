#pragma once

#include <string>
#include <vector>
#include "team.hpp"
#include "driver.hpp"
#include <optional>
#include <memory>
#include <chrono>

class Contract
{
public:
    enum class Role 
    {
        MAIN_DRIVER,
        SECOND_DRIVER,
        RESERVE_DRIVER,
        TEST_DRIVER,
    };

    Contract(int id,
            int driverId,
            int teamId,
            std::chrono::year startDate,
            std::chrono::year endDate,
            double yearlySalary,
            double performanceBonus);

    Contract(int driverId,
            int teamId,
            std::chrono::year startDate,
            std::chrono::year endDate,
            double yearlySalary,
            double performanceBonus);

    // Getters 
    int getId() const { return m_id; }
    int getDriverId() const { return m_driverId; }
    int getTeamId() const { return m_teamId; }
    Role getRole() const { return m_role; }
    std::chrono::year getStartDate() const { return m_startDate; }
    std::chrono::year getEndDate() const { return m_endDate; }
    double getYearlySalary() const { return m_yearlySalary; }
    double getPerformanceBonus() const { return m_performanceBonus; }

    // Setters
    void setId(int driverId) { m_id = driverId; }
    void setDriverId(int driverId) { m_driverId = driverId; }
    void setTeamId(int teamId) { m_teamId = teamId; }
    void setRole(Role role) { m_role = role; }
    void setStartDate(std::chrono::year startDate) { m_startDate = startDate; }
    void setEndDate(std::chrono::year endDate) { m_endDate = endDate; }
    void setYearlySalary(double yearlySalary) { m_yearlySalary = yearlySalary; }
    void setPerformanceBonus(double performanceBonus) { m_performanceBonus = performanceBonus; }

    // Helper methods
    std::string getRoleString() const;
    int getContractDuration() const;
    double getTotalValue() const;
    bool isActive() const;
    bool isExpiring() const;

private:
        int m_id = -1;
        int m_driverId;
        int m_teamId;
        std::chrono::year m_startDate;
        std::chrono::year m_endDate;
        double m_yearlySalary;
        double m_performanceBonus;
        Role m_role;
};

using ContractPtr = std::shared_ptr<Contract>;