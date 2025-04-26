#include "driver.hpp"
#include <sstream>
#include <iomanip>
#include <chrono>

Driver::Driver(int id,
               const std::string& name, 
               std::chrono::system_clock::time_point dateOfBirth, 
               const std::string& nationality,
               int careerPoints,
               int careerWins,
               int careerPodiums,
               int careerPolePositions,
               Status status)
    : m_id(id), m_name(name), m_dateOfBirth(dateOfBirth), m_nationality(nationality),
      m_careerPoints(careerPoints), m_careerWins(careerWins), m_careerPodiums(careerPodiums),
      m_careerPolePositions(careerPolePositions), m_status(status) {}

Driver::Driver(const std::string& name, 
                std::chrono::system_clock::time_point dateOfBirth, 
                const std::string& nationality,
                int careerPoints,
                int careerWins,
                int careerPodiums,
                int careerPolePositions,
                Status status)
    : m_name(name), m_dateOfBirth(dateOfBirth), m_nationality(nationality),
      m_careerPoints(careerPoints), m_careerWins(careerWins), m_careerPodiums(careerPodiums),
      m_careerPolePositions(careerPolePositions), m_status(status) {}

std::string Driver::getFormattedDateOfBirth() const
{
    auto time = std::chrono::system_clock::to_time_t(m_dateOfBirth);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

int Driver::getAge() const
{
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::tm* currentTime = std::localtime(&timeT);

    auto birthTimeT = std::chrono::system_clock::to_time_t(m_dateOfBirth);
    std::tm* birthTime = std::localtime(&birthTimeT);

    int age = currentTime -> tm_year - birthTime -> tm_year;

    if (currentTime -> tm_mon < birthTime -> tm_mon || 
        (currentTime -> tm_mon == birthTime -> tm_mon && currentTime -> tm_mday < birthTime -> tm_mday)) 
    {
        age--;
    }

    return age;
}

std::string Driver::getStatusString() const
{
    switch (m_status)
    {
        case Status::ACTIVE: return "Active";
        case Status::RESERVE: return "Reserve";
        case Status::FREE_AGENT: return "Free Agent";
        case Status::RETIRED: return "Retired";
        default: return "Unknown";
    }
}

double Driver::calculatePerformanceIndex() const
{
    // Calculating driver performance index based on career statistics
    double index = m_careerPoints * 0.1;
    index += m_careerWins * 5;
    index += m_careerPodiums * 2.5;
    index += m_careerPolePositions * 2;

    // Adjusting index based on age
    int age = getAge();
    if (age < 24)
    {
        index *= (0.85 + (age - 20) * 0.07);
    }
    else if (age > 36)
    {
        index *= (1.0 - (age - 36) * 0.05);
    }

    return index;
}