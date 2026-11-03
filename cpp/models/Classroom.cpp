#include "Classroom.h"

using namespace std;

Classroom::Classroom()
    : Facility(), building("Main Building"), floor(1), hasProjector(false) {}

Classroom::Classroom(int facilityId, const string& name, const string& location, int capacity,
                     const string& building, int floor, bool hasProjector, bool available)
    : Facility(facilityId, name, location, capacity, available),
      building(building), floor(floor), hasProjector(hasProjector) {
    if (floor < 0) {
        throw invalid_argument("Floor cannot be negative.");
    }
}

string Classroom::getBuilding() const { return building; }
int Classroom::getFloor() const { return floor; }
bool Classroom::hasProjectorAvailable() const { return hasProjector; }

void Classroom::setBuilding(const string& building) { this->building = building; }

void Classroom::setFloor(int floor) {
    if (floor < 0) {
        throw invalid_argument("Floor cannot be negative.");
    }
    this->floor = floor;
}

void Classroom::setHasProjector(bool hasProjector) { this->hasProjector = hasProjector; }

void Classroom::display() const {
    Facility::display();
    cout << "Building: " << building << endl;
    cout << "Floor: " << floor << endl;
    cout << "Projector: " << (hasProjector ? "Yes" : "No") << endl;
}

string Classroom::getType() const {
    return "Classroom";
}
