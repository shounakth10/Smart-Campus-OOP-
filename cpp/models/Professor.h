#pragma once

#include "Person.h"
#include <vector>

using namespace std;

class Professor : public Person {
private:
    string department;
    string designation;
    vector<int> courseIds;

public:
    Professor();
    Professor(int id, const string& name, const string& email, const string& phone,
              const string& department, const string& designation);
    virtual ~Professor() override = default;

    string getDepartment() const;
    void setDepartment(const string& department);

    string getDesignation() const;
    void setDesignation(const string& designation);

    const vector<int>& getCourseIds() const;
    int getCourseCount() const;

    void assignCourse(int courseId);
    bool removeCourse(int courseId);
    bool teachesCourse(int courseId) const;
    void displayCourses() const;

    virtual void display() const override;
    virtual string getRole() const override;
};
