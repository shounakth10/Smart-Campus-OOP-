#include "FacilityManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

FacilityManager::FacilityManager() {}
FacilityManager::~FacilityManager() {}

bool FacilityManager::addFacility(shared_ptr<Facility> facility) {
    if (!facility) return false;
    if (findFacility(facility->getFacilityId()) != nullptr) return false;
    facilities.push_back(facility);
    return true;
}

bool FacilityManager::removeFacility(int facilityId) {
    auto it = remove_if(facilities.begin(), facilities.end(),
                             [facilityId](const shared_ptr<Facility>& f) { return f->getFacilityId() == facilityId; });
    if (it != facilities.end()) {
        facilities.erase(it, facilities.end());
        return true;
    }
    return false;
}

Facility* FacilityManager::findFacility(int facilityId) {
    for (auto& f : facilities) {
        if (f->getFacilityId() == facilityId) return f.get();
    }
    return nullptr;
}

const Facility* FacilityManager::findFacility(int facilityId) const {
    for (const auto& f : facilities) {
        if (f->getFacilityId() == facilityId) return f.get();
    }
    return nullptr;
}

vector<shared_ptr<Facility>> FacilityManager::getAvailableFacilities() const {
    vector<shared_ptr<Facility>> result;
    for (const auto& f : facilities) {
        if (f->isAvailable()) result.push_back(f);
    }
    return result;
}

bool FacilityManager::isAvailable(int facilityId) const {
    const Facility* f = findFacility(facilityId);
    return f ? f->isAvailable() : false;
}

const vector<shared_ptr<Facility>>& FacilityManager::getAllFacilities() const {
    return facilities;
}

void FacilityManager::displayAllFacilities() const {
    cout << "--- Campus Facilities (" << facilities.size() << ") ---" << endl;
    for (const auto& f : facilities) {
        f->display();
    }
}
