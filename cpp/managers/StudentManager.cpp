#include "StudentManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

StudentManager::StudentManager() {}
StudentManager::~StudentManager() {}

bool StudentManager::addStudent(const Student& student) {
    if (findStudent(student.getId()) != nullptr) return false;
    students.push_back(student);
    return true;
}

bool StudentManager::removeStudent(int studentId) {
    auto it = remove_if(students.begin(), students.end(),
                             [studentId](const Student& s) { return s.getId() == studentId; });
    if (it != students.end()) {
        students.erase(it, students.end());
        return true;
    }
    return false;
}

bool StudentManager::updateStudent(const Student& student) {
    Student* s = findStudent(student.getId());
    if (s != nullptr) {
        *s = student;
        return true;
    }
    return false;
}

Student* StudentManager::findStudent(int studentId) {
    for (auto& s : students) {
        if (s.getId() == studentId) return &s;
    }
    return nullptr;
}

const Student* StudentManager::findStudent(int studentId) const {
    for (const auto& s : students) {
        if (s.getId() == studentId) return &s;
    }
    return nullptr;
}

const vector<Student>& StudentManager::getAllStudents() const {
    return students;
}

void StudentManager::displayAllStudents() const {
    cout << "--- Registered Students (" << students.size() << ") ---" << endl;
    for (const auto& s : students) {
        s.display();
    }
}
