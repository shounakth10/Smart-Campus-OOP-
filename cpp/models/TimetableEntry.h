#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "../utils/DateTimeUtils.h"

using namespace std;

class TimetableEntry {
private:
    int entryId;
    int courseId;
    int professorId;
    int facilityId;
    string day;
    string startTime;
    string endTime;
    string division;
    int year;

public:
    TimetableEntry();
    TimetableEntry(int entryId, int courseId, int professorId, int facilityId,
                   const string& day, const string& startTime, const string& endTime,
                   const string& division, int year);

    int getEntryId() const;
    int getCourseId() const;
    int getProfessorId() const;
    int getFacilityId() const;
    string getDay() const;
    string getStartTime() const;
    string getEndTime() const;
    string getDivision() const;
    int getYear() const;

    void setCourseId(int courseId);
    void setProfessorId(int professorId);
    void setFacilityId(int facilityId);
    void setDay(const string& day);
    void setTime(const string& startTime, const string& endTime);
    void setDivision(const string& division);
    void setYear(int year);

    bool overlaps(const TimetableEntry& other) const;
    bool conflictsWithProfessor(const TimetableEntry& other) const;
    bool conflictsWithFacility(const TimetableEntry& other) const;
    bool conflictsWithClass(const TimetableEntry& other) const;

    void display() const;
};
