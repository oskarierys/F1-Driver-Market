#include "race_result.hpp"
#include <sstream>
#include <iomanip>
#include <chrono>

RaceResult::RaceResult(int id,
                       int driverId,
                       int teamId,
                       const std::string& raceName,
                       int season,
                       std::chrono::system_clock::time_point raceDate,
                       int position,
                       int points,
                       bool fastestLap,
                       int gridPosition)
    : m_id(id), m_driverId(driverId), m_teamId(teamId), m_raceName(raceName),
      m_season(season), m_raceDate(raceDate), m_position(position), m_points(points),
      m_fastestLap(fastestLap), m_gridPosition(gridPosition) {}

RaceResult::RaceResult(int id,
                        int driverId,
                        int teamId,
                        const std::string& raceName,
                        int season,
                        std::chrono::system_clock::time_point raceDate,
                        int position,
                        int points,
                        bool fastestLap,
                        int gridPosition)
    : m_id(id), m_driverId(driverId), m_teamId(teamId), m_raceName(raceName),
      m_season(season), m_raceDate(raceDate), m_position(position), m_points(points),
      m_fastestLap(fastestLap), m_gridPosition(gridPosition) {}

std::string RaceResult::getFormattedRaceDate() const
{
    auto time = std::chrono::system_clock::to_time_t(m_raceDate);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int RaceResult::getPositionGained() const
{
    return m_gridPosition - m_position;
}

bool RaceResult::isPodium() const
{
    return m_position <= 3;
}

bool RaceResult::isWin() const
{
    return m_position == 1;
}

bool RaceResult::isPointScoring() const
{
    return m_points > 0;
}