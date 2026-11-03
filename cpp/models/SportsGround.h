#pragma once

#include "Facility.h"

using namespace std;

class SportsGround : public Facility {
private:
    string sportType;
    string surfaceType;

public:
    SportsGround();
    SportsGround(int facilityId, const string& name, const string& location, int capacity,
                 const string& sportType, const string& surfaceType, bool available = true);
    virtual ~SportsGround() override = default;

    string getSportType() const;
    string getSurfaceType() const;

    void setSportType(const string& sportType);
    void setSurfaceType(const string& surfaceType);

    virtual void display() const override;
    virtual string getType() const override;
};
