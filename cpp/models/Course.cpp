#include "Course.h"
#include <algorithm>

using namespace std;

Course::Course()
    : courseId(0), courseCode(""), courseName(""), credits(0), department(""), professorId(-1) {}

Course::Course(int courseId, const string& courseCode, const string& courseName,
               int credits, const string& department)
    : courseId(courseId), courseCode(courseCode), courseName(courseName),
      credits(credits), department(department), professorId(-1) {
    if (courseId <= 0) {
        throw invalid_argument("Course ID must be positive.");
    }
    if (courseCode.empty()) {
        throw invalid_argument("Course code cannot be empty.");
    }
    if (courseName.empty()) {
        throw invalid_argument("Course name cannot be empty.");
    }
    if (credits <= 0) {
        throw invalid_argument("Credits must be greater than 0.");
    }
    if (department.empty()) {
        throw invalid_argument("Department cannot be empty.");
    }
}

int Course::getCourseId() const { return courseId; }
string Course::getCourseCode() const { return courseCode; }
string Course::getCourseName() const { return courseName; }
int Course::getCredits() const { return credits; }
string Course::getDepartment() const { return department; }
int Course::getProfessorId() const { return professorId; }
const vector<int>& Course::getEnrolledStudentIds() const { return enrolledStudentIds; }
int Course::getEnrollmentCount() const { return static_cast<int>(enrolledStudentIds.size()); }

void Course::setCourseCode(const string& courseCode) {
    if (courseCode.empty()) throw invalid_argument("Course code cannot be empty.");
    this->courseCode = courseCode;
}

void Course::setCourseName(const string& courseName) {
    if (courseName.empty()) throw invalid_argument("Course name cannot be empty.");
    this->courseName = courseName;
}

void Course::setCredits(int credits) {
    if (credits <= 0) throw invalid_argument("Credits must be greater than 0.");
    this->credits = credits;
}

void Course::setDepartment(const string& department) {
    if (department.empty()) throw invalid_argument("Department cannot be empty.");
    this->department = department;
}

void Course::assignProfessor(int professorId) {
    if (professorId <= 0) {
        throw invalid_argument("Professor ID must be positive.");
    }
    this->professorId = professorId;
}

void Course::removeProfessor() {
    this->professorId = -1;
}

bool Course::enrollStudent(int studentId) {
    if (studentId <= 0) return false;
    if (!isStudentEnrolled(studentId)) {
        enrolledStudentIds.push_back(studentId);
        return true;
    }
    return false;
}

bool Course::removeStudent(int studentId) {
    auto it = find(enrolledStudentIds.begin(), enrolledStudentIds.end(), studentId);
    if (it != enrolledStudentIds.end()) {
        enrolledStudentIds.erase(it);
        return true;
    }
    return false;
}

bool Course::isStudentEnrolled(int studentId) const {
    return find(enrolledStudentIds.begin(), enrolledStudentIds.end(), studentId) != enrolledStudentIds.end();
}

void Course::display() const {
    cout << "--------------------------------" << endl;
    cout << "Course ID: " << courseId << endl;
    cout << "Course Code: " << courseCode << endl;
    cout << "Course Name: " << courseName << endl;
    cout << "Credits: " << credits << endl;
    cout << "Department: " << department << endl;
    if (professorId == -1) {
        cout << "Professor: Not Assigned" << endl;
    } else {
        cout << "Professor ID: " << professorId << endl;
    }
    cout << "Enrolled Students: " << getEnrollmentCount() << endl;
    cout << "--------------------------------" << endl;
}
