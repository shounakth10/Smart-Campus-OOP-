#pragma once

#include "Event.h"

using namespace std;

class Workshop : public Event {
private:
    string topic;
    string instructor;

public:
    Workshop();
    Workshop(int eventId, const string& eventName, const string& description,
             const string& date, const string& startTime, const string& endTime,
             int facilityId, int organizerId, int maxParticipants,
             const string& topic, const string& instructor);
    virtual ~Workshop() override = default;

    string getTopic() const;
    string getInstructor() const;

    void setTopic(const string& topic);
    void setInstructor(const string& instructor);

    virtual void display() const override;
    virtual string getType() const override;
};
