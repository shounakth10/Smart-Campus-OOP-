#include "EventManager.h"
#include "../utils/DateTimeUtils.h"
#include <iostream>
#include <algorithm>

using namespace std;

EventManager::EventManager() {}
EventManager::~EventManager() {}

bool EventManager::addEvent(unique_ptr<Event> event) {
    if (!event) return false;

    if (findEvent(event->getEventId()) != nullptr) {
        cout << "[EventManager] Conflict rejected: Event ID " << event->getEventId()
             << " already exists!" << endl;
        return false;
    }

    for (const auto& e : events) {
        if (e->getFacilityId() == event->getFacilityId() && e->getDate() == event->getDate()) {
            if (DateTimeUtils::isTimeOverlap(e->getStartTime(), e->getEndTime(),
                                             event->getStartTime(), event->getEndTime())) {
                cout << "[EventManager] Conflict rejected: Facility ID " << event->getFacilityId()
                     << " is already booked for Event '" << e->getEventName()
                     << "' on " << event->getDate() << " (" << event->getStartTime()
                     << " - " << event->getEndTime() << ")." << endl;
                return false;
            }
        }
    }

    cout << "[EventManager] Successfully added Event: '" << event->getEventName()
         << "' (ID " << event->getEventId() << ")" << endl;
    events.push_back(move(event));
    return true;
}

bool EventManager::removeEvent(int eventId) {
    auto it = remove_if(events.begin(), events.end(),
                        [eventId](const unique_ptr<Event>& e) { return e->getEventId() == eventId; });
    if (it != events.end()) {
        events.erase(it, events.end());
        cout << "[EventManager] Successfully removed Event ID " << eventId << endl;
        return true;
    }
    cout << "[EventManager] Remove failed: Event ID " << eventId << " not found." << endl;
    return false;
}

Event* EventManager::findEvent(int eventId) {
    for (auto& e : events) {
        if (e->getEventId() == eventId) return e.get();
    }
    return nullptr;
}

const Event* EventManager::findEvent(int eventId) const {
    for (const auto& e : events) {
        if (e->getEventId() == eventId) return e.get();
    }
    return nullptr;
}

bool EventManager::registerParticipant(int eventId, int studentId) {
    Event* e = findEvent(eventId);
    if (!e) {
        cout << "[EventManager] Registration failed: Event ID " << eventId << " not found." << endl;
        return false;
    }
    return e->registerParticipant(studentId);
}

bool EventManager::removeParticipant(int eventId, int studentId) {
    Event* e = findEvent(eventId);
    if (!e) {
        cout << "[EventManager] Participant removal failed: Event ID " << eventId << " not found." << endl;
        return false;
    }
    bool success = e->removeParticipant(studentId);
    if (success) {
        cout << "[EventManager] Removed Student ID " << studentId << " from Event ID " << eventId << endl;
    } else {
        cout << "[EventManager] Student ID " << studentId << " was not registered for Event ID " << eventId << endl;
    }
    return success;
}

vector<Event*> EventManager::getEventsByDate(const string& date) {
    vector<Event*> result;
    for (auto& e : events) {
        if (e->getDate() == date) {
            result.push_back(e.get());
        }
    }
    return result;
}

const vector<unique_ptr<Event>>& EventManager::getAllEvents() const {
    return events;
}

void EventManager::displayAllEvents() const {
    cout << "=== Campus Events Catalog (" << events.size() << " Events) ===" << endl;
    for (const auto& e : events) {
        e->display();
        cout << "--------------------------------" << endl;
    }
}
