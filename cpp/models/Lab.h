#pragma once

#include "Facility.h"

using namespace std;

class Lab : public Facility {
private:
    string labType;
    int computerCount;
    bool hasEquipment;

public:
    Lab();
    Lab(int facilityId, const string& name, const string& location, int capacity,
        const string& labType, int computerCount, bool hasEquipment, bool available = true);
    virtual ~Lab() override = default;

    string getLabType() const;
    int getComputerCount() const;
    bool getHasEquipment() const;

    void setLabType(const string& labType);
    void setComputerCount(int computerCount);
    void setHasEquipment(bool hasEquipment);

    virtual void display() const override;
    virtual string getType() const override;
};
