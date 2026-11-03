# SmartCampus – University Management & Resource Planning System

A comprehensive, modular Object-Oriented Programming (OOP) core written in C++ (C++17 standard compliant).

---

## 📌 Implemented Modules

### 1. Person Management Module
- **`Person`**: Base class representing campus individuals (`id`, `name`, `email`, `phone`, `display()`, `getRole()`).
- **`Student`**: Derived from `Person`, includes `branch`, `year`, `division`, `courseIds`, `addCourse()`, `removeCourse()`, `displayCourses()`.
- **`Professor`**: Derived from `Person`, includes `department`, `designation`, `courseIds`, `assignCourse()`, `removeCourse()`, `displayCourses()`.
- **`Staff`**: Derived from `Person`, includes `department`, `designation`, and role identification.

### 2. Facility Management Module
- **`Facility`**: Base class representing campus venues (`facilityId`, `name`, `location`, `capacity`, `available`).
- **`Classroom`**: Derived from `Facility`, adds `building`, `floor`, `hasProjector`.
- **`Lab`**: Derived from `Facility`, adds `labType`, `computerCount`, `hasEquipment`.
- **`Auditorium`**: Derived from `Facility`, adds `hasStage`, `hasSoundSystem`.
- **`SportsGround`**: Derived from `Facility`, adds `sportType`, `surfaceType`.

### 3. Course Management Module
- **`Course`**: Model representing academic courses (`courseId`, `courseCode`, `courseName`, `credits`, `department`, `professorId`, `enrolledStudentIds`).
- **`CourseManager`**: Business-logic manager handling course catalog, professor allocation, student enrollment, duplicate prevention, and bidirectional relationship synchronization.

### 4. Booking Management Module
- **`Booking`**: Model representing facility reservations (`bookingId`, `facilityId`, `bookedByPersonId`, `date`, `startTime`, `endTime`, `purpose`, `status`).
- **`BookingManager`**: Handles facility booking requests, duration calculation, cancellation, and time-overlap conflict prevention.
- **`DateTimeUtils`**: Shared utility class for 24-hour time parsing (`HH:MM`), validation, duration calculation, and time interval overlap checks.

### 5. Timetable Management Module
- **`TimetableEntry`**: Model representing lecture schedules (`entryId`, `courseId`, `professorId`, `facilityId`, `day`, `startTime`, `endTime`, `division`, `year`).
- **`TimetableManager`**: Master schedule coordinator preventing professor, facility, and class section time conflicts.

### 6. Event Management Module
- **`Event`**: Polymorphic base class for campus events (`eventId`, `eventName`, `description`, `date`, `startTime`, `endTime`, `facilityId`, `organizerId`, `maxParticipants`, `participantIds`).
- **Derived Event Classes**: `Workshop`, `SportsEvent`, `CulturalEvent`, `TechnicalEvent`.
- **`EventManager`**: Manages event catalog via `std::vector<std::unique_ptr<Event>>`, enforces registration capacity limits, prevents duplicate participant registration, and blocks facility schedule conflicts.

### 7. Analytics & Facility Utilization Module
- **`AnalyticsManager`**: Calculates resource metrics, utilization percentages, and rule-based recommendations.
- **Utilization Formula**:
  $$\text{Utilization } (\%) = \left( \frac{\text{Total Booked Hours}}{\text{Total Available Hours}} \right) \times 100$$
- **Utilization Categories**:
  - `0 – 30%`: Underutilized
  - `31 – 70%`: Normal
  - `71 – 90%`: Highly Utilized
  - `91 – 100%+`: Overloaded
- **Dashboard Statistics**: Aggregates total students, professors, staff, courses, facilities, active bookings, timetable entries, and recommendations.

### 8. CSV Persistence Module
- **`FileManager`**: Custom standard C++ file I/O helper using `<fstream>` and `<sstream>`.
- **`saveAllData()` & `loadAllData()`**: Explicit methods for serializing system state into CSV files under `data/` and reconstructing complete object hierarchies upon startup.

---

## 🛠️ Build & Run Instructions

### Compilation Command

```bash
g++ -std=c++17 \
cpp/main.cpp \
cpp/models/Person.cpp \
cpp/models/Student.cpp \
cpp/models/Professor.cpp \
cpp/models/Staff.cpp \
cpp/models/Facility.cpp \
cpp/models/Classroom.cpp \
cpp/models/Lab.cpp \
cpp/models/Auditorium.cpp \
cpp/models/SportsGround.cpp \
cpp/models/Course.cpp \
cpp/models/Booking.cpp \
cpp/models/TimetableEntry.cpp \
cpp/models/Event.cpp \
cpp/models/Workshop.cpp \
cpp/models/SportsEvent.cpp \
cpp/models/CulturalEvent.cpp \
cpp/models/TechnicalEvent.cpp \
cpp/managers/CourseManager.cpp \
cpp/managers/BookingManager.cpp \
cpp/managers/TimetableManager.cpp \
cpp/managers/EventManager.cpp \
cpp/managers/AnalyticsManager.cpp \
cpp/utils/DateTimeUtils.cpp \
cpp/utils/FileManager.cpp \
cpp/utils/CLIHandler.cpp \
-o SmartCampus.exe
```

### Execution Command

```bash
./SmartCampus.exe
```

### Web App Execution

```bash
pip install -r requirements.txt
python flask/app.py
```

Then open: http://127.0.0.1:5000
