#include "Professor.h"
#include <algorithm>

using namespace std;

Professor::Professor() : Person(), department(""), designation("") {}

Professor::Professor(int id, const string& name, const string& email, const string& phone,
                     const string& department, const string& designation)
    : Person(id, name, email, phone), department(department), designation(designation) {}

string Professor::getDepartment() const { return department; }
void Professor::setDepartment(const string& department) { this->department = department; }

string Professor::getDesignation() const { return designation; }
void Professor::setDesignation(const string& designation) { this->designation = designation; }

const vector<int>& Professor::getCourseIds() const { return courseIds; }
int Professor::getCourseCount() const { return static_cast<int>(courseIds.size()); }

void Professor::assignCourse(int courseId) {
    if (!teachesCourse(courseId)) {
        courseIds.push_back(courseId);
    } else {
        cout << "[Professor] Course ID " << courseId << " is already assigned." << endl;
    }
}

bool Professor::removeCourse(int courseId) {
    auto it = find(courseIds.begin(), courseIds.end(), courseId);
    if (it != courseIds.end()) {
        courseIds.erase(it);
        return true;
    }
    return false;
}

bool Professor::teachesCourse(int courseId) const {
    return find(courseIds.begin(), courseIds.end(), courseId) != courseIds.end();
}

void Professor::displayCourses() const {
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

void Professor::display() const {
    Person::display();
    cout << "Department: " << department << endl;
    cout << "Designation: " << designation << endl;
    displayCourses();
}

string Professor::getRole() const {
    return "Professor";
}
