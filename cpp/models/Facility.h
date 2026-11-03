#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Facility {
protected:
    int facilityId;
    string name;
    string location;
    int capacity;
    bool available;

public:
    Facility();
    Facility(int facilityId, const string& name, const string& location, int capacity, bool available = true);
    virtual ~Facility();

    int getFacilityId() const;
    string getName() const;
    string getLocation() const;
    int getCapacity() const;
    bool isAvailable() const;

    void setName(const string& name);
    void setLocation(const string& location);
    void setCapacity(int capacity);
    void setAvailable(bool available);

    virtual void display() const;
    virtual string getType() const;
};
