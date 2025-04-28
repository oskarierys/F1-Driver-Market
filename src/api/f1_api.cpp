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

