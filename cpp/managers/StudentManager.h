#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "../models/Student.h"
#include <vector>

using namespace std;

class StudentManager {
private:
    vector<Student> students;

public:
    StudentManager();
    ~StudentManager();

    bool addStudent(const Student& student);
    bool removeStudent(int studentId);
    bool updateStudent(const Student& student);
    Student* findStudent(int studentId);
    const Student* findStudent(int studentId) const;
    const vector<Student>& getAllStudents() const;
    void displayAllStudents() const;
};

#endif 
