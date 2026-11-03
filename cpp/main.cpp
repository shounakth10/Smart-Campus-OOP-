#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

// Models
#include "models/Person.h"
#include "models/Student.h"
#include "models/Professor.h"
#include "models/Staff.h"

#include "models/Facility.h"
#include "models/Classroom.h"
#include "models/Lab.h"
#include "models/Auditorium.h"
#include "models/SportsGround.h"

#include "models/Course.h"
#include "models/Booking.h"
#include "models/TimetableEntry.h"

#include "models/Event.h"
#include "models/Workshop.h"
#include "models/SportsEvent.h"
#include "models/CulturalEvent.h"
#include "models/TechnicalEvent.h"

// Managers
#include "managers/CourseManager.h"
#include "managers/BookingManager.h"
#include "managers/TimetableManager.h"
#include "managers/EventManager.h"
#include "managers/AnalyticsManager.h"

// Utilities
#include "utils/DateTimeUtils.h"
#include "utils/FileManager.h"
#include "utils/CLIHandler.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc >= 3 && string(argv[1]) == "api") {
        return CLIHandler::handleCLI(argc, argv);
    }

    cout << "==========================================================================" << endl;
    cout << "     SMARTCAMPUS – CAMPUS MANAGEMENT & RESOURCE PLANNING SYSTEM          " << endl;
    cout << "==========================================================================\n" << endl;

    // =========================================================================
    // SECTION 1: SAMPLE DATA INITIALIZATION (STUDENTS, PROFESSORS, STAFF)
    // =========================================================================
    cout << "--- 1. Initializing Person Entities (5 Students, 3 Professors, 2 Staff) ---" << endl;
    vector<Student> students;
    students.emplace_back(101, "Rahul Sharma", "rahul@vit.edu", "9876543210", "CSE-AI", 2, "F");
    students.emplace_back(102, "Aditya Patil", "aditya@vit.edu", "9876543211", "CSE-AI", 2, "F");
    students.emplace_back(103, "Sneha Kulkarni", "sneha@vit.edu", "9876543212", "Computer Science", 3, "A");
    students.emplace_back(104, "Vikram Singh", "vikram@vit.edu", "9876543213", "Electronics", 1, "B");
    students.emplace_back(105, "Ananya Joshi", "ananya@vit.edu", "9876543214", "Computer Science", 3, "A");

    vector<Professor> professors;
    professors.emplace_back(201, "Dr. Amit Patil", "amit@vit.edu", "9876543220", "Computer Science", "Assistant Professor");
    professors.emplace_back(202, "Dr. Neha Joshi", "neha@vit.edu", "9876543221", "Computer Science", "Associate Professor");
    professors.emplace_back(203, "Dr. Rajesh Kumar", "rajesh@vit.edu", "9876543222", "Electronics", "Senior Professor");

    vector<Staff> staff;
    staff.emplace_back(301, "Priya Deshmukh", "priya@vit.edu", "9876543230", "Administration", "Office Assistant");
    staff.emplace_back(302, "Suresh Varma", "suresh@vit.edu", "9876543231", "IT Support", "Systems Administrator");

    cout << "Initialized " << students.size() << " Students, " << professors.size()
         << " Professors, and " << staff.size() << " Staff members.\n" << endl;

    // =========================================================================
    // SECTION 2: FACILITY INITIALIZATION (7 FACILITIES)
    // =========================================================================
    cout << "--- 2. Initializing Facilities (3 Classrooms, 2 Labs, 1 Auditorium, 1 SportsGround) ---" << endl;
    vector<unique_ptr<Facility>> facilities;
    facilities.push_back(unique_ptr<Facility>(new Classroom(101, "CSE Classroom 301", "Main Building", 60, "Main Building", 3, true)));
    facilities.push_back(unique_ptr<Facility>(new Classroom(102, "CSE Classroom 302", "Main Building", 60, "Main Building", 3, true)));
    facilities.push_back(unique_ptr<Facility>(new Classroom(103, "EC Classroom 101", "EC Block", 50, "EC Block", 1, false)));
    facilities.push_back(unique_ptr<Facility>(new Lab(201, "AI Lab", "CS Building", 40, "Artificial Intelligence", 40, true)));
    facilities.push_back(unique_ptr<Facility>(new Lab(202, "Programming Lab", "CS Building", 35, "Software Engineering", 35, true)));
    facilities.push_back(unique_ptr<Facility>(new Auditorium(301, "Main Auditorium", "Admin Block", 500, true, true)));
    facilities.push_back(unique_ptr<Facility>(new SportsGround(401, "Campus Lawn", "Central Campus", 300, "Leisure & Recreation", "Grass")));

    cout << "Initialized " << facilities.size() << " Facilities using std::unique_ptr.\n" << endl;

    // =========================================================================
    // SECTION 3: COURSE INITIALIZATION & ALLOCATIONS
    // =========================================================================
    cout << "--- 3. Initializing Courses & Allocations ---" << endl;
    CourseManager courseManager;
    courseManager.addCourse(Course(301, "CS201", "Data Structures", 4, "Computer Science"));
    courseManager.addCourse(Course(302, "CS202", "Object Oriented Programming", 4, "Computer Science"));
    courseManager.addCourse(Course(303, "AI201", "Machine Learning", 3, "Artificial Intelligence"));
    courseManager.addCourse(Course(304, "CS301", "Operating Systems", 4, "Computer Science"));
    courseManager.addCourse(Course(305, "EC101", "Basic Electronics", 3, "Electronics"));

    courseManager.assignProfessor(301, professors[0]);
    courseManager.assignProfessor(303, professors[0]);
    courseManager.assignProfessor(302, professors[1]);
    courseManager.assignProfessor(304, professors[1]);
    courseManager.assignProfessor(305, professors[2]);

    courseManager.enrollStudent(301, students[0]);
    courseManager.enrollStudent(302, students[0]);
    courseManager.enrollStudent(303, students[0]);
    courseManager.enrollStudent(301, students[1]);
    courseManager.enrollStudent(303, students[1]);
    courseManager.enrollStudent(304, students[2]);
    courseManager.enrollStudent(305, students[3]);

    cout << "Configured " << courseManager.getCourseCount() << " courses with professor assignments and student enrollments.\n" << endl;

    // =========================================================================
    // SECTION 4: BOOKINGS & CONFLICT TESTING
    // =========================================================================
    cout << "--- 4. Initializing Facility Bookings & Conflict Testing ---" << endl;
    BookingManager bookingManager;

    bookingManager.createBooking(Booking(501, 101, 101, "2026-10-10", "10:00", "12:00", "ACM Hackathon Briefing"));
    bookingManager.createBooking(Booking(502, 201, 201, "2026-10-10", "14:00", "17:00", "AI Lab Workshop"));
    bookingManager.createBooking(Booking(503, 301, 202, "2026-10-11", "09:00", "12:00", "Department Guest Lecture"));
    bookingManager.createBooking(Booking(504, 401, 103, "2026-10-12", "16:00", "18:00", "Lawn Recreation Session"));
    bookingManager.createBooking(Booking(505, 102, 203, "2026-10-13", "11:00", "13:00", "Electronics Lab Review"));

    // =========================================================================
    // SECTION 5: TIMETABLE & CONFLICT TESTING
    // =========================================================================
    cout << "--- 5. Initializing Timetable ---" << endl;
    TimetableManager timetableManager;

    timetableManager.addEntry(TimetableEntry(601, 301, 201, 101, "Monday", "10:00", "12:00", "F", 2));
    timetableManager.addEntry(TimetableEntry(602, 302, 202, 102, "Monday", "13:00", "15:00", "F", 2));
    timetableManager.addEntry(TimetableEntry(603, 303, 201, 201, "Tuesday", "10:00", "12:00", "F", 2));
    timetableManager.addEntry(TimetableEntry(604, 304, 202, 101, "Tuesday", "13:00", "15:00", "A", 3));
    timetableManager.addEntry(TimetableEntry(605, 305, 203, 103, "Wednesday", "10:00", "12:00", "B", 1));
    timetableManager.addEntry(TimetableEntry(606, 301, 201, 101, "Wednesday", "14:00", "16:00", "F", 2));

    // =========================================================================
    // SECTION 6: EVENT MANAGEMENT & CAPACITY TESTING
    // =========================================================================
    cout << "--- 6. Initializing Events ---" << endl;
    EventManager eventManager;

    auto w1 = make_unique<Workshop>(701, "C++ Modern Design", "Deep dive into C++17/20",
                                    "2026-10-15", "10:00", "13:00", 201, 201, 2,
                                    "Modern Metaprogramming", "Dr. Amit Patil");

    auto s1 = make_unique<SportsEvent>(702, "Campus Lawn Gathering", "Cultural Outdoor Evening",
                                      "2026-10-18", "15:00", "18:00", 401, 301, 100,
                                      "Outdoor Event", "Annual");

    auto c1 = make_unique<CulturalEvent>(703, "Annual Cultural Fest", "Music & Dance Night",
                                         "2026-10-22", "18:00", "21:00", 301, 301, 500,
                                         "Music & Performance Art");

    auto t1 = make_unique<TechnicalEvent>(704, "SmartCampus Hackathon 2026", "24-hr System Design Hack",
                                         "2026-10-25", "09:00", "17:00", 301, 101, 100,
                                         "Systems Architecture", "Hackathon");

    eventManager.addEvent(move(w1));
    eventManager.addEvent(move(s1));
    eventManager.addEvent(move(c1));
    eventManager.addEvent(move(t1));

    // =========================================================================
    // SECTION 7: ANALYTICS DASHBOARD
    // =========================================================================
    AnalyticsManager analyticsManager(60.0); // 12 hrs/day x 5 days/week = 60 hrs baseline
    analyticsManager.displayDashboard(students, professors, staff, courseManager,
                                      facilities, bookingManager, timetableManager, eventManager);

    // Save initial state to CSV
    FileManager::saveAllData("data", students, professors, staff, facilities,
                             courseManager, bookingManager, timetableManager, eventManager);

    cout << "\n==========================================================================" << endl;
    cout << " ALL C++ BACKEND MODULES EXECUTED & DATA SAVED SUCCESSFULLY!             " << endl;
    cout << "==========================================================================" << endl;

    return 0;
}
