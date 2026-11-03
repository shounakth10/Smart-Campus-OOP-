#pragma once

#include "../models/Course.h"
#include "../models/Student.h"
#include "../models/Professor.h"
#include <vector>

using namespace std;

class CourseManager {
private:
    vector<Course> courses;

public:
    CourseManager();
    ~CourseManager();

    void addCourse(const Course& course);
    bool removeCourse(int courseId);

    Course* findCourse(int courseId);
    const Course* findCourse(int courseId) const;

    bool assignProfessor(int courseId, Professor& professor);
    bool removeProfessor(int courseId, Professor& professor);

    bool enrollStudent(int courseId, Student& student);
    bool removeStudent(int courseId, Student& student);

    void displayAllCourses() const;
    int getCourseCount() const;
    const vector<Course>& getAllCourses() const;
};
