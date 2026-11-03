#include "Student.h"
#include <algorithm>

using namespace std;

Student::Student() : Person(), branch(""), year(1), division("") {}

Student::Student(int id, const string& name, const string& email, const string& phone,
                 const string& branch, int year, const string& division)
    : Person(id, name, email, phone), branch(branch), year(year), division(division) {}

string Student::getBranch() const { return branch; }
void Student::setBranch(const string& branch) { this->branch = branch; }

int Student::getYear() const { return year; }
void Student::setYear(int year) { this->year = year; }

string Student::getDivision() const { return division; }
void Student::setDivision(const string& division) { this->division = division; }

const vector<int>& Student::getCourseIds() const { return courseIds; }
int Student::getCourseCount() const { return static_cast<int>(courseIds.size()); }

void Student::addCourse(int courseId) {
    if (!isEnrolledInCourse(courseId)) {
        courseIds.push_back(courseId);
    } else {
        cout << "[Student] Course ID " << courseId << " is already added." << endl;
    }
}

bool Student::removeCourse(int courseId) {
    auto it = find(courseIds.begin(), courseIds.end(), courseId);
    if (it != courseIds.end()) {
        courseIds.erase(it);
        return true;
    }
    return false;
}

bool Student::isEnrolledInCourse(int courseId) const {
    return find(courseIds.begin(), courseIds.end(), courseId) != courseIds.end();
}

void Student::displayCourses() const {
    cout << "Courses: ";
    if (courseIds.empty()) {
        cout << "None" << endl;
        return;
    }
    for (size_t i = 0; i < courseIds.size(); ++i) {
        cout << courseIds[i] << (i + 1 < courseIds.size() ? ", " : "");
    }
    cout << endl;
}

void Student::display() const {
    Person::display();
    cout << "Branch: " << branch << endl;
    cout << "Year: " << year << endl;
    cout << "Division: " << division << endl;
    displayCourses();
}

string Student::getRole() const {
    return "Student";
}
