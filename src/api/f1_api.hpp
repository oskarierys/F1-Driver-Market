#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cpprest/http_client.h>
#include <nlohmann/json.hpp>
#include "../models/driver.hpp"
#include "../models/team.hpp"
#include "../models/contract.hpp"
#include "../models/race_result.hpp"

class F1Api
{
public:
    F1Api(const std::string& apiBaseUrl);
    ~F1Api();

    // Driver methods
    std::vector<DriverPtr> fetchDrivers();
    std::optional<DriverPtr> fetchDriverById(int id);
    std::vector<DriverPtr> fetchDriversByNationality(const std::string& nationality);

    // Team methods
    std::vector<TeamPtr> fetchTeams();
    std::optional<TeamPtr> fetchTeamById(int id);

    // Race result methods
    std::vector<RaceResultPtr> fetchRaceResults(int season);
    std::vector<RaceResultPtr> fetchRaceResultsForDriver(int driverId, int season);
    std::vector<RaceResultPtr> fetchRaceResultsForTeam(int teamId, int season);

private:
    web::http::client::http_client m_client;
    std::string m_apiKey;

    // Helper methods
    web::http::http_response sendRequest(const std::string& endpoint);
    nlohmann::json parseResponse(const web::http::http_response& response);

    // Model conversion methods
    DriverPtr jsonToDriver(const nlohmann::json& json);
    TeamPtr jsonToTeam(const nlohmann::json& json);
    RaceResultPtr jsonToRaceResult(const nlohmann::json& json);
};