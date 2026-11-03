#pragma once

#include "Person.h"

using namespace std;

class Staff : public Person {
private:
    string department;
    string designation;

public:
    Staff();
    Staff(int id, const string& name, const string& email, const string& phone,
          const string& department, const string& designation);
    virtual ~Staff() override = default;

    string getDepartment() const;
    void setDepartment(const string& department);

    string getDesignation() const;
    void setDesignation(const string& designation);

    virtual void display() const override;
    virtual string getRole() const override;
};
