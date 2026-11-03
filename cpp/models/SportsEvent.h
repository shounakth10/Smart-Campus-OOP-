#pragma once

#include "Event.h"

using namespace std;

class SportsEvent : public Event {
private:
    string sport;
    string level;

public:
    SportsEvent();
    SportsEvent(int eventId, const string& eventName, const string& description,
                const string& date, const string& startTime, const string& endTime,
                int facilityId, int organizerId, int maxParticipants,
                const string& sport, const string& level);
    virtual ~SportsEvent() override = default;

    string getSport() const;
    string getLevel() const;

    void setSport(const string& sport);
    void setLevel(const string& level);

    virtual void display() const override;
    virtual string getType() const override;
};
