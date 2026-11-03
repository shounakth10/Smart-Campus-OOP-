# SmartCampus
## Object-Oriented Programming Project Report

### 1. Project Overview

SmartCampus is a college campus management and resource-planning system. Its C++ backend models people, courses, campus facilities, bookings, timetables, and events. A Flask application provides browser-based pages and forwards API requests to the C++ command-line backend. The system stores its records in CSV files under `data/`.

The project demonstrates how object-oriented programming can organize a real-world domain into classes with clear responsibilities, inheritance hierarchies, and manager classes that coordinate related objects.

### 2. Objectives

- Represent students, professors, staff, facilities, courses, bookings, timetable entries, and events as objects.
- Organize campus operations into modules with separate responsibilities.
- Avoid conflicting facility bookings, timetable entries, and event schedules.
- Support course enrollment, professor assignment, and event registration.
- Save and restore system records using CSV files.
- Present campus data through a Flask web interface and analytics dashboard.

### 3. Technologies

- **C++17:** Models, business rules, managers, persistence, and command interface.
- **Python and Flask:** Web pages and HTTP API routes.
- **HTML, CSS, and JavaScript:** Browser interface.
- **CSV:** Persistent data files in the `data/` directory.
- **g++:** C++ compiler used to build the backend executable.

### 4. System Architecture

The application has four main layers:

1. **Models** represent domain objects and their data, such as `Student`, `Course`, and `Booking`.
2. **Managers** coordinate collections and enforce operations such as enrollment and schedule-conflict checks.
3. **Utilities** handle CSV persistence, time calculations, and CLI/API command dispatch.
4. **Web interface** renders pages and calls Flask API routes, which invoke the C++ backend.

The high-level request flow is:

`Browser page → Flask route → C++ CLI command → manager/model → CSV data`

### 5. Class Explanations

#### People

- **`Person`** — Base class for people on campus. Stores an ID, name, email, and phone number. Its virtual `display()` and `getRole()` methods provide behavior that subclasses can specialize.
- **`Student`** — Inherits from `Person`. Adds a branch, year, division, and course IDs. Supports adding, removing, checking, and displaying course enrollments.
- **`Professor`** — Inherits from `Person`. Adds a department, designation, and course IDs. Supports assigning and removing courses and checking which courses the professor teaches.
- **`Staff`** — Inherits from `Person`. Adds a department and designation and provides staff-specific display and role behavior.

#### Facilities

- **`Facility`** — Base class for campus venues. Stores a facility ID, name, location, capacity, and availability. Virtual display and type methods support specialized facility behavior.
- **`Classroom`** — Inherits from `Facility`. Adds building, floor, and projector details.
- **`Lab`** — Inherits from `Facility`. Adds lab type, computer count, and equipment availability.
- **`Auditorium`** — Inherits from `Facility`. Adds stage and sound-system details.
- **`SportsGround`** — Inherits from `Facility`. Adds sport and surface types.

#### Academic and scheduling models

- **`Course`** — Stores a course ID, code, name, credits, department, professor ID, and enrolled student IDs. Supports professor assignment and student enrollment operations.
- **`Booking`** — Represents a facility reservation. Stores the facility, person making the booking, date, time range, purpose, and status. Provides duration, cancellation, and active-status operations.
- **`TimetableEntry`** — Represents one scheduled class with a course, professor, facility, day, time range, division, and year. Provides overlap and professor/facility/class conflict checks.

#### Events

- **`Event`** — Polymorphic base class for campus events. Stores event details, schedule, facility, organizer, participant limit, and participant IDs. Supports participant registration and capacity checks.
- **`Workshop`** — Inherits from `Event`. Adds a topic and instructor.
- **`SportsEvent`** — Inherits from `Event`. Adds the sport and competition level.
- **`CulturalEvent`** — Inherits from `Event`. Adds a cultural category.
- **`TechnicalEvent`** — Inherits from `Event`. Adds the technology and competition type.

#### Managers

- **`StudentManager`** — Holds students and provides add, remove, update, find, list, and display operations.
- **`FacilityManager`** — Holds shared facility objects and provides add, remove, find, availability, and listing operations.
- **`CourseManager`** — Holds courses and coordinates course creation/removal, professor assignment, and student enrollment. It synchronizes related course and person records.
- **`BookingManager`** — Holds bookings, checks facility availability for a time interval, creates and cancels bookings, and retrieves bookings by facility or date.
- **`TimetableManager`** — Holds timetable entries and provides add, edit, delete, lookup, timetable queries, and conflict checking.
- **`EventManager`** — Owns event objects through `unique_ptr<Event>`, manages event records, and handles participant registration and removal.
- **`AnalyticsManager`** — Calculates booked hours and facility utilization, classifies utilization levels, generates recommendations, and aggregates dashboard statistics.

#### Utilities and application entry points

- **`DateTimeUtils`** — Provides time validation, conversion to minutes, overlap checks, and duration calculations for `HH:MM` time values.
- **`FileManager`** — Loads and saves each model collection to CSV, including facilities and polymorphic event records, and provides combined load/save operations.
- **`CLIHandler`** — Handles backend commands used by the web API. It loads the CSV state, dispatches read or mutation commands, returns JSON, and saves state after successful mutations.
- **`main()`** — Starts the CLI handler for API commands or runs the standalone C++ demonstration program.

### 6. Object-Oriented Programming Concepts

- **Encapsulation:** Model fields are generally private or protected and accessed through methods.
- **Inheritance:** `Student`, `Professor`, and `Staff` derive from `Person`; facility types derive from `Facility`; event types derive from `Event`.
- **Polymorphism:** `display()` and `getType()`/`getRole()` are virtual methods. Events are stored as `unique_ptr<Event>`, allowing the event manager to hold different derived event types through a common base class.
- **Abstraction:** Managers expose operations such as `createBooking()` and `enrollStudent()` without requiring callers to perform each validation and collection update themselves.
- **Composition and ownership:** Managers own or contain collections of their related objects; `EventManager` uses `unique_ptr` to express exclusive ownership of events.

### 7. Main Features

- Maintain student, professor, and staff records.
- Maintain courses and associate students and professors with them.
- List campus facilities and their utilization.
- Create and cancel facility bookings while checking schedule conflicts.
- Add timetable entries while checking professor, venue, and class-section conflicts.
- Create different types of campus events and register participants within event capacity.
- View dashboard statistics and utilization recommendations.
- Persist application state to CSV files.
- Access the system through Flask pages and API endpoints.

### 8. Data and Persistence

The `data/` directory contains CSV files for students, professors, staff, facilities, courses, bookings, timetable entries, and events. `FileManager` reconstructs the application state when a backend command runs and writes changes back after successful mutation commands.

### 9. Running the Project

From the project directory, install the Python dependency and start Flask:

```powershell
python -m pip install -r requirements.txt
python flask\app.py
```

The backend requires `g++` to be installed and available in `PATH`. The Flask application builds `SmartCampus.exe` automatically when it is missing. Open **http://127.0.0.1:5000** in a browser.

### 10. Scope Note

`StudentManager` and `FacilityManager` are implemented as classes in the source tree. The current CLI/web request path instead loads student and facility collections directly in `CLIHandler`; these two managers are not the central managers used by that path.

### 11. Conclusion

SmartCampus demonstrates how an object-oriented design can represent university entities and organize their interactions. Its inheritance hierarchies model related people, facilities, and events; manager classes implement the system’s operational rules; and CSV persistence and a Flask interface make the functionality accessible beyond the standalone C++ program.
