#include "TimetableManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

TimetableManager::TimetableManager() {}
TimetableManager::~TimetableManager() {}

bool TimetableManager::hasConflict(const TimetableEntry& entry) const {
    for (const auto& e : entries) {
        if (e.getEntryId() == entry.getEntryId()) continue; // Skip self when editing

        if (e.conflictsWithProfessor(entry)) {
            cout << "[TimetableManager] Conflict rejected: Professor ID " << entry.getProfessorId()
                 << " has another lecture on " << entry.getDay() << " (" << entry.getStartTime()
                 << " - " << entry.getEndTime() << ")." << endl;
            return true;
        }
        if (e.conflictsWithFacility(entry)) {
            cout << "[TimetableManager] Conflict rejected: Facility ID " << entry.getFacilityId()
                 << " is occupied on " << entry.getDay() << " (" << entry.getStartTime()
                 << " - " << entry.getEndTime() << ")." << endl;
            return true;
        }
        if (e.conflictsWithClass(entry)) {
            cout << "[TimetableManager] Conflict rejected: Class Year " << entry.getYear()
                 << " Div " << entry.getDivision() << " has another lecture on " << entry.getDay()
                 << " (" << entry.getStartTime() << " - " << entry.getEndTime() << ")." << endl;
            return true;
        }
    }
    return false;
}

bool TimetableManager::addEntry(const TimetableEntry& entry) {
    if (findEntry(entry.getEntryId()) != nullptr) {
        cout << "[TimetableManager] Conflict rejected: Entry ID " << entry.getEntryId()
             << " already exists!" << endl;
        return false;
    }
    if (hasConflict(entry)) {
        return false;
    }
    entries.push_back(entry);
    cout << "[TimetableManager] Successfully added Timetable Entry ID " << entry.getEntryId() << endl;
    return true;
}

bool TimetableManager::editEntry(int entryId, const TimetableEntry& updated) {
    TimetableEntry* e = findEntry(entryId);
    if (!e) {
        cout << "[TimetableManager] Edit failed: Entry ID " << entryId << " not found." << endl;
        return false;
    }
    if (hasConflict(updated)) {
        return false;
    }
    *e = updated;
    cout << "[TimetableManager] Successfully updated Timetable Entry ID " << entryId << endl;
    return true;
}

bool TimetableManager::deleteEntry(int entryId) {
    auto it = remove_if(entries.begin(), entries.end(),
                        [entryId](const TimetableEntry& e) { return e.getEntryId() == entryId; });
    if (it != entries.end()) {
        entries.erase(it, entries.end());
        cout << "[TimetableManager] Successfully deleted Timetable Entry ID " << entryId << endl;
        return true;
    }
    cout << "[TimetableManager] Delete failed: Entry ID " << entryId << " not found." << endl;
    return false;
}

TimetableEntry* TimetableManager::findEntry(int entryId) {
    for (auto& e : entries) {
        if (e.getEntryId() == entryId) return &e;
    }
    return nullptr;
}

const TimetableEntry* TimetableManager::findEntry(int entryId) const {
    for (const auto& e : entries) {
        if (e.getEntryId() == entryId) return &e;
    }
    return nullptr;
}

vector<TimetableEntry> TimetableManager::getDailyTimetable(const string& day) const {
    vector<TimetableEntry> result;
    for (const auto& e : entries) {
        if (e.getDay() == day) result.push_back(e);
    }
    return result;
}

vector<TimetableEntry> TimetableManager::getProfessorTimetable(int professorId) const {
    vector<TimetableEntry> result;
    for (const auto& e : entries) {
        if (e.getProfessorId() == professorId) result.push_back(e);
    }
    return result;
}

vector<TimetableEntry> TimetableManager::getClassTimetable(const string& division, int year) const {
    vector<TimetableEntry> result;
    for (const auto& e : entries) {
        if (e.getDivision() == division && e.getYear() == year) result.push_back(e);
    }
    return result;
}

const vector<TimetableEntry>& TimetableManager::getAllEntries() const {
    return entries;
}

void TimetableManager::displayAllEntries() const {
    cout << "=== Master Timetable Catalog (" << entries.size() << " Entries) ===" << endl;
    for (const auto& e : entries) {
        e.display();
        cout << "--------------------------------" << endl;
    }
}
