#pragma once

#include "../models/TimetableEntry.h"
#include <vector>

using namespace std;

class TimetableManager {
private:
    vector<TimetableEntry> entries;

public:
    TimetableManager();
    ~TimetableManager();

    bool addEntry(const TimetableEntry& entry);
    bool editEntry(int entryId, const TimetableEntry& updated);
    bool deleteEntry(int entryId);

    TimetableEntry* findEntry(int entryId);
    const TimetableEntry* findEntry(int entryId) const;

    bool hasConflict(const TimetableEntry& entry) const;

    vector<TimetableEntry> getDailyTimetable(const string& day) const;
    vector<TimetableEntry> getProfessorTimetable(int professorId) const;
    vector<TimetableEntry> getClassTimetable(const string& division, int year) const;
    const vector<TimetableEntry>& getAllEntries() const;

    void displayAllEntries() const;
};
