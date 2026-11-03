#include "CLIHandler.h"

#include "../models/Person.h"
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
#include "../managers/AnalyticsManager.h"

#include "FileManager.h"
#include "DateTimeUtils.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

static string jsonEscape(const string& s) {
    string res = "";
    for (char c : s) {
        if (c == '"') res += "\\\"";
        else if (c == '\\') res += "\\\\";
        else if (c == '\n') res += "\\n";
        else if (c == '\r') res += "\\r";
        else if (c == '\t') res += "\\t";
        else res += c;
    }
    return res;
}

int CLIHandler::handleCLI(int argc, char* argv[]) {
    if (argc < 3) return 1;

    string cmd = argv[2];
    string dataDir = "data";

    vector<Student> students;
    vector<Professor> professors;
    vector<Staff> staff;
    vector<unique_ptr<Facility>> facilities;
    CourseManager courseManager;
    BookingManager bookingManager;
    TimetableManager timetableManager;
    EventManager eventManager;

    FileManager::loadAllData(dataDir, students, professors, staff, facilities,
                             courseManager, bookingManager, timetableManager, eventManager);

    AnalyticsManager analyticsManager(60.0); // 12 hours/day x 5 days/week = 60 hours baseline

    if (cmd == "dashboard") {
        DashboardStats stats = analyticsManager.getDashboardStatistics(students, professors, staff,
                                                                        courseManager, facilities,
                                                                        bookingManager, timetableManager, eventManager);
        cout << "{"
             << "\"totalStudents\":" << stats.totalStudents << ","
             << "\"totalProfessors\":" << stats.totalProfessors << ","
             << "\"totalStaff\":" << stats.totalStaff << ","
             << "\"totalCourses\":" << stats.totalCourses << ","
             << "\"totalFacilities\":" << stats.totalFacilities << ","
             << "\"totalBookings\":" << stats.totalBookings << ","
             << "\"activeBookings\":" << stats.activeBookings << ","
             << "\"totalTimetableEntries\":" << stats.totalTimetableEntries << ","
             << "\"totalEvents\":" << stats.totalEvents << ","
             << "\"averageFacilityUtilization\":" << stats.averageFacilityUtilization << ","
             << "\"mostUtilizedFacility\":\"" << jsonEscape(stats.mostUtilizedFacility) << "\","
             << "\"underutilizedFacilityCount\":" << stats.underutilizedFacilityCount
             << "}" << endl;
        return 0;
    }

    if (cmd == "students") {
        cout << "[";
        for (size_t i = 0; i < students.size(); ++i) {
            const auto& s = students[i];
            cout << "{"
                 << "\"id\":" << s.getId() << ","
                 << "\"name\":\"" << jsonEscape(s.getName()) << "\","
                 << "\"email\":\"" << jsonEscape(s.getEmail()) << "\","
                 << "\"phone\":\"" << jsonEscape(s.getPhone()) << "\","
                 << "\"branch\":\"" << jsonEscape(s.getBranch()) << "\","
                 << "\"year\":" << s.getYear() << ","
                 << "\"division\":\"" << jsonEscape(s.getDivision()) << "\","
                 << "\"courseCount\":" << s.getCourseCount()
                 << "}" << (i + 1 < students.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "professors") {
        cout << "[";
        for (size_t i = 0; i < professors.size(); ++i) {
            const auto& p = professors[i];
            cout << "{"
                 << "\"id\":" << p.getId() << ","
                 << "\"name\":\"" << jsonEscape(p.getName()) << "\","
                 << "\"email\":\"" << jsonEscape(p.getEmail()) << "\","
                 << "\"phone\":\"" << jsonEscape(p.getPhone()) << "\","
                 << "\"department\":\"" << jsonEscape(p.getDepartment()) << "\","
                 << "\"designation\":\"" << jsonEscape(p.getDesignation()) << "\","
                 << "\"courseCount\":" << p.getCourseCount()
                 << "}" << (i + 1 < professors.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "staff") {
        cout << "[";
        for (size_t i = 0; i < staff.size(); ++i) {
            const auto& st = staff[i];
            cout << "{"
                 << "\"id\":" << st.getId() << ","
                 << "\"name\":\"" << jsonEscape(st.getName()) << "\","
                 << "\"email\":\"" << jsonEscape(st.getEmail()) << "\","
                 << "\"phone\":\"" << jsonEscape(st.getPhone()) << "\","
                 << "\"department\":\"" << jsonEscape(st.getDepartment()) << "\","
                 << "\"designation\":\"" << jsonEscape(st.getDesignation()) << "\""
                 << "}" << (i + 1 < staff.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "courses") {
        const auto& courses = courseManager.getAllCourses();
        cout << "[";
        for (size_t i = 0; i < courses.size(); ++i) {
            const auto& c = courses[i];
            cout << "{"
                 << "\"courseId\":" << c.getCourseId() << ","
                 << "\"courseCode\":\"" << jsonEscape(c.getCourseCode()) << "\","
                 << "\"courseName\":\"" << jsonEscape(c.getCourseName()) << "\","
                 << "\"credits\":" << c.getCredits() << ","
                 << "\"department\":\"" << jsonEscape(c.getDepartment()) << "\","
                 << "\"professorId\":" << c.getProfessorId() << ","
                 << "\"enrollmentCount\":" << c.getEnrollmentCount()
                 << "}" << (i + 1 < courses.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "facilities") {
        cout << "[";
        for (size_t i = 0; i < facilities.size(); ++i) {
            const auto& f = facilities[i];
            double util = analyticsManager.calculateFacilityUtilization(f->getFacilityId(), bookingManager, timetableManager, eventManager);
            cout << "{"
                 << "\"facilityId\":" << f->getFacilityId() << ","
                 << "\"type\":\"" << jsonEscape(f->getType()) << "\","
                 << "\"name\":\"" << jsonEscape(f->getName()) << "\","
                 << "\"location\":\"" << jsonEscape(f->getLocation()) << "\","
                 << "\"capacity\":" << f->getCapacity() << ","
                 << "\"available\":" << (f->isAvailable() ? "true" : "false") << ","
                 << "\"utilization\":" << util << ","
                 << "\"status\":\"" << jsonEscape(analyticsManager.getUtilizationStatus(util)) << "\""
                 << "}" << (i + 1 < facilities.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "bookings") {
        const auto& bookings = bookingManager.getAllBookings();
        cout << "[";
        for (size_t i = 0; i < bookings.size(); ++i) {
            const auto& b = bookings[i];
            cout << "{"
                 << "\"bookingId\":" << b.getBookingId() << ","
                 << "\"facilityId\":" << b.getFacilityId() << ","
                 << "\"bookedByPersonId\":" << b.getBookedByPersonId() << ","
                 << "\"date\":\"" << jsonEscape(b.getDate()) << "\","
                 << "\"startTime\":\"" << jsonEscape(b.getStartTime()) << "\","
                 << "\"endTime\":\"" << jsonEscape(b.getEndTime()) << "\","
                 << "\"duration\":" << b.getDurationInHours() << ","
                 << "\"purpose\":\"" << jsonEscape(b.getPurpose()) << "\","
                 << "\"status\":\"" << jsonEscape(b.getStatus()) << "\""
                 << "}" << (i + 1 < bookings.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "timetable") {
        const auto& entries = timetableManager.getAllEntries();
        cout << "[";
        for (size_t i = 0; i < entries.size(); ++i) {
            const auto& t = entries[i];
            cout << "{"
                 << "\"entryId\":" << t.getEntryId() << ","
                 << "\"courseId\":" << t.getCourseId() << ","
                 << "\"professorId\":" << t.getProfessorId() << ","
                 << "\"facilityId\":" << t.getFacilityId() << ","
                 << "\"day\":\"" << jsonEscape(t.getDay()) << "\","
                 << "\"startTime\":\"" << jsonEscape(t.getStartTime()) << "\","
                 << "\"endTime\":\"" << jsonEscape(t.getEndTime()) << "\","
                 << "\"division\":\"" << jsonEscape(t.getDivision()) << "\","
                 << "\"year\":" << t.getYear()
                 << "}" << (i + 1 < entries.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "events") {
        const auto& evList = eventManager.getAllEvents();
        cout << "[";
        for (size_t i = 0; i < evList.size(); ++i) {
            const auto* e = evList[i].get();
            cout << "{"
                 << "\"eventId\":" << e->getEventId() << ","
                 << "\"type\":\"" << jsonEscape(e->getType()) << "\","
                 << "\"eventName\":\"" << jsonEscape(e->getEventName()) << "\","
                 << "\"description\":\"" << jsonEscape(e->getDescription()) << "\","
                 << "\"date\":\"" << jsonEscape(e->getDate()) << "\","
                 << "\"startTime\":\"" << jsonEscape(e->getStartTime()) << "\","
                 << "\"endTime\":\"" << jsonEscape(e->getEndTime()) << "\","
                 << "\"facilityId\":" << e->getFacilityId() << ","
                 << "\"organizerId\":" << e->getOrganizerId() << ","
                 << "\"participantCount\":" << e->getParticipantCount() << ","
                 << "\"maxParticipants\":" << e->getMaxParticipants()
                 << "}" << (i + 1 < evList.size() ? "," : "");
        }
        cout << "]" << endl;
        return 0;
    }

    if (cmd == "analytics") {
        // Build per-facility utilization array
        cout << "{\"baselineHours\":60.0,\"facilities\":[";
        for (size_t i = 0; i < facilities.size(); ++i) {
            const auto& f = facilities[i];
            double util = analyticsManager.calculateFacilityUtilization(f->getFacilityId(), bookingManager, timetableManager, eventManager);
            double bookedHrs = analyticsManager.calculateBookedHours(f->getFacilityId(), bookingManager, timetableManager, eventManager);
            cout << "{"
                 << "\"facilityId\":" << f->getFacilityId() << ","
                 << "\"name\":\"" << jsonEscape(f->getName()) << "\","
                 << "\"type\":\"" << jsonEscape(f->getType()) << "\","
                 << "\"utilization\":" << util << ","
                 << "\"bookedHours\":" << bookedHrs << ","
                 << "\"status\":\"" << jsonEscape(analyticsManager.getUtilizationStatus(util)) << "\""
                 << "}" << (i + 1 < facilities.size() ? "," : "");
        }
        auto recs = analyticsManager.generateRecommendations(bookingManager, timetableManager, eventManager, facilities);
        cout << "],\"recommendations\":[";
        for (size_t i = 0; i < recs.size(); ++i) {
            cout << "\"" << jsonEscape(recs[i]) << "\"" << (i + 1 < recs.size() ? "," : "");
        }
        cout << "]}" << endl;
        return 0;
    }

    // MUTATION COMMANDS
    bool mutated = false;

    if (cmd == "add_student" && argc >= 10) {
        int id = stoi(argv[3]);
        string name = argv[4];
        string email = argv[5];
        string phone = argv[6];
        string branch = argv[7];
        int year = stoi(argv[8]);
        string div = argv[9];

        students.emplace_back(id, name, email, phone, branch, year, div);
        mutated = true;
        cout << "{\"success\":true,\"message\":\"Student added successfully.\"}" << endl;
    }
    else if (cmd == "add_professor" && argc >= 9) {
        int id = stoi(argv[3]);
        string name = argv[4];
        string email = argv[5];
        string phone = argv[6];
        string dept = argv[7];
        string desig = argv[8];

        professors.emplace_back(id, name, email, phone, dept, desig);
        mutated = true;
        cout << "{\"success\":true,\"message\":\"Professor added successfully.\"}" << endl;
    }
    else if (cmd == "add_staff" && argc >= 9) {
        int id = stoi(argv[3]);
        string name = argv[4];
        string email = argv[5];
        string phone = argv[6];
        string dept = argv[7];
        string desig = argv[8];

        staff.emplace_back(id, name, email, phone, dept, desig);
        mutated = true;
        cout << "{\"success\":true,\"message\":\"Staff added successfully.\"}" << endl;
    }
    else if (cmd == "add_course" && argc >= 8) {
        int id = stoi(argv[3]);
        string code = argv[4];
        string name = argv[5];
        int credits = stoi(argv[6]);
        string dept = argv[7];

        courseManager.addCourse(Course(id, code, name, credits, dept));
        mutated = true;
        cout << "{\"success\":true,\"message\":\"Course added successfully.\"}" << endl;
    }
    else if (cmd == "enroll_student" && argc >= 5) {
        int courseId = stoi(argv[3]);
        int studentId = stoi(argv[4]);

        auto it = find_if(students.begin(), students.end(), [studentId](const Student& st) { return st.getId() == studentId; });
        if (it != students.end()) {
            bool ok = courseManager.enrollStudent(courseId, *it);
            if (ok) {
                mutated = true;
                cout << "{\"success\":true,\"message\":\"Student enrolled in course successfully.\"}" << endl;
            } else {
                cout << "{\"success\":false,\"message\":\"Enrollment failed or student already enrolled.\"}" << endl;
            }
        } else {
            cout << "{\"success\":false,\"message\":\"Student ID not found.\"}" << endl;
        }
    }
    else if (cmd == "assign_professor" && argc >= 5) {
        int courseId = stoi(argv[3]);
        int profId = stoi(argv[4]);

        auto it = find_if(professors.begin(), professors.end(), [profId](const Professor& pr) { return pr.getId() == profId; });
        if (it != professors.end()) {
            bool ok = courseManager.assignProfessor(courseId, *it);
            if (ok) {
                mutated = true;
                cout << "{\"success\":true,\"message\":\"Professor assigned to course successfully.\"}" << endl;
            } else {
                cout << "{\"success\":false,\"message\":\"Assignment failed or professor already assigned.\"}" << endl;
            }
        } else {
            cout << "{\"success\":false,\"message\":\"Professor ID not found.\"}" << endl;
        }
    }
    else if (cmd == "create_booking" && argc >= 10) {
        int id = stoi(argv[3]);
        int facId = stoi(argv[4]);
        int personId = stoi(argv[5]);
        string date = argv[6];
        string start = argv[7];
        string end = argv[8];
        string purpose = argv[9];

        try {
            Booking b(id, facId, personId, date, start, end, purpose);
            bool ok = bookingManager.createBooking(b);
            if (ok) {
                mutated = true;
                cout << "{\"success\":true,\"message\":\"Facility booking created successfully.\"}" << endl;
            } else {
                cout << "{\"success\":false,\"message\":\"Booking conflict: Facility is already occupied during this time.\"}" << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "{\"success\":false,\"message\":\"" << jsonEscape(e.what()) << "\"}" << endl;
        }
    }
    else if (cmd == "cancel_booking" && argc >= 4) {
        int id = stoi(argv[3]);
        bool ok = bookingManager.cancelBooking(id);
        if (ok) {
            mutated = true;
            cout << "{\"success\":true,\"message\":\"Booking cancelled successfully.\"}" << endl;
        } else {
            cout << "{\"success\":false,\"message\":\"Booking cancellation failed or not found.\"}" << endl;
        }
    }
    else if (cmd == "add_timetable" && argc >= 12) {
        int id = stoi(argv[3]);
        int courseId = stoi(argv[4]);
        int profId = stoi(argv[5]);
        int facId = stoi(argv[6]);
        string day = argv[7];
        string start = argv[8];
        string end = argv[9];
        string div = argv[10];
        int year = stoi(argv[11]);

        try {
            TimetableEntry t(id, courseId, profId, facId, day, start, end, div, year);
            bool ok = timetableManager.addEntry(t);
            if (ok) {
                mutated = true;
                cout << "{\"success\":true,\"message\":\"Timetable entry added successfully.\"}" << endl;
            } else {
                cout << "{\"success\":false,\"message\":\"Timetable conflict detected for professor, facility, or class section.\"}" << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "{\"success\":false,\"message\":\"" << jsonEscape(e.what()) << "\"}" << endl;
        }
    }
    else if (cmd == "create_event" && argc >= 11) {
        int id = stoi(argv[3]);
        string type = argv[4];
        string name = argv[5];
        string desc = argv[6];
        string date = argv[7];
        string start = argv[8];
        string end = argv[9];
        int facId = stoi(argv[10]);
        int orgId = (argc >= 12) ? stoi(argv[11]) : 101;
        int maxP = (argc >= 13) ? stoi(argv[12]) : 50;
        string e1 = (argc >= 14) ? argv[13] : "General";
        string e2 = (argc >= 15) ? argv[14] : "N/A";

        try {
            unique_ptr<Event> ev;
            if (type == "Workshop") ev = make_unique<Workshop>(id, name, desc, date, start, end, facId, orgId, maxP, e1, e2);
            else if (type == "Sports Event") ev = make_unique<SportsEvent>(id, name, desc, date, start, end, facId, orgId, maxP, e1, e2);
            else if (type == "Cultural Event") ev = make_unique<CulturalEvent>(id, name, desc, date, start, end, facId, orgId, maxP, e1);
            else ev = make_unique<TechnicalEvent>(id, name, desc, date, start, end, facId, orgId, maxP, e1, e2);

            bool ok = eventManager.addEvent(move(ev));
            if (ok) {
                mutated = true;
                cout << "{\"success\":true,\"message\":\"Event created successfully.\"}" << endl;
            } else {
                cout << "{\"success\":false,\"message\":\"Event creation failed due to duplicate ID or facility conflict.\"}" << endl;
            }
        } catch (const invalid_argument& e) {
            cout << "{\"success\":false,\"message\":\"" << jsonEscape(e.what()) << "\"}" << endl;
        }
    }
    else if (cmd == "register_event" && argc >= 5) {
        int eventId = stoi(argv[3]);
        int studentId = stoi(argv[4]);

        bool ok = eventManager.registerParticipant(eventId, studentId);
        if (ok) {
            mutated = true;
            cout << "{\"success\":true,\"message\":\"Participant registered for event successfully.\"}" << endl;
        } else {
            cout << "{\"success\":false,\"message\":\"Registration failed: Event is full or participant already registered.\"}" << endl;
        }
    }

    if (mutated) {
        FileManager::saveAllData(dataDir, students, professors, staff, facilities,
                                 courseManager, bookingManager, timetableManager, eventManager);
    }

    return 0;
}
