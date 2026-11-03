#include "BookingManager.h"
#include <iostream>

using namespace std;

BookingManager::BookingManager() {}
BookingManager::~BookingManager() {}

bool BookingManager::createBooking(const Booking& booking) {
    if (findBooking(booking.getBookingId()) != nullptr) {
        cout << "[BookingManager] Conflict rejected: Booking ID " << booking.getBookingId()
             << " already exists!" << endl;
        return false;
    }
    if (!DateTimeUtils::isValidTime(booking.getStartTime()) || !DateTimeUtils::isValidTime(booking.getEndTime())) {
        cout << "[BookingManager] Conflict rejected: Invalid time format for booking ID " << booking.getBookingId() << endl;
        return false;
    }
    if (DateTimeUtils::timeToMinutes(booking.getEndTime()) <= DateTimeUtils::timeToMinutes(booking.getStartTime())) {
        cout << "[BookingManager] Conflict rejected: End time must be after start time for booking ID " << booking.getBookingId() << endl;
        return false;
    }
    if (!isFacilityAvailable(booking.getFacilityId(), booking.getDate(), booking.getStartTime(), booking.getEndTime())) {
        cout << "[BookingManager] Conflict rejected: Facility ID " << booking.getFacilityId()
             << " is already booked for " << booking.getDate() << " (" << booking.getStartTime()
             << " - " << booking.getEndTime() << ")." << endl;
        return false;
    }
    bookings.push_back(booking);
    cout << "[BookingManager] Successfully created Booking ID " << booking.getBookingId() << endl;
    return true;
}

bool BookingManager::cancelBooking(int bookingId) {
    Booking* b = findBooking(bookingId);
    if (b != nullptr && b->isActive()) {
        b->cancelBooking();
        cout << "[BookingManager] Booking ID " << bookingId << " has been cancelled." << endl;
        return true;
    }
    cout << "[BookingManager] Cancel failed: Booking ID " << bookingId << " not found or already cancelled." << endl;
    return false;
}

Booking* BookingManager::findBooking(int bookingId) {
    for (auto& b : bookings) {
        if (b.getBookingId() == bookingId) return &b;
    }
    return nullptr;
}

const Booking* BookingManager::findBooking(int bookingId) const {
    for (const auto& b : bookings) {
        if (b.getBookingId() == bookingId) return &b;
    }
    return nullptr;
}

bool BookingManager::isFacilityAvailable(int facilityId, const string& date,
                                       const string& startTime, const string& endTime) const {
    for (const auto& b : bookings) {
        if (b.getFacilityId() == facilityId && b.getDate() == date && b.isActive()) {
            if (DateTimeUtils::isTimeOverlap(b.getStartTime(), b.getEndTime(), startTime, endTime)) {
                return false;
            }
        }
    }
    return true;
}

vector<Booking> BookingManager::getFacilityBookings(int facilityId) const {
    vector<Booking> result;
    for (const auto& b : bookings) {
        if (b.getFacilityId() == facilityId) result.push_back(b);
    }
    return result;
}

vector<Booking> BookingManager::getBookingsForDate(const string& date) const {
    vector<Booking> result;
    for (const auto& b : bookings) {
        if (b.getDate() == date) result.push_back(b);
    }
    return result;
}

const vector<Booking>& BookingManager::getAllBookings() const {
    return bookings;
}

void BookingManager::displayAllBookings() const {
    cout << "=== Facility Bookings Catalog (" << bookings.size() << " Bookings) ===" << endl;
    for (const auto& b : bookings) {
        b.display();
        cout << "--------------------------------" << endl;
    }
}
