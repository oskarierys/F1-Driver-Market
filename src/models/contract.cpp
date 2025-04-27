#include "contract.hpp"
#include <chrono>

Contract::Contract(int id,
                   int driverId,
                   int teamId,
                   std::chrono::year startDate,
                   std::chrono::year endDate,
                   double yearlySalary,
                   double performanceBonus)
    : m_id(id), m_driverId(driverId), m_teamId(teamId), m_startDate(startDate),
      m_endDate(endDate), m_yearlySalary(yearlySalary), m_performanceBonus(performanceBonus) {}
      
Contract::Contract(int driverId,
                   int teamId,
                   std::chrono::year startDate,
                   std::chrono::year endDate,
                   double yearlySalary,
                   double performanceBonus)
    : m_driverId(driverId), m_teamId(teamId), m_startDate(startDate),
      m_endDate(endDate), m_yearlySalary(yearlySalary), m_performanceBonus(performanceBonus) {}

std::string Contract::getRoleString() const
{
    switch (m_role)
    {
        case Role::MAIN_DRIVER: return "Main Driver";
        case Role::SECOND_DRIVER: return "Second Driver";
        case Role::RESERVE_DRIVER: return "Reserve Driver";
        case Role::TEST_DRIVER: return "Test Driver";
        default: return "Unknown Role";
    }
}

int Contract::getContractDuration() const
{
    return static_cast<int>(m_endDate) - static_cast<int>(m_startDate) + 1;
}

double Contract::getTotalValue() const
{
    return (m_yearlySalary * getContractDuration()) + m_performanceBonus;
}

bool Contract::isActive() const
{
    auto now = std::chrono::system_clock::now();
    auto currentYear = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now)).year();

    return currentYear >= m_startDate && currentYear <= m_endDate;
}

bool Contract::isExpiring() const
{
    auto now = std::chrono::system_clock::now();
    auto currentYear = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now)).year();

    return currentYear == m_endDate;
}