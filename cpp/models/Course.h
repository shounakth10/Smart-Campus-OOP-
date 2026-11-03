#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Course {
private:
    int courseId;
    string courseCode;
    string courseName;
    int credits;
    string department;
    int professorId;
    vector<int> enrolledStudentIds;

public:
    Course();
    Course(int courseId, const string& courseCode, const string& courseName,
           int credits, const string& department);

    int getCourseId() const;
    string getCourseCode() const;
    string getCourseName() const;
    int getCredits() const;
    string getDepartment() const;
    int getProfessorId() const;
    const vector<int>& getEnrolledStudentIds() const;
    int getEnrollmentCount() const;

    void setCourseCode(const string& courseCode);
    void setCourseName(const string& courseName);
    void setCredits(int credits);
    void setDepartment(const string& department);

    void assignProfessor(int professorId);
    void removeProfessor();

    bool enrollStudent(int studentId);
    bool removeStudent(int studentId);
    bool isStudentEnrolled(int studentId) const;

    void display() const;
};
