#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include "../models/Facility.h"
#include <vector>
#include <memory>

using namespace std;

class FacilityManager {
private:
    vector<shared_ptr<Facility>> facilities;

public:
    FacilityManager();
    ~FacilityManager();

    bool addFacility(shared_ptr<Facility> facility);
    bool removeFacility(int facilityId);
    Facility* findFacility(int facilityId);
    const Facility* findFacility(int facilityId) const;
    vector<shared_ptr<Facility>> getAvailableFacilities() const;
    bool isAvailable(int facilityId) const;
    const vector<shared_ptr<Facility>>& getAllFacilities() const;
    void displayAllFacilities() const;
};

#endif 
