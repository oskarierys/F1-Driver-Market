#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include <chrono>

class Driver
{
public:
    enum class Status
    {
        ACTIVE, 
        RESERVE,
        FREE_AGENT,
        RETIRED,
    };

    Driver(int id, 
            const std::string& name, 
            std::chrono::system_clock::time_point dateOfBirth, 
            const std::string& nationality, 
            int careerPoints, 
            int careerWins, 
            int careerPodiums, 
            int careerPolePositions, 
            Status status);
    
    // Constructot for a new driver
    Driver(const std::string& name, 
            std::chrono::system_clock::time_point dateOfBirth, 
            const std::string& nationality,
            int careerPoints = 0,
            int careerWins = 0,
            int careerPodiums = 0,
            int careerPolePositions = 0,
            Status status = Status::FREE_AGENT);

    // Getters
    int getId() const { return m_id; }
    const std::string& getName() const { return m_name; }
    std::chrono::system_clock::time_point getDateOfBirth() const { return m_dateOfBirth; }
    const std::string& getNationality() const { return m_nationality; }
    int getCareerPoints() const { return m_careerPoints; }
    int getCareerWins() const { return m_careerWins; }
    int getCareerPodiums() const { return m_careerPodiums; }
    int getCareerPolePositions() const { return m_careerPolePositions; }
    Status getStatus() const { return m_status; }

    // Setters
    void setName(const std::string& name) { m_name = name; }
    void setDateOfBirth(std::chrono::system_clock::time_point dateOfBirth) { m_dateOfBirth = dateOfBirth; }
    void setNationality(const std::string& nationality) { m_nationality = nationality; }
    void setCareerPoints(int careerPoints) { m_careerPoints = careerPoints; }
    void setCareerWins(int careerWins) { m_careerWins = careerWins; }
    void setCareerPodiums(int careerPodiums) { m_careerPodiums = careerPodiums; }
    void setCareerPolePositions(int careerPolePositions) { m_careerPolePositions = careerPolePositions; }
    void setStatus(Status status) { m_status = status; }

    // Helper methods
    std::string getFormattedDateOfBirth() const;
    std::string getStatusString() const;
    int getAge() const;
    double calculatePerformanceIndex() const;

private:
    int m_id = -1; // -1 means not saved to DB
    std::string m_name;
    std::chrono::system_clock::time_point m_dateOfBirth;
    std::string m_nationality;
    int m_careerPoints;
    int m_careerWins;
    int m_careerPodiums;
    int m_careerPolePositions;
    Status m_status;
};

using DriverPtr = std::shared_ptr<Driver>;