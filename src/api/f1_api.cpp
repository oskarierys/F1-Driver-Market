#include "f1_api.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <spdlog/spdlog.h>

F1Api::F1Api(const std::string& apiBaseUrl) 
    : m_client(web::uri(utility::conversions::to_string_t(apiBaseUrl))), m_apiKey("api_key") {}

std::vector<DriverPtr> F1Api::fetchDrivers()
{
    std::vector<DriverPtr> drivers;

    try
    {
        auto response = sendRequest("/drivers");
        auto json = parseResponse(response);

        if (json.contains("drivers") && json["drivers"].is_array())
        {
            for (const auto& driverJson : json["drivers"])
            {
                drivers.push_back(jsonToDriver(driverJson));
            }
        }
        else 
        {
            spdlog::error("Invalid response format for drivers: {}", json.dump());
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error in fetching drivers: {}", e.what());
    }
    
    return drivers;
}

std::optional<DriverPtr> F1Api::fetchDriverById(int driverId)
{
    try
    {
        auto response = sendRequest("/drivers/" + std::to_string(driverId));
        auto json = parseResponse(response);

        if (json.contains("driver"))
        {
            return jsonToDriver(json["driver"]);
        }
        else 
        {
            spdlog::error("Invalid response format for driver");
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error in fetching driver by ID: {}", driverId, e.what());
    }
    
    return std::nullopt;
}

std::vector<DriverPtr> F1Api::fetchDriversByNationality(const std::string& nationality)
{
    std::vector<DriverPtr> drivers;

    try
    {
        auto response = sendRequest("/drivers?nationality = " + nationality);
        auto json = parseResponse(response);

        if (json.contains("drivers") && json["drivers"].is_array())
        {
            for (const auto& driverJson : json["drivers"])
            {
                drivers.push_back(jsonToDriver(driverJson));
            }
        }
        else 
        {
            spdlog::error("Invalid response format for drivers by nationality");
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error in fetching drivers by nationality");
    }

    return drivers;
}

std::vector<TeamPtr> F1Api::fetchTeams()
{
    std::vector<TeamPtr> teams;

    try
    {
        auto response = sendRequest("/team");
        auto json = parseResponse(response);

        if (json.contains("teams") && json["teams"].is_array())
        {
            for (const auto& teamJson : json["teams"])
            {
                teams.push_back(jsonToTeam(teamJson));
            }
        }
        else
        {
            spdlog::error("Invalid response format for teams");
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error in fetching teams");
    }

    return teams;
}

std::optional<TeamPtr> F1Api::fetchTeamById(int teamId)
{
    try
    {
        auto response = sendRequest("/teams/" + std::to_string(teamId));
        auto json = parseResponse(response);

        if (json.contains("team"))
        {
            return jsonToTeam(json["team"]);
        }
        else 
        {
            spdlog::error("Invalid response format for team by ID");
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error in fetching team by ID: {}", e.what());
    }
    
    return std::nullopt;
}

std::vector<RaceResultPtr> F1Api::fetchRaceResults(int season)
{
    std::vector<RaceResultPtr> results;

    try
    {
        auto response = sendRequest("/results?season=" + std::to_string(season));
        auto json = parseResponse(response);

        if (json.contains("results") && json["results"].is_array())
        {
            for (const auto& resultJson : json["results"])
            {
                results.push_back(jsonToRaceResult(resultJson));
            }
        }
        else 
        {
            spdlog::error("Invalid response format for race results");
        }
    }
    catch(const std::exception& e)
    {
        spdlog::error("Error in fetching race results for season {}: {}", season, e.what());
    }
}