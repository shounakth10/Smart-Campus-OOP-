#include "TimetableEntry.h"

using namespace std;

TimetableEntry::TimetableEntry()
    : entryId(0), courseId(0), professorId(0), facilityId(0), day("Monday"),
      startTime("00:00"), endTime("00:00"), division(""), year(1) {}

TimetableEntry::TimetableEntry(int entryId, int courseId, int professorId, int facilityId,
                               const string& day, const string& startTime, const string& endTime,
                               const string& division, int year)
    : entryId(entryId), courseId(courseId), professorId(professorId), facilityId(facilityId),
      day(day), startTime(startTime), endTime(endTime), division(division), year(year) {
    if (entryId <= 0) throw invalid_argument("Entry ID must be positive.");
    if (courseId <= 0) throw invalid_argument("Course ID must be positive.");
    if (professorId <= 0) throw invalid_argument("Professor ID must be positive.");
    if (facilityId <= 0) throw invalid_argument("Facility ID must be positive.");
    if (day.empty()) throw invalid_argument("Day cannot be empty.");
    if (division.empty()) throw invalid_argument("Division cannot be empty.");
    if (year <= 0) throw invalid_argument("Year must be positive.");
    if (!DateTimeUtils::isValidTime(startTime) || !DateTimeUtils::isValidTime(endTime)) {
        throw invalid_argument("Invalid time format for TimetableEntry.");
    }
    if (DateTimeUtils::timeToMinutes(endTime) <= DateTimeUtils::timeToMinutes(startTime)) {
        throw invalid_argument("End time must be after start time.");
    }
}

int TimetableEntry::getEntryId() const { return entryId; }
int TimetableEntry::getCourseId() const { return courseId; }
int TimetableEntry::getProfessorId() const { return professorId; }
int TimetableEntry::getFacilityId() const { return facilityId; }
string TimetableEntry::getDay() const { return day; }
string TimetableEntry::getStartTime() const { return startTime; }
string TimetableEntry::getEndTime() const { return endTime; }
string TimetableEntry::getDivision() const { return division; }
int TimetableEntry::getYear() const { return year; }

void TimetableEntry::setCourseId(int courseId) { this->courseId = courseId; }
void TimetableEntry::setProfessorId(int professorId) { this->professorId = professorId; }
void TimetableEntry::setFacilityId(int facilityId) { this->facilityId = facilityId; }
void TimetableEntry::setDay(const string& day) { this->day = day; }
void TimetableEntry::setTime(const string& startTime, const string& endTime) {
    if (!DateTimeUtils::isValidTime(startTime) || !DateTimeUtils::isValidTime(endTime)) {
        throw invalid_argument("Invalid time format.");
    }
    if (DateTimeUtils::timeToMinutes(endTime) <= DateTimeUtils::timeToMinutes(startTime)) {
        throw invalid_argument("End time must be after start time.");
    }
    this->startTime = startTime;
    this->endTime = endTime;
}
void TimetableEntry::setDivision(const string& division) { this->division = division; }
void TimetableEntry::setYear(int year) { this->year = year; }

bool TimetableEntry::overlaps(const TimetableEntry& other) const {
    if (this->day != other.day) return false;
    return DateTimeUtils::isTimeOverlap(this->startTime, this->endTime, other.startTime, other.endTime);
}

bool TimetableEntry::conflictsWithProfessor(const TimetableEntry& other) const {
    if (this->professorId != other.professorId) return false;
    return overlaps(other);
}

bool TimetableEntry::conflictsWithFacility(const TimetableEntry& other) const {
    if (this->facilityId != other.facilityId) return false;
    return overlaps(other);
}

bool TimetableEntry::conflictsWithClass(const TimetableEntry& other) const {
    if (this->year != other.year || this->division != other.division) return false;
    return overlaps(other);
}

void TimetableEntry::display() const {
    cout << "Entry ID: " << entryId << endl;
    cout << "Course ID: " << courseId << endl;
    cout << "Professor ID: " << professorId << endl;
    cout << "Facility ID: " << facilityId << endl;
    cout << "Class: Year " << year << " Div " << division << endl;
    cout << "Day: " << day << endl;
    cout << "Time: " << startTime << " - " << endTime << endl;
}
