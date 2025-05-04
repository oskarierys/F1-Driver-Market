#pragma once 

#include <vector>
#include <memory>
#include <optional>
#include "../models/driver.hpp"
#include "../database/database_manager.hpp"
#include "../api/f1_api.hpp"

class DriverService
{
public:
    DriverService(std::shared_ptr<DatabaseManager> dbManager, std::shared_ptr<F1Api> api);

    // Driver methods
    bool addDriver(DriverPtr driver);
    bool updateDriver(const DriverPtr& driver);
    bool deleteDriver(int id);
    std::optional<DriverPtr> getDriver(int id);
    std::vector<DriverPtr> getAllDrivers();
    std::vector<DriverPtr> getDriversByStatus(Driver::Status status);
    std::vector<DriverPtr> getDriversByTeam(int teamId);

    // Data synchronization methods
    int SynchDriversFromApi();

    // Analysis methods
    double calculateDriverMarketValue(int driverId);
    std::vector<std::pair<DriverPtr, double>> getDriversRankedByPerformance();
    std::vector<DriverPtr> getPotentialFreeAgents(int season);

private:
    std::shared_ptr<DatabaseManager> m_dbManager;
    std::shared_ptr<F1Api> m_api;

    // Helper methods
    double calculateAgeFactorForValue(int age);
    double calculatePerformanceFactorForValue(int points, int wins, int podiums, int polePositions);
};