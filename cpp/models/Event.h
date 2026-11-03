#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "../utils/DateTimeUtils.h"

using namespace std;

class Event {
protected:
    int eventId;
    string eventName;
    string description;
    string date;
    string startTime;
    string endTime;
    int facilityId;
    int organizerId;
    int maxParticipants;
    vector<int> participantIds;

public:
    Event();
    Event(int eventId, const string& eventName, const string& description,
          const string& date, const string& startTime, const string& endTime,
          int facilityId, int organizerId, int maxParticipants);
    virtual ~Event() = default;

    int getEventId() const;
    string getEventName() const;
    string getDescription() const;
    string getDate() const;
    string getStartTime() const;
    string getEndTime() const;
    int getFacilityId() const;
    int getOrganizerId() const;
    int getMaxParticipants() const;
    int getParticipantCount() const;
    const vector<int>& getParticipantIds() const;

    void setEventName(const string& name);
    void setDescription(const string& desc);
    void setDate(const string& date);
    void setTime(const string& startTime, const string& endTime);
    void setFacilityId(int facilityId);
    void setOrganizerId(int organizerId);
    void setMaxParticipants(int maxParticipants);

    bool registerParticipant(int studentId);
    bool removeParticipant(int studentId);
    bool isParticipantRegistered(int studentId) const;
    bool isFull() const;

    virtual void display() const;
    virtual string getType() const;
};
