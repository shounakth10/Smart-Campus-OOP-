#pragma once

#include "../models/Student.h"
#include "../models/Professor.h"
#include "../models/Staff.h"
#include "../models/Facility.h"
#include "../models/Classroom.h"
#include "../models/Lab.h"
#include "../models/Auditorium.h"
#include "../models/SportsGround.h"
#include "../models/Course.h"
#include "../models/Booking.h"
#include "../models/TimetableEntry.h"
#include "../models/Event.h"
#include "../models/Workshop.h"
#include "../models/SportsEvent.h"
#include "../models/CulturalEvent.h"
#include "../models/TechnicalEvent.h"

#include "../managers/CourseManager.h"
#include "../managers/BookingManager.h"
#include "../managers/TimetableManager.h"
#include "../managers/EventManager.h"

#include <string>
#include <vector>
#include <memory>

using namespace std;

class FileManager {
public:
    // Saver methods
    static bool saveStudents(const string& filepath, const vector<Student>& students);
    static bool saveProfessors(const string& filepath, const vector<Professor>& professors);
    static bool saveStaff(const string& filepath, const vector<Staff>& staff);
    static bool saveFacilities(const string& filepath, const vector<unique_ptr<Facility>>& facilities);
    static bool saveCourses(const string& filepath, const vector<Course>& courses);
    static bool saveBookings(const string& filepath, const vector<Booking>& bookings);
    static bool saveTimetable(const string& filepath, const vector<TimetableEntry>& entries);
    static bool saveEvents(const string& filepath, const vector<unique_ptr<Event>>& events);

    // Loader methods
    static vector<Student> loadStudents(const string& filepath);
    static vector<Professor> loadProfessors(const string& filepath);
    static vector<Staff> loadStaff(const string& filepath);
    static vector<unique_ptr<Facility>> loadFacilities(const string& filepath);
    static vector<Course> loadCourses(const string& filepath);
    static vector<Booking> loadBookings(const string& filepath);
    static vector<TimetableEntry> loadTimetable(const string& filepath);
    static vector<unique_ptr<Event>> loadEvents(const string& filepath);

    // Master Save/Load Methods
    static bool saveAllData(const string& dataDir,
                            const vector<Student>& students,
                            const vector<Professor>& professors,
                            const vector<Staff>& staff,
                            const vector<unique_ptr<Facility>>& facilities,
                            const CourseManager& cm,
                            const BookingManager& bm,
                            const TimetableManager& tm,
                            const EventManager& em);

    static bool loadAllData(const string& dataDir,
                            vector<Student>& students,
                            vector<Professor>& professors,
                            vector<Staff>& staff,
                            vector<unique_ptr<Facility>>& facilities,
                            CourseManager& cm,
                            BookingManager& bm,
                            TimetableManager& tm,
                            EventManager& em);
};
