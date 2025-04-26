#pragma once

#include <string>
#include <memory>
#include <chrono>
#include <optional>

class RaceResult
{
public:
    RaceResult(int id,
              int driverId,
              int teamId,
              const std::string& raceName,
              int season,
              std::chrono::system_clock::time_point raceDate,
              int position,
              int points,
              bool fastestLap,
              int gridPosition);


    RaceResult(int driverId,
              int teamId,
              const std::string& raceName,
              int season,
              std::chrono::system_clock::time_point raceDate,
              int position,
              int points,
              bool fastestLap,
              int gridPosition);

    // Getters
    int getId() const { return m_id; }
    int getDriverId() const { return m_driverId; }
    int getTeamId() const { return m_teamId; }
    const std::string& getRaceName() const { return m_raceName; }
    int getSeason() const { return m_season; }
    std::chrono::system_clock::time_point getRaceDate() const { return m_raceDate; }
    int getPosition() const { return m_position; }
    int getPoints() const { return m_points; }
    bool hasFastestLap() const { return m_fastestLap; }
    int getGridPosition() const { return m_gridPosition; }

    // Setters
    void setId(int id) { m_id = id; }
    void setDriverId(int driverId) { m_driverId = driverId; }
    void setTeamId(int teamId) { m_teamId = teamId; }
    void setRaceName(const std::string& raceName) { m_raceName = raceName; }
    void setSeason(int season) { m_season = season; }
    void setRaceDate(std::chrono::system_clock::time_point date) { m_raceDate = date; }
    void setPosition(int position) { m_position = position; }
    void setPoints(int points) { m_points = points; }
    void setFastestLap(bool fastestLap) { m_fastestLap = fastestLap; }
    void setGridPosition(int gridPosition) { m_gridPosition = gridPosition; }

    // Helper methods
    std::string getFormattedRaceDate() const;
    int getPositionGained() const;
    bool isPodium() const;
    bool isWin() const;
    bool isPointScoring() const;

private:
    int m_id = -1;
    int m_driverId;
    int m_teamId;
    std::string m_raceName;
    int m_season;
    std::chrono::system_clock::time_point m_raceDate;
    int m_position;
    int m_points;
    bool m_fastestLap;
    int m_gridPosition;
};

using RaceResultPtr = std::shared_ptr<RaceResult>;