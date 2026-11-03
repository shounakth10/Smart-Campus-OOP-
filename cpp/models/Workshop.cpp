#include "Workshop.h"

using namespace std;

Workshop::Workshop()
    : Event(), topic(""), instructor("") {}

Workshop::Workshop(int eventId, const string& eventName, const string& description,
                   const string& date, const string& startTime, const string& endTime,
                   int facilityId, int organizerId, int maxParticipants,
                   const string& topic, const string& instructor)
    : Event(eventId, eventName, description, date, startTime, endTime, facilityId, organizerId, maxParticipants),
      topic(topic), instructor(instructor) {}

string Workshop::getTopic() const { return topic; }
string Workshop::getInstructor() const { return instructor; }

void Workshop::setTopic(const string& topic) { this->topic = topic; }
void Workshop::setInstructor(const string& instructor) { this->instructor = instructor; }

void Workshop::display() const {
    Event::display();
    cout << "Topic: " << topic << endl;
    cout << "Instructor: " << instructor << endl;
}

string Workshop::getType() const {
    return "Workshop";
}
