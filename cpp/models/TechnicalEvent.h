#pragma once

#include "Event.h"

using namespace std;

class TechnicalEvent : public Event {
private:
    string technology;
    string competitionType;

public:
    TechnicalEvent();
    TechnicalEvent(int eventId, const string& eventName, const string& description,
                   const string& date, const string& startTime, const string& endTime,
                   int facilityId, int organizerId, int maxParticipants,
                   const string& technology, const string& competitionType);
    virtual ~TechnicalEvent() override = default;

    string getTechnology() const;
    string getCompetitionType() const;

    void setTechnology(const string& tech);
    void setCompetitionType(const string& compType);

    virtual void display() const override;
    virtual string getType() const override;
};
