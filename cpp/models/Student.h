#pragma once

#include "Person.h"
#include <vector>

using namespace std;

class Student : public Person {
private:
    string branch;
    int year;
    string division;
    vector<int> courseIds;

public:
    Student();
    Student(int id, const string& name, const string& email, const string& phone,
            const string& branch, int year, const string& division);
    virtual ~Student() override = default;

    string getBranch() const;
    void setBranch(const string& branch);

    int getYear() const;
    void setYear(int year);

    string getDivision() const;
    void setDivision(const string& division);

    const vector<int>& getCourseIds() const;
    int getCourseCount() const;

    void addCourse(int courseId);
    bool removeCourse(int courseId);
    bool isEnrolledInCourse(int courseId) const;
    void displayCourses() const;

    virtual void display() const override;
    virtual string getRole() const override;
};
