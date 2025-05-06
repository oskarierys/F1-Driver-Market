#pragma once

#include <vector>
#include <memory>
#include <optional>
#include <utility>
#include "../models/team.hpp"
#include "../database/database_manager.hpp"
#include "../api/f1_api.hpp"
#include "../models/driver.hpp"

class TeamService
{
public:
    TeamService(std::shared_ptr<DatabaseManager> dbManager, std::shared_ptr<F1Api> api);

    // Team methods
    bool addTeam(TeamPtr team);
    bool updateTeam(const TeamPtr& team);
    bool deleteTeam(int id);
    std::optional<TeamPtr> getTeam(int id);
    std::vector<TeamPtr> getAllTeams();

    // Data synchronization methods
    int SynchTeamsFromApi();

    // Analysis methods
    std::vector<std::pair<DriverPtr, double>> getTeamDriversWithContractValue(int teamId);
    double calculateTeamTotalDriverExpenditure(int teamId);
    std::vector<std::pair<TeamPtr, double>> getTeamsRankedByPerformance(int season);
    std::vector<DriverPtr> suggestDriversForTeam(int teamId, int maxBudget);

private:
    std::shared_ptr<DatabaseManager> m_dbManager;
    std::shared_ptr<F1Api> m_api;

    // Helper methods
    double calculateTeamPerformanceScore(int teamId, int season);
    double calculateTeamDriverCompatibility(int teamId, int driverId);
}; 