#include "CourseManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

CourseManager::CourseManager() {}
CourseManager::~CourseManager() {}

void CourseManager::addCourse(const Course& course) {
    if (findCourse(course.getCourseId()) != nullptr) {
        cout << "[CourseManager] Warning: Course ID " << course.getCourseId()
             << " (" << course.getCourseCode() << ") already exists! Duplicate prevented." << endl;
        return;
    }
    courses.push_back(course);
}

bool CourseManager::removeCourse(int courseId) {
    auto it = remove_if(courses.begin(), courses.end(),
                        [courseId](const Course& c) { return c.getCourseId() == courseId; });
    if (it != courses.end()) {
        courses.erase(it, courses.end());
        return true;
    }
    return false;
}

Course* CourseManager::findCourse(int courseId) {
    for (auto& c : courses) {
        if (c.getCourseId() == courseId) return &c;
    }
    return nullptr;
}

const Course* CourseManager::findCourse(int courseId) const {
    for (const auto& c : courses) {
        if (c.getCourseId() == courseId) return &c;
    }
    return nullptr;
}

bool CourseManager::assignProfessor(int courseId, Professor& professor) {
    Course* c = findCourse(courseId);
    if (!c) {
        cout << "[CourseManager] Error: Course ID " << courseId << " not found." << endl;
        return false;
    }
    if (professor.getId() <= 0) {
        cout << "[CourseManager] Error: Invalid Professor ID." << endl;
        return false;
    }
    c->assignProfessor(professor.getId());
    professor.assignCourse(courseId);
    return true;
}

bool CourseManager::removeProfessor(int courseId, Professor& professor) {
    Course* c = findCourse(courseId);
    if (!c) {
        cout << "[CourseManager] Error: Course ID " << courseId << " not found." << endl;
        return false;
    }
    if (c->getProfessorId() == -1) {
        cout << "[CourseManager] Warning: Course ID " << courseId << " has no assigned professor." << endl;
        return false;
    }
    professor.removeCourse(courseId);
    c->removeProfessor();
    return true;
}

bool CourseManager::enrollStudent(int courseId, Student& student) {
    Course* c = findCourse(courseId);
    if (!c) {
        cout << "[CourseManager] Error: Course ID " << courseId << " not found." << endl;
        return false;
    }
    if (c->isStudentEnrolled(student.getId())) {
        cout << "[CourseManager] Warning: Student ID " << student.getId()
             << " is already enrolled in Course ID " << courseId << "." << endl;
        return false;
    }
    bool success = c->enrollStudent(student.getId());
    if (success) {
        student.addCourse(courseId);
    }
    return success;
}

bool CourseManager::removeStudent(int courseId, Student& student) {
    Course* c = findCourse(courseId);
    if (!c) {
        cout << "[CourseManager] Error: Course ID " << courseId << " not found." << endl;
        return false;
    }
    bool cRemoved = c->removeStudent(student.getId());
    bool sRemoved = student.removeCourse(courseId);
    return cRemoved || sRemoved;
}

void CourseManager::displayAllCourses() const {
    cout << "=== Course Catalog (" << courses.size() << " Courses) ===" << endl;
    for (const auto& c : courses) {
        c.display();
    }
}

int CourseManager::getCourseCount() const {
    return static_cast<int>(courses.size());
}

const vector<Course>& CourseManager::getAllCourses() const {
    return courses;
}
