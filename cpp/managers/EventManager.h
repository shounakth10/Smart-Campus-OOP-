#pragma once

#include "../models/Event.h"
#include <vector>
#include <memory>

using namespace std;

class EventManager {
private:
    vector<unique_ptr<Event>> events;

public:
    EventManager();
    ~EventManager();

    bool addEvent(unique_ptr<Event> event);
    bool removeEvent(int eventId);

    Event* findEvent(int eventId);
    const Event* findEvent(int eventId) const;

    bool registerParticipant(int eventId, int studentId);
    bool removeParticipant(int eventId, int studentId);

    vector<Event*> getEventsByDate(const string& date);
    const vector<unique_ptr<Event>>& getAllEvents() const;
    void displayAllEvents() const;
};
