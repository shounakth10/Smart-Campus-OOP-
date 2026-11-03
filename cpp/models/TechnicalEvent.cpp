#include "TechnicalEvent.h"

using namespace std;

TechnicalEvent::TechnicalEvent()
    : Event(), technology(""), competitionType("") {}

TechnicalEvent::TechnicalEvent(int eventId, const string& eventName, const string& description,
                               const string& date, const string& startTime, const string& endTime,
                               int facilityId, int organizerId, int maxParticipants,
                               const string& technology, const string& competitionType)
    : Event(eventId, eventName, description, date, startTime, endTime, facilityId, organizerId, maxParticipants),
      technology(technology), competitionType(competitionType) {}

string TechnicalEvent::getTechnology() const { return technology; }
string TechnicalEvent::getCompetitionType() const { return competitionType; }

void TechnicalEvent::setTechnology(const string& tech) { this->technology = tech; }
void TechnicalEvent::setCompetitionType(const string& compType) { this->competitionType = compType; }

void TechnicalEvent::display() const {
    Event::display();
    cout << "Technology Domain: " << technology << endl;
    cout << "Competition Type: " << competitionType << endl;
}

string TechnicalEvent::getType() const {
    return "Technical Event";
}
