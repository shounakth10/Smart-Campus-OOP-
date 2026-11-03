#include "CulturalEvent.h"

using namespace std;

CulturalEvent::CulturalEvent()
    : Event(), culturalCategory("") {}

CulturalEvent::CulturalEvent(int eventId, const string& eventName, const string& description,
                             const string& date, const string& startTime, const string& endTime,
                             int facilityId, int organizerId, int maxParticipants,
                             const string& culturalCategory)
    : Event(eventId, eventName, description, date, startTime, endTime, facilityId, organizerId, maxParticipants),
      culturalCategory(culturalCategory) {}

string CulturalEvent::getCulturalCategory() const { return culturalCategory; }
void CulturalEvent::setCulturalCategory(const string& category) { this->culturalCategory = category; }

void CulturalEvent::display() const {
    Event::display();
    cout << "Cultural Category: " << culturalCategory << endl;
}

string CulturalEvent::getType() const {
    return "Cultural Event";
}
