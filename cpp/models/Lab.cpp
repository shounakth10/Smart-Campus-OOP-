#include "Lab.h"

using namespace std;

Lab::Lab()
    : Facility(), labType("General"), computerCount(0), hasEquipment(false) {}

Lab::Lab(int facilityId, const string& name, const string& location, int capacity,
         const string& labType, int computerCount, bool hasEquipment, bool available)
    : Facility(facilityId, name, location, capacity, available),
      labType(labType), computerCount(computerCount), hasEquipment(hasEquipment) {
    if (computerCount < 0) {
        throw invalid_argument("Computer count cannot be negative.");
    }
}

string Lab::getLabType() const { return labType; }
int Lab::getComputerCount() const { return computerCount; }
bool Lab::getHasEquipment() const { return hasEquipment; }

void Lab::setLabType(const string& labType) { this->labType = labType; }

void Lab::setComputerCount(int computerCount) {
    if (computerCount < 0) {
        throw invalid_argument("Computer count cannot be negative.");
    }
    this->computerCount = computerCount;
}

void Lab::setHasEquipment(bool hasEquipment) { this->hasEquipment = hasEquipment; }

void Lab::display() const {
    Facility::display();
    cout << "Lab Type: " << labType << endl;
    cout << "Computers: " << computerCount << endl;
    cout << "Special Equipment: " << (hasEquipment ? "Yes" : "No") << endl;
}

string Lab::getType() const {
    return "Lab";
}
