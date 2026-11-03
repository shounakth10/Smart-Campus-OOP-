#include "Staff.h"

using namespace std;

Staff::Staff() : Person(), department(""), designation("") {}

Staff::Staff(int id, const string& name, const string& email, const string& phone,
             const string& department, const string& designation)
    : Person(id, name, email, phone), department(department), designation(designation) {}

string Staff::getDepartment() const { return department; }
void Staff::setDepartment(const string& department) { this->department = department; }

string Staff::getDesignation() const { return designation; }
void Staff::setDesignation(const string& designation) { this->designation = designation; }

void Staff::display() const {
    Person::display();
    cout << "Department: " << department << endl;
    cout << "Designation: " << designation << endl;
}

string Staff::getRole() const {
    return "Staff";
}
