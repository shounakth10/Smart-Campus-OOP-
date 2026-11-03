#include "Facility.h"

using namespace std;

Facility::Facility()
    : facilityId(1), name("Default Facility"), location("Unknown"), capacity(0), available(true) {}

Facility::Facility(int facilityId, const string& name, const string& location, int capacity, bool available)
    : facilityId(facilityId), name(name), location(location), capacity(capacity), available(available) {
    if (facilityId <= 0) {
        throw invalid_argument("Facility ID must be positive.");
    }
    if (name.empty()) {
        throw invalid_argument("Facility name cannot be empty.");
    }
    if (capacity < 0) {
        throw invalid_argument("Capacity cannot be negative.");
    }
}

Facility::~Facility() {}

int Facility::getFacilityId() const { return facilityId; }
string Facility::getName() const { return name; }
string Facility::getLocation() const { return location; }
int Facility::getCapacity() const { return capacity; }
bool Facility::isAvailable() const { return available; }

void Facility::setName(const string& name) {
    if (name.empty()) {
        throw invalid_argument("Facility name cannot be empty.");
    }
    this->name = name;
}

void Facility::setLocation(const string& location) {
    this->location = location;
}

void Facility::setCapacity(int capacity) {
    if (capacity < 0) {
        throw invalid_argument("Capacity cannot be negative.");
    }
    this->capacity = capacity;
}

void Facility::setAvailable(bool available) {
    this->available = available;
}

void Facility::display() const {
    cout << "Facility ID: " << facilityId << endl;
    cout << "Name: " << name << endl;
    cout << "Location: " << location << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Availability: " << (available ? "Available" : "Occupied") << endl;
    cout << "Type: " << getType() << endl;
}

string Facility::getType() const {
    return "Facility";
}
