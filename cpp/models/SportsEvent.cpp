#include "SportsEvent.h"

using namespace std;

SportsEvent::SportsEvent()
    : Event(), sport(""), level("") {}

SportsEvent::SportsEvent(int eventId, const string& eventName, const string& description,
                         const string& date, const string& startTime, const string& endTime,
                         int facilityId, int organizerId, int maxParticipants,
                         const string& sport, const string& level)
    : Event(eventId, eventName, description, date, startTime, endTime, facilityId, organizerId, maxParticipants),
      sport(sport), level(level) {}

string SportsEvent::getSport() const { return sport; }
string SportsEvent::getLevel() const { return level; }

void SportsEvent::setSport(const string& sport) { this->sport = sport; }
void SportsEvent::setLevel(const string& level) { this->level = level; }

void SportsEvent::display() const {
    Event::display();
    cout << "Sport: " << sport << endl;
    cout << "Tournament Level: " << level << endl;
}

string SportsEvent::getType() const {
    return "Sports Event";
}
