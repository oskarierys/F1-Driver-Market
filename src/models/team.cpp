#include "team.hpp"
#include <chrono>

Team::Team(int id,
            const std::string& name, 
            const std::string& nationality,
            int foundedYear,
            int championships,
            double yearlyBudget,
            double driverBudget)
    : m_id(id), m_name(name), m_nationality(nationality), m_foundedYear(foundedYear),
      m_championships(championships), m_yearlyBudget(yearlyBudget), m_driverBudget(driverBudget) {}

Team::Team(const std::string& name, 
            const std::string& nationality,
            int foundedYear,
            int championships,
            double yearlyBudget,
            double driverBudget)
    : m_name(name), m_nationality(nationality), m_foundedYear(foundedYear),
      m_championships(championships), m_yearlyBudget(yearlyBudget), m_driverBudget(driverBudget) {}

int Team::getAge() const
{
    auto now = std::chrono::system_clock::now();
    auto currentYear = std::chrono::year_month_day(std::chrono::floor<std::chrono::days>(now)).year();

    return static_cast<int>(currentYear) - m_foundedYear;
}

double Team::getDriverBudgetPercentage() const
{
    if (m_yearlyBudget <= 0.0)
    {
        return 0.0;
    }

    return (m_driverBudget / m_yearlyBudget) * 100.0;
}

