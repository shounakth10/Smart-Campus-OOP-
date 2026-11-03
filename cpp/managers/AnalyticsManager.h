#pragma once

#include "../models/Facility.h"
#include "../models/Student.h"
#include "../models/Professor.h"
#include "../models/Staff.h"
#include "../models/Course.h"
#include "../models/Booking.h"
#include "../models/TimetableEntry.h"
#include "../models/Event.h"

#include "BookingManager.h"
#include "TimetableManager.h"
#include "CourseManager.h"
#include "EventManager.h"

#include <vector>
#include <string>
#include <memory>

using namespace std;

struct DashboardStats {
    int totalStudents;
    int totalProfessors;
    int totalStaff;
    int totalCourses;
    int totalFacilities;
    int totalBookings;
    int activeBookings;
    int totalTimetableEntries;
    int totalEvents;
    int totalEventParticipants;
    double averageFacilityUtilization;
    string mostUtilizedFacility;
    int underutilizedFacilityCount;
};

class AnalyticsManager {
private:
    double weeklyAvailableHours;

public:
    AnalyticsManager(double weeklyAvailableHours = 40.0);
    ~AnalyticsManager();

    double getWeeklyAvailableHours() const;
    void setWeeklyAvailableHours(double hours);

    double calculateBookedHours(int facilityId, const BookingManager& bm,
                               const TimetableManager& tm, const EventManager& em) const;

    double calculateAvailableHours(int facilityId) const;

    double calculateFacilityUtilization(int facilityId, const BookingManager& bm,
                                         const TimetableManager& tm, const EventManager& em) const;

    string getUtilizationStatus(double percentage) const;

    vector<int> getMostUsedFacilities(const BookingManager& bm, const TimetableManager& tm,
                                     const EventManager& em, const vector<unique_ptr<Facility>>& facilities) const;

    vector<int> getUnderutilizedFacilities(const BookingManager& bm, const TimetableManager& tm,
                                          const EventManager& em, const vector<unique_ptr<Facility>>& facilities) const;

    vector<string> generateRecommendations(const BookingManager& bm, const TimetableManager& tm,
                                           const EventManager& em, const vector<unique_ptr<Facility>>& facilities) const;

    DashboardStats getDashboardStatistics(const vector<Student>& students,
                                           const vector<Professor>& professors,
                                           const vector<Staff>& staff,
                                           const CourseManager& cm,
                                           const vector<unique_ptr<Facility>>& facilities,
                                           const BookingManager& bm,
                                           const TimetableManager& tm,
                                           const EventManager& em) const;

    void displayDashboard(const vector<Student>& students,
                          const vector<Professor>& professors,
                          const vector<Staff>& staff,
                          const CourseManager& cm,
                          const vector<unique_ptr<Facility>>& facilities,
                          const BookingManager& bm,
                          const TimetableManager& tm,
                          const EventManager& em) const;
};
