#include "Person.h"

using namespace std;

Person::Person() : id(0), name(""), email(""), phone("") {}

Person::Person(int id, const string& name, const string& email, const string& phone)
    : id(id), name(name), email(email), phone(phone) {}

Person::~Person() {}

int Person::getId() const { return id; }
void Person::setId(int id) { this->id = id; }

string Person::getName() const { return name; }
void Person::setName(const string& name) { this->name = name; }

string Person::getEmail() const { return email; }
void Person::setEmail(const string& email) { this->email = email; }

string Person::getPhone() const { return phone; }
void Person::setPhone(const string& phone) { this->phone = phone; }

void Person::display() const {
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Role: " << getRole() << endl;
}

string Person::getRole() const {
    return "Person";
}
