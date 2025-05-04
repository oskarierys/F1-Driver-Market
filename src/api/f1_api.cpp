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
        auto response = sendRequest("/drivers?nationality=" + nationality);
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

std::vector<RaceResultPtr> F1Api::fetchRaceResultsForDriver(int driverId, int season)
{
    std::vector<RaceResultPtr> results;

    try
    {
        auto response = sendRequest("/results?driver=" + std::to_string(driverId) + "&season=" + std::to_string(season));
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
            spdlog::error("Invalid response format for driver race results");
        }
    }
    catch (const std::exception& e)
    {
        spdlog::error("Error in fetching race results for driver {} in season {}: {}", driverId, season, e.what());
    }

    return results;
}

std::vector<RaceResultPtr> F1Api::fetchRaceResultsForTeam(int teamId, int season)
{
    std::vector<RaceResultPtr> results;

    try
    {
        auto response = sendRequest("/results?team=" + std::to_string(teamId) + "&season=" + std::to_string(season));
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
            spdlog::error("Invalid response format for team race results");
        }
    }
    catch (const std::exception& e)
    {
        spdlog::error("Error in fetching race results for team {} in season {}: {}", teamId, season, e.what());
    }

    return results;
}

web::http::http_response F1Api::sendRequest(const std::string& endpoint)
{
    web::http::http_request request(web::http::methods::GET);
    request.headers().add(utility::conversions::to_string_t("Authorization"), utility::conversions::to_string_t("Bearer ") + utility::conversions::to_string_t(m_apiKey));

    request.set_request_uri(utility::conversions::to_string_t(endpoint));
    return m_client.request(request).get();
}

nlohmann::json F1Api::parseResponse(const web::http::http_response& response)
{
    if (response.status_code() != web::http::status_codes::OK)
    {
        throw std::runtime_error("Failed to fetch data from API: " + std::to_string(response.status_code()));
    }

    auto jsonString = response.extract_string().get();
    return nlohmann::json::parse(utility::conversions::to_utf8string(jsonString));
}

DriverPtr F1Api::jsonToDriver(const nlohmann::json& json)
{
    int id = json["id"];
    std::string name = json["name"];

    std::tm tm = {};
    std::stringstream ss(json["dateOfBirth"].get<std::string>());
    ss >> std::get_time(&tm, "%Y-%m-%d");
    auto dateOfBirth = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    std::string nationality = json["nationality"];
    int careerPoints = json["careerPoints"];
    int careerWins = json["careerWins"];
    int careerPodiums = json["careerPodiums"];
    int careerPolePositions = json["careerPolePositions"];

    Driver::Status status;
    std::string statusStr = json["status"];
    if (statusStr == "active")
        status = Driver::Status::ACTIVE;
    else if (statusStr == "reserve")
        status = Driver::Status::RESERVE;
    else if (statusStr == "free_agent")
        status = Driver::Status::FREE_AGENT;
    else
        status = Driver::Status::RETIRED;

    return std::make_shared<Driver>(id, name, dateOfBirth, nationality, careerPoints, careerWins, careerPodiums, careerPolePositions, status);
}

TeamPtr F1Api::jsonToTeam(const nlohmann::json& json)
{
    int id = json["id"];
    std::string name = json["name"];
    std::string nationality = json["nationality"];
    int foundedYear = json["foundedYear"];
    int championships = json["championships"];
    double yearlyBudget = json["yearlyBudget"];
    double driverBudget = json["driverBudget"];

    return std::make_shared<Team>(id, name, nationality, foundedYear, championships, yearlyBudget, driverBudget);
}

RaceResultPtr F1Api::jsonToRaceResult(const nlohmann::json& json)
{
    int id = json["id"];
    int driverId = json["driverId"];
    int teamId = json["teamId"];
    std::string raceName = json["raceName"];
    int season = json["season"];
    
    std::tm tm = {};
    std::stringstream ss(json["raceDate"].get<std::string>());
    ss >> std::get_time(&tm, "%Y-%m-%d");
    auto raceDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    
    int position = json["position"];
    int points = json["points"];
    bool fastestLap = json["fastestLap"];
    int gridPosition = json["gridPosition"];
    
    return std::make_shared<RaceResult>(id, driverId, teamId, raceName, season, raceDate, position, points, fastestLap, gridPosition);
}