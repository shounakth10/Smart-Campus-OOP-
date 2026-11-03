#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include "../utils/DateTimeUtils.h"

using namespace std;

class Booking {
private:
    int bookingId;
    int facilityId;
    int bookedByPersonId;
    string date;
    string startTime;
    string endTime;
    string purpose;
    string status;

public:
    Booking();
    Booking(int bookingId, int facilityId, int bookedByPersonId, const string& date,
            const string& startTime, const string& endTime, const string& purpose,
            const string& status = "Confirmed");

    int getBookingId() const;
    int getFacilityId() const;
    int getBookedByPersonId() const;
    string getDate() const;
    string getStartTime() const;
    string getEndTime() const;
    string getPurpose() const;
    string getStatus() const;

    void setFacilityId(int facilityId);
    void setBookedByPersonId(int personId);
    void setDate(const string& date);
    void setTime(const string& startTime, const string& endTime);
    void setPurpose(const string& purpose);
    void setStatus(const string& status);

    double getDurationInHours() const;
    void cancelBooking();
    bool isActive() const;
    void display() const;
};
