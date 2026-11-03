#pragma once

#include "Event.h"

using namespace std;

class CulturalEvent : public Event {
private:
    string culturalCategory;

public:
    CulturalEvent();
    CulturalEvent(int eventId, const string& eventName, const string& description,
                  const string& date, const string& startTime, const string& endTime,
                  int facilityId, int organizerId, int maxParticipants,
                  const string& culturalCategory);
    virtual ~CulturalEvent() override = default;

    string getCulturalCategory() const;
    void setCulturalCategory(const string& category);

    virtual void display() const override;
    virtual string getType() const override;
};
