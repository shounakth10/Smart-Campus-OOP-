#include "SportsGround.h"

using namespace std;

SportsGround::SportsGround()
    : Facility(), sportType("Multi-sport"), surfaceType("Turf") {}

SportsGround::SportsGround(int facilityId, const string& name, const string& location, int capacity,
                           const string& sportType, const string& surfaceType, bool available)
    : Facility(facilityId, name, location, capacity, available),
      sportType(sportType), surfaceType(surfaceType) {}

string SportsGround::getSportType() const { return sportType; }
string SportsGround::getSurfaceType() const { return surfaceType; }

void SportsGround::setSportType(const string& sportType) { this->sportType = sportType; }
void SportsGround::setSurfaceType(const string& surfaceType) { this->surfaceType = surfaceType; }

void SportsGround::display() const {
    Facility::display();
    cout << "Sport: " << sportType << endl;
    cout << "Surface: " << surfaceType << endl;
}

string SportsGround::getType() const {
    return "Sports Ground";
}
