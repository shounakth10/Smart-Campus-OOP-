#include "Auditorium.h"

using namespace std;

Auditorium::Auditorium()
    : Facility(), hasStage(false), hasSoundSystem(false) {}

Auditorium::Auditorium(int facilityId, const string& name, const string& location, int capacity,
                       bool hasStage, bool hasSoundSystem, bool available)
    : Facility(facilityId, name, location, capacity, available),
      hasStage(hasStage), hasSoundSystem(hasSoundSystem) {}

bool Auditorium::getHasStage() const { return hasStage; }
bool Auditorium::getHasSoundSystem() const { return hasSoundSystem; }

void Auditorium::setHasStage(bool hasStage) { this->hasStage = hasStage; }
void Auditorium::setHasSoundSystem(bool hasSoundSystem) { this->hasSoundSystem = hasSoundSystem; }

void Auditorium::display() const {
    Facility::display();
    cout << "Stage: " << (hasStage ? "Yes" : "No") << endl;
    cout << "Sound System: " << (hasSoundSystem ? "Yes" : "No") << endl;
}

string Auditorium::getType() const {
    return "Auditorium";
}
