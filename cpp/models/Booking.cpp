#include "Booking.h"

using namespace std;

Booking::Booking()
    : bookingId(0), facilityId(0), bookedByPersonId(0), date(""), startTime("00:00"),
      endTime("00:00"), purpose(""), status("Confirmed") {}

Booking::Booking(int bookingId, int facilityId, int bookedByPersonId, const string& date,
                 const string& startTime, const string& endTime, const string& purpose,
                 const string& status)
    : bookingId(bookingId), facilityId(facilityId), bookedByPersonId(bookedByPersonId),
      date(date), startTime(startTime), endTime(endTime), purpose(purpose), status(status) {
    if (bookingId <= 0) {
        throw invalid_argument("Booking ID must be positive.");
    }
    if (facilityId <= 0) {
        throw invalid_argument("Facility ID must be positive.");
    }
    if (bookedByPersonId <= 0) {
        throw invalid_argument("Person ID must be positive.");
    }
    if (date.empty()) {
        throw invalid_argument("Date cannot be empty.");
    }
    if (!DateTimeUtils::isValidTime(startTime) || !DateTimeUtils::isValidTime(endTime)) {
        throw invalid_argument("Invalid time format. Use HH:MM.");
    }
    if (DateTimeUtils::timeToMinutes(endTime) <= DateTimeUtils::timeToMinutes(startTime)) {
        throw invalid_argument("End time must be strictly after start time.");
    }
}

int Booking::getBookingId() const { return bookingId; }
int Booking::getFacilityId() const { return facilityId; }
int Booking::getBookedByPersonId() const { return bookedByPersonId; }
string Booking::getDate() const { return date; }
string Booking::getStartTime() const { return startTime; }
string Booking::getEndTime() const { return endTime; }
string Booking::getPurpose() const { return purpose; }
string Booking::getStatus() const { return status; }

void Booking::setFacilityId(int facilityId) {
    if (facilityId <= 0) throw invalid_argument("Facility ID must be positive.");
    this->facilityId = facilityId;
}

void Booking::setBookedByPersonId(int personId) {
    if (personId <= 0) throw invalid_argument("Person ID must be positive.");
    this->bookedByPersonId = personId;
}

void Booking::setDate(const string& date) {
    if (date.empty()) throw invalid_argument("Date cannot be empty.");
    this->date = date;
}

void Booking::setTime(const string& startTime, const string& endTime) {
    if (!DateTimeUtils::isValidTime(startTime) || !DateTimeUtils::isValidTime(endTime)) {
        throw invalid_argument("Invalid time format. Use HH:MM.");
    }
    if (DateTimeUtils::timeToMinutes(endTime) <= DateTimeUtils::timeToMinutes(startTime)) {
        throw invalid_argument("End time must be strictly after start time.");
    }
    this->startTime = startTime;
    this->endTime = endTime;
}

void Booking::setPurpose(const string& purpose) { this->purpose = purpose; }
void Booking::setStatus(const string& status) { this->status = status; }

double Booking::getDurationInHours() const {
    return DateTimeUtils::calculateDuration(startTime, endTime);
}

void Booking::cancelBooking() {
    this->status = "Cancelled";
}

bool Booking::isActive() const {
    return status == "Confirmed";
}

void Booking::display() const {
    cout << "Booking ID: " << bookingId << endl;
    cout << "Facility ID: " << facilityId << endl;
    cout << "Booked By Person ID: " << bookedByPersonId << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << startTime << " - " << endTime
         << " (Duration: " << getDurationInHours() << " hrs)" << endl;
    cout << "Purpose: " << purpose << endl;
    cout << "Status: " << status << endl;
}
