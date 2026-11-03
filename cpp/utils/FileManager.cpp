#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Helper to serialize vector<int> to string "101;102;103"
static string serializeIds(const vector<int>& ids) {
    string res = "";
    for (size_t i = 0; i < ids.size(); ++i) {
        res += to_string(ids[i]) + (i + 1 < ids.size() ? ";" : "");
    }
    return res;
}

// Helper to deserialize "101;102;103" to vector<int>
static vector<int> deserializeIds(const string& str) {
    vector<int> res;
    if (str.empty()) return res;
    stringstream ss(str);
    string token;
    while (getline(ss, token, ';')) {
        if (!token.empty()) {
            try {
                res.push_back(stoi(token));
            } catch (...) {}
        }
    }
    return res;
}

// ============================================================================
// STUDENTS PERSISTENCE
// ============================================================================
bool FileManager::saveStudents(const string& filepath, const vector<Student>& students) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "id,name,email,phone,branch,year,division,courseIds\n";
    for (const auto& s : students) {
        file << s.getId() << ","
             << s.getName() << ","
             << s.getEmail() << ","
             << s.getPhone() << ","
             << s.getBranch() << ","
             << s.getYear() << ","
             << s.getDivision() << ","
             << serializeIds(s.getCourseIds()) << "\n";
    }
    file.close();
    return true;
}

vector<Student> FileManager::loadStudents(const string& filepath) {
    vector<Student> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, email, phone, branch, yearStr, division, coursesStr;

        if (getline(ss, idStr, ',') &&
            getline(ss, name, ',') &&
            getline(ss, email, ',') &&
            getline(ss, phone, ',') &&
            getline(ss, branch, ',') &&
            getline(ss, yearStr, ',') &&
            getline(ss, division, ',')) {

            getline(ss, coursesStr); // Optional last field
            try {
                int id = stoi(idStr);
                int year = stoi(yearStr);
                Student s(id, name, email, phone, branch, year, division);
                vector<int> cIds = deserializeIds(coursesStr);
                for (int cId : cIds) s.addCourse(cId);
                result.push_back(s);
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// PROFESSORS PERSISTENCE
// ============================================================================
bool FileManager::saveProfessors(const string& filepath, const vector<Professor>& professors) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "id,name,email,phone,department,designation,courseIds\n";
    for (const auto& p : professors) {
        file << p.getId() << ","
             << p.getName() << ","
             << p.getEmail() << ","
             << p.getPhone() << ","
             << p.getDepartment() << ","
             << p.getDesignation() << ","
             << serializeIds(p.getCourseIds()) << "\n";
    }
    file.close();
    return true;
}

vector<Professor> FileManager::loadProfessors(const string& filepath) {
    vector<Professor> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, email, phone, dept, desig, coursesStr;

        if (getline(ss, idStr, ',') &&
            getline(ss, name, ',') &&
            getline(ss, email, ',') &&
            getline(ss, phone, ',') &&
            getline(ss, dept, ',') &&
            getline(ss, desig, ',')) {

            getline(ss, coursesStr);
            try {
                int id = stoi(idStr);
                Professor p(id, name, email, phone, dept, desig);
                vector<int> cIds = deserializeIds(coursesStr);
                for (int cId : cIds) p.assignCourse(cId);
                result.push_back(p);
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// STAFF PERSISTENCE
// ============================================================================
bool FileManager::saveStaff(const string& filepath, const vector<Staff>& staff) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "id,name,email,phone,department,designation\n";
    for (const auto& st : staff) {
        file << st.getId() << ","
             << st.getName() << ","
             << st.getEmail() << ","
             << st.getPhone() << ","
             << st.getDepartment() << ","
             << st.getDesignation() << "\n";
    }
    file.close();
    return true;
}

vector<Staff> FileManager::loadStaff(const string& filepath) {
    vector<Staff> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, email, phone, dept, desig;

        if (getline(ss, idStr, ',') &&
            getline(ss, name, ',') &&
            getline(ss, email, ',') &&
            getline(ss, phone, ',') &&
            getline(ss, dept, ',') &&
            getline(ss, desig, ',')) {

            try {
                result.emplace_back(stoi(idStr), name, email, phone, dept, desig);
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// FACILITIES PERSISTENCE
// ============================================================================
bool FileManager::saveFacilities(const string& filepath, const vector<unique_ptr<Facility>>& facilities) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "facilityId,type,name,location,capacity,available,extra1,extra2,extra3\n";
    for (const auto& f : facilities) {
        file << f->getFacilityId() << ","
             << f->getType() << ","
             << f->getName() << ","
             << f->getLocation() << ","
             << f->getCapacity() << ","
             << (f->isAvailable() ? "1" : "0") << ",";

        if (f->getType() == "Classroom") {
            const Classroom* c = dynamic_cast<const Classroom*>(f.get());
            if (c) file << c->getBuilding() << "," << c->getFloor() << "," << (c->hasProjectorAvailable() ? "1" : "0");
        } else if (f->getType() == "Lab") {
            const Lab* l = dynamic_cast<const Lab*>(f.get());
            if (l) file << l->getLabType() << "," << l->getComputerCount() << "," << (l->getHasEquipment() ? "1" : "0");
        } else if (f->getType() == "Auditorium") {
            const Auditorium* a = dynamic_cast<const Auditorium*>(f.get());
            if (a) file << (a->getHasStage() ? "1" : "0") << "," << (a->getHasSoundSystem() ? "1" : "0") << ",N/A";
        } else if (f->getType() == "Sports Ground") {
            const SportsGround* s = dynamic_cast<const SportsGround*>(f.get());
            if (s) file << s->getSportType() << "," << s->getSurfaceType() << ",N/A";
        }
        file << "\n";
    }
    file.close();
    return true;
}

vector<unique_ptr<Facility>> FileManager::loadFacilities(const string& filepath) {
    vector<unique_ptr<Facility>> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, type, name, loc, capStr, availStr, e1, e2, e3;

        if (getline(ss, idStr, ',') &&
            getline(ss, type, ',') &&
            getline(ss, name, ',') &&
            getline(ss, loc, ',') &&
            getline(ss, capStr, ',') &&
            getline(ss, availStr, ',')) {

            getline(ss, e1, ',');
            getline(ss, e2, ',');
            getline(ss, e3);

            try {
                int id = stoi(idStr);
                int cap = stoi(capStr);
                bool avail = (availStr == "1" || availStr == "true");

                if (type == "Classroom") {
                    result.push_back(unique_ptr<Facility>(new Classroom(id, name, loc, cap, e1, stoi(e2), (e3 == "1"), avail)));
                } else if (type == "Lab") {
                    result.push_back(unique_ptr<Facility>(new Lab(id, name, loc, cap, e1, stoi(e2), (e3 == "1"), avail)));
                } else if (type == "Auditorium") {
                    result.push_back(unique_ptr<Facility>(new Auditorium(id, name, loc, cap, (e1 == "1"), (e2 == "1"), avail)));
                } else if (type == "Sports Ground") {
                    result.push_back(unique_ptr<Facility>(new SportsGround(id, name, loc, cap, e1, e2, avail)));
                }
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// COURSES PERSISTENCE
// ============================================================================
bool FileManager::saveCourses(const string& filepath, const vector<Course>& courses) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "courseId,courseCode,courseName,credits,department,professorId,enrolledStudentIds\n";
    for (const auto& c : courses) {
        file << c.getCourseId() << ","
             << c.getCourseCode() << ","
             << c.getCourseName() << ","
             << c.getCredits() << ","
             << c.getDepartment() << ","
             << c.getProfessorId() << ","
             << serializeIds(c.getEnrolledStudentIds()) << "\n";
    }
    file.close();
    return true;
}

vector<Course> FileManager::loadCourses(const string& filepath) {
    vector<Course> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, code, name, credStr, dept, profStr, studentsStr;

        if (getline(ss, idStr, ',') &&
            getline(ss, code, ',') &&
            getline(ss, name, ',') &&
            getline(ss, credStr, ',') &&
            getline(ss, dept, ',') &&
            getline(ss, profStr, ',')) {

            getline(ss, studentsStr);
            try {
                int cId = stoi(idStr);
                int cred = stoi(credStr);
                int pId = stoi(profStr);
                Course c(cId, code, name, cred, dept);
                if (pId > 0) c.assignProfessor(pId);
                vector<int> sIds = deserializeIds(studentsStr);
                for (int sId : sIds) c.enrollStudent(sId);
                result.push_back(c);
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// BOOKINGS PERSISTENCE
// ============================================================================
bool FileManager::saveBookings(const string& filepath, const vector<Booking>& bookings) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "bookingId,facilityId,bookedByPersonId,date,startTime,endTime,purpose,status\n";
    for (const auto& b : bookings) {
        file << b.getBookingId() << ","
             << b.getFacilityId() << ","
             << b.getBookedByPersonId() << ","
             << b.getDate() << ","
             << b.getStartTime() << ","
             << b.getEndTime() << ","
             << b.getPurpose() << ","
             << b.getStatus() << "\n";
    }
    file.close();
    return true;
}

vector<Booking> FileManager::loadBookings(const string& filepath) {
    vector<Booking> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string bId, fId, pId, date, start, end, purpose, status;

        if (getline(ss, bId, ',') &&
            getline(ss, fId, ',') &&
            getline(ss, pId, ',') &&
            getline(ss, date, ',') &&
            getline(ss, start, ',') &&
            getline(ss, end, ',') &&
            getline(ss, purpose, ',') &&
            getline(ss, status, ',')) {

            try {
                result.emplace_back(stoi(bId), stoi(fId), stoi(pId), date, start, end, purpose, status);
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// TIMETABLE PERSISTENCE
// ============================================================================
bool FileManager::saveTimetable(const string& filepath, const vector<TimetableEntry>& entries) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "entryId,courseId,professorId,facilityId,day,startTime,endTime,division,year\n";
    for (const auto& t : entries) {
        file << t.getEntryId() << ","
             << t.getCourseId() << ","
             << t.getProfessorId() << ","
             << t.getFacilityId() << ","
             << t.getDay() << ","
             << t.getStartTime() << ","
             << t.getEndTime() << ","
             << t.getDivision() << ","
             << t.getYear() << "\n";
    }
    file.close();
    return true;
}

vector<TimetableEntry> FileManager::loadTimetable(const string& filepath) {
    vector<TimetableEntry> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string eId, cId, pId, fId, day, start, end, div, yr;

        if (getline(ss, eId, ',') &&
            getline(ss, cId, ',') &&
            getline(ss, pId, ',') &&
            getline(ss, fId, ',') &&
            getline(ss, day, ',') &&
            getline(ss, start, ',') &&
            getline(ss, end, ',') &&
            getline(ss, div, ',') &&
            getline(ss, yr, ',')) {

            try {
                result.emplace_back(stoi(eId), stoi(cId), stoi(pId), stoi(fId),
                                   day, start, end, div, stoi(yr));
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// EVENTS PERSISTENCE
// ============================================================================
bool FileManager::saveEvents(const string& filepath, const vector<unique_ptr<Event>>& events) {
    ofstream file(filepath);
    if (!file.is_open()) return false;
    file << "eventId,type,eventName,description,date,startTime,endTime,facilityId,organizerId,maxParticipants,extra1,extra2,participantIds\n";
    for (const auto& e : events) {
        file << e->getEventId() << ","
             << e->getType() << ","
             << e->getEventName() << ","
             << e->getDescription() << ","
             << e->getDate() << ","
             << e->getStartTime() << ","
             << e->getEndTime() << ","
             << e->getFacilityId() << ","
             << e->getOrganizerId() << ","
             << e->getMaxParticipants() << ",";

        if (e->getType() == "Workshop") {
            const Workshop* w = dynamic_cast<const Workshop*>(e.get());
            if (w) file << w->getTopic() << "," << w->getInstructor() << ",";
        } else if (e->getType() == "Sports Event") {
            const SportsEvent* s = dynamic_cast<const SportsEvent*>(e.get());
            if (s) file << s->getSport() << "," << s->getLevel() << ",";
        } else if (e->getType() == "Cultural Event") {
            const CulturalEvent* c = dynamic_cast<const CulturalEvent*>(e.get());
            if (c) file << c->getCulturalCategory() << ",N/A,";
        } else if (e->getType() == "Technical Event") {
            const TechnicalEvent* t = dynamic_cast<const TechnicalEvent*>(e.get());
            if (t) file << t->getTechnology() << "," << t->getCompetitionType() << ",";
        }

        file << serializeIds(e->getParticipantIds()) << "\n";
    }
    file.close();
    return true;
}

vector<unique_ptr<Event>> FileManager::loadEvents(const string& filepath) {
    vector<unique_ptr<Event>> result;
    ifstream file(filepath);
    if (!file.is_open()) return result;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, type, name, desc, date, start, end, fId, orgId, maxP, e1, e2, pStr;

        if (getline(ss, idStr, ',') &&
            getline(ss, type, ',') &&
            getline(ss, name, ',') &&
            getline(ss, desc, ',') &&
            getline(ss, date, ',') &&
            getline(ss, start, ',') &&
            getline(ss, end, ',') &&
            getline(ss, fId, ',') &&
            getline(ss, orgId, ',') &&
            getline(ss, maxP, ',')) {

            getline(ss, e1, ',');
            getline(ss, e2, ',');
            getline(ss, pStr);

            try {
                int id = stoi(idStr);
                int facId = stoi(fId);
                int oId = stoi(orgId);
                int mP = stoi(maxP);

                unique_ptr<Event> ev;
                if (type == "Workshop") {
                    ev = unique_ptr<Event>(new Workshop(id, name, desc, date, start, end, facId, oId, mP, e1, e2));
                } else if (type == "Sports Event") {
                    ev = unique_ptr<Event>(new SportsEvent(id, name, desc, date, start, end, facId, oId, mP, e1, e2));
                } else if (type == "Cultural Event") {
                    ev = unique_ptr<Event>(new CulturalEvent(id, name, desc, date, start, end, facId, oId, mP, e1));
                } else if (type == "Technical Event") {
                    ev = unique_ptr<Event>(new TechnicalEvent(id, name, desc, date, start, end, facId, oId, mP, e1, e2));
                }

                if (ev) {
                    vector<int> pIds = deserializeIds(pStr);
                    for (int pId : pIds) ev->registerParticipant(pId);
                    result.push_back(move(ev));
                }
            } catch (...) {}
        }
    }
    file.close();
    return result;
}

// ============================================================================
// MASTER SAVE & LOAD
// ============================================================================
bool FileManager::saveAllData(const string& dataDir,
                            const vector<Student>& students,
                            const vector<Professor>& professors,
                            const vector<Staff>& staff,
                            const vector<unique_ptr<Facility>>& facilities,
                            const CourseManager& cm,
                            const BookingManager& bm,
                            const TimetableManager& tm,
                            const EventManager& em) {

    bool s1 = saveStudents(dataDir + "/students.csv", students);
    bool s2 = saveProfessors(dataDir + "/professors.csv", professors);
    bool s3 = saveStaff(dataDir + "/staff.csv", staff);
    bool s4 = saveFacilities(dataDir + "/facilities.csv", facilities);
    bool s5 = saveCourses(dataDir + "/courses.csv", cm.getAllCourses());
    bool s6 = saveBookings(dataDir + "/bookings.csv", bm.getAllBookings());
    bool s7 = saveTimetable(dataDir + "/timetable.csv", tm.getAllEntries());
    bool s8 = saveEvents(dataDir + "/events.csv", em.getAllEvents());

    return s1 && s2 && s3 && s4 && s5 && s6 && s7 && s8;
}

bool FileManager::loadAllData(const string& dataDir,
                            vector<Student>& students,
                            vector<Professor>& professors,
                            vector<Staff>& staff,
                            vector<unique_ptr<Facility>>& facilities,
                            CourseManager& cm,
                            BookingManager& bm,
                            TimetableManager& tm,
                            EventManager& em) {

    students = loadStudents(dataDir + "/students.csv");
    professors = loadProfessors(dataDir + "/professors.csv");
    staff = loadStaff(dataDir + "/staff.csv");
    facilities = loadFacilities(dataDir + "/facilities.csv");

    vector<Course> loadedCourses = loadCourses(dataDir + "/courses.csv");
    for (const auto& c : loadedCourses) cm.addCourse(c);

    vector<Booking> loadedBookings = loadBookings(dataDir + "/bookings.csv");
    for (const auto& b : loadedBookings) bm.createBooking(b);

    vector<TimetableEntry> loadedEntries = loadTimetable(dataDir + "/timetable.csv");
    for (const auto& t : loadedEntries) tm.addEntry(t);

    vector<unique_ptr<Event>> loadedEvents = loadEvents(dataDir + "/events.csv");
    for (auto& e : loadedEvents) em.addEvent(move(e));

    return true;
}
