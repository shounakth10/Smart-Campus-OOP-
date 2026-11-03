#include "Event.h"
#include <algorithm>

using namespace std;

Event::Event()
    : eventId(0), eventName(""), description(""), date(""), startTime("00:00"),
      endTime("00:00"), facilityId(0), organizerId(0), maxParticipants(0) {}

Event::Event(int eventId, const string& eventName, const string& description,
             const string& date, const string& startTime, const string& endTime,
             int facilityId, int organizerId, int maxParticipants)
    : eventId(eventId), eventName(eventName), description(description),
      date(date), startTime(startTime), endTime(endTime),
      facilityId(facilityId), organizerId(organizerId), maxParticipants(maxParticipants) {
    if (eventId <= 0) throw invalid_argument("Event ID must be positive.");
    if (eventName.empty()) throw invalid_argument("Event name cannot be empty.");
    if (date.empty()) throw invalid_argument("Event date cannot be empty.");
    if (facilityId <= 0) throw invalid_argument("Facility ID must be positive.");
    if (organizerId <= 0) throw invalid_argument("Organizer ID must be positive.");
    if (maxParticipants <= 0) throw invalid_argument("Max participants must be positive.");
    if (!DateTimeUtils::isValidTime(startTime) || !DateTimeUtils::isValidTime(endTime)) {
        throw invalid_argument("Invalid time format for Event.");
    }
    if (DateTimeUtils::timeToMinutes(endTime) <= DateTimeUtils::timeToMinutes(startTime)) {
        throw invalid_argument("Event end time must be strictly after start time.");
    }
}

int Event::getEventId() const { return eventId; }
string Event::getEventName() const { return eventName; }
string Event::getDescription() const { return description; }
string Event::getDate() const { return date; }
string Event::getStartTime() const { return startTime; }
string Event::getEndTime() const { return endTime; }
int Event::getFacilityId() const { return facilityId; }
int Event::getOrganizerId() const { return organizerId; }
int Event::getMaxParticipants() const { return maxParticipants; }
int Event::getParticipantCount() const { return static_cast<int>(participantIds.size()); }
const vector<int>& Event::getParticipantIds() const { return participantIds; }

void Event::setEventName(const string& name) {
    if (name.empty()) throw invalid_argument("Event name cannot be empty.");
    this->eventName = name;
}

void Event::setDescription(const string& desc) { this->description = desc; }
void Event::setDate(const string& date) {
    if (date.empty()) throw invalid_argument("Event date cannot be empty.");
    this->date = date;
}

void Event::setTime(const string& startTime, const string& endTime) {
    if (!DateTimeUtils::isValidTime(startTime) || !DateTimeUtils::isValidTime(endTime)) {
        throw invalid_argument("Invalid time format.");
    }
    if (DateTimeUtils::timeToMinutes(endTime) <= DateTimeUtils::timeToMinutes(startTime)) {
        throw invalid_argument("End time must be after start time.");
    }
    this->startTime = startTime;
    this->endTime = endTime;
}

void Event::setFacilityId(int facilityId) {
    if (facilityId <= 0) throw invalid_argument("Facility ID must be positive.");
    this->facilityId = facilityId;
}

void Event::setOrganizerId(int organizerId) {
    if (organizerId <= 0) throw invalid_argument("Organizer ID must be positive.");
    this->organizerId = organizerId;
}

void Event::setMaxParticipants(int maxParticipants) {
    if (maxParticipants <= 0) throw invalid_argument("Max participants must be positive.");
    this->maxParticipants = maxParticipants;
}

bool Event::registerParticipant(int studentId) {
    if (studentId <= 0) return false;
    if (isFull()) {
        cout << "[Event] Registration failed: Event '" << eventName << "' (ID " << eventId << ") is full!" << endl;
        return false;
    }
    if (isParticipantRegistered(studentId)) {
        cout << "[Event] Registration failed: Student ID " << studentId << " is already registered for Event ID " << eventId << "." << endl;
        return false;
    }
    participantIds.push_back(studentId);
    return true;
}

bool Event::removeParticipant(int studentId) {
    auto it = find(participantIds.begin(), participantIds.end(), studentId);
    if (it != participantIds.end()) {
        participantIds.erase(it);
        return true;
    }
    return false;
}

bool Event::isParticipantRegistered(int studentId) const {
    return find(participantIds.begin(), participantIds.end(), studentId) != participantIds.end();
}

bool Event::isFull() const {
    return static_cast<int>(participantIds.size()) >= maxParticipants;
}

void Event::display() const {
    cout << "Event ID: " << eventId << endl;
    cout << "Event Name: " << eventName << endl;
    cout << "Type: " << getType() << endl;
    cout << "Description: " << description << endl;
    cout << "Date: " << date << " (" << startTime << " - " << endTime << ")" << endl;
    cout << "Facility ID: " << facilityId << endl;
    cout << "Organizer ID: " << organizerId << endl;
    cout << "Participants: " << getParticipantCount() << "/" << maxParticipants << endl;
}

string Event::getType() const {
    return "Event";
}
