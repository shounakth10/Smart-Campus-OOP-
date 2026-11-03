#pragma once

#include <string>
#include <iostream>

using namespace std;

class Person {
protected:
    int id;
    string name;
    string email;
    string phone;

public:
    Person();
    Person(int id, const string& name, const string& email, const string& phone);
    virtual ~Person();

    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string& name);

    string getEmail() const;
    void setEmail(const string& email);

    string getPhone() const;
    void setPhone(const string& phone);

    virtual void display() const;
    virtual string getRole() const;
};
