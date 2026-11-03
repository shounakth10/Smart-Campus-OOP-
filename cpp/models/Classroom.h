#pragma once

#include "Facility.h"

using namespace std;

class Classroom : public Facility {
private:
    string building;
    int floor;
    bool hasProjector;

public:
    Classroom();
    Classroom(int facilityId, const string& name, const string& location, int capacity,
              const string& building, int floor, bool hasProjector, bool available = true);
    virtual ~Classroom() override = default;

    string getBuilding() const;
    int getFloor() const;
    bool hasProjectorAvailable() const;

    void setBuilding(const string& building);
    void setFloor(int floor);
    void setHasProjector(bool hasProjector);

    virtual void display() const override;
    virtual string getType() const override;
};
