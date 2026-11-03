#pragma once

#include "Facility.h"

using namespace std;

class Auditorium : public Facility {
private:
    bool hasStage;
    bool hasSoundSystem;

public:
    Auditorium();
    Auditorium(int facilityId, const string& name, const string& location, int capacity,
               bool hasStage, bool hasSoundSystem, bool available = true);
    virtual ~Auditorium() override = default;

    bool getHasStage() const;
    bool getHasSoundSystem() const;

    void setHasStage(bool hasStage);
    void setHasSoundSystem(bool hasSoundSystem);

    virtual void display() const override;
    virtual string getType() const override;
};
