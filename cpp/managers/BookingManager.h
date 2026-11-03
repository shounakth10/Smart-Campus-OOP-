#pragma once

#include "../models/Booking.h"
#include "../utils/DateTimeUtils.h"
#include <vector>

using namespace std;

class BookingManager {
private:
    vector<Booking> bookings;

public:
    BookingManager();
    ~BookingManager();

    bool createBooking(const Booking& booking);
    bool cancelBooking(int bookingId);

    Booking* findBooking(int bookingId);
    const Booking* findBooking(int bookingId) const;

    bool isFacilityAvailable(int facilityId, const string& date,
                            const string& startTime, const string& endTime) const;

    vector<Booking> getFacilityBookings(int facilityId) const;
    vector<Booking> getBookingsForDate(const string& date) const;
    const vector<Booking>& getAllBookings() const;

    void displayAllBookings() const;
};
