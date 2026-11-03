import os
import sys
import json
import subprocess
from flask import Flask, render_template, request, jsonify

FLASK_DIR = os.path.abspath(os.path.dirname(__file__))
BASE_DIR = os.path.abspath(os.path.join(FLASK_DIR, ".."))
app = Flask(__name__, template_folder=os.path.join(FLASK_DIR, 'templates'), static_folder=os.path.join(FLASK_DIR, 'static'))

# Locate SmartCampus.exe relative to project root
EXE_PATH = os.path.join(BASE_DIR, "SmartCampus.exe")

CPP_SOURCE_FILES = [
    os.path.join(BASE_DIR, "cpp", "main.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Person.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Student.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Professor.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Staff.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Facility.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Classroom.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Lab.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Auditorium.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "SportsGround.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Course.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Booking.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "TimetableEntry.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Event.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "Workshop.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "SportsEvent.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "CulturalEvent.cpp"),
    os.path.join(BASE_DIR, "cpp", "models", "TechnicalEvent.cpp"),
    os.path.join(BASE_DIR, "cpp", "managers", "CourseManager.cpp"),
    os.path.join(BASE_DIR, "cpp", "managers", "BookingManager.cpp"),
    os.path.join(BASE_DIR, "cpp", "managers", "TimetableManager.cpp"),
    os.path.join(BASE_DIR, "cpp", "managers", "EventManager.cpp"),
    os.path.join(BASE_DIR, "cpp", "managers", "AnalyticsManager.cpp"),
    os.path.join(BASE_DIR, "cpp", "utils", "DateTimeUtils.cpp"),
    os.path.join(BASE_DIR, "cpp", "utils", "FileManager.cpp"),
    os.path.join(BASE_DIR, "cpp", "utils", "CLIHandler.cpp"),
]


def ensure_cpp_backend():
    """Build the C++ backend automatically if the executable is missing."""
    if os.path.exists(EXE_PATH):
        return

    compile_cmd = ["g++", "-std=c++17", *CPP_SOURCE_FILES, "-o", "SmartCampus.exe"]
    result = subprocess.run(compile_cmd, cwd=BASE_DIR, capture_output=True, text=True)
    if result.returncode != 0:
        message = result.stderr.strip() or result.stdout.strip() or "Unknown C++ build error."
        raise RuntimeError(f"Failed to build SmartCampus backend: {message}")

    if not os.path.exists(EXE_PATH):
        raise RuntimeError("SmartCampus.exe was not created after compilation.")


def run_cpp_cmd(args):
    """Subprocess helper invoking SmartCampus.exe CLI API interface."""
    try:
        ensure_cpp_backend()
        cmd = [EXE_PATH, "api"] + [str(a) for a in args]
        res = subprocess.run(cmd, cwd=BASE_DIR, capture_output=True, text=True, check=True)
        lines = [line.strip() for line in res.stdout.strip().split('\n') if line.strip()]
        if not lines:
            return {"success": False, "message": "No output returned from C++ backend."}
        json_str = lines[-1]
        return json.loads(json_str)
    except subprocess.CalledProcessError as e:
        return {"success": False, "message": f"C++ execution failed: {e.stderr or e.stdout}"}
    except Exception as e:
        return {"success": False, "message": f"Subprocess error: {str(e)}"}

# ==============================================================================
# PAGE ROUTES
# ==============================================================================
@app.route('/')
def dashboard_page():
    return render_template('dashboard.html')

@app.route('/students')
def students_page():
    return render_template('students.html')

@app.route('/professors')
def professors_page():
    return render_template('professors.html')

@app.route('/staff')
def staff_page():
    return render_template('staff.html')

@app.route('/courses')
def courses_page():
    return render_template('courses.html')

@app.route('/facilities')
def facilities_page():
    return render_template('facilities.html')

@app.route('/bookings')
def bookings_page():
    return render_template('bookings.html')

@app.route('/timetable')
def timetable_page():
    return render_template('timetable.html')

@app.route('/events')
def events_page():
    return render_template('events.html')

@app.route('/analytics')
def analytics_page():
    return render_template('analytics.html')

# ==============================================================================
# API ENDPOINTS (Delegated strictly to C++ backend)
# ==============================================================================
@app.route('/api/dashboard', methods=['GET'])
def api_dashboard():
    return jsonify(run_cpp_cmd(["dashboard"]))

@app.route('/api/students', methods=['GET'])
def api_students():
    return jsonify(run_cpp_cmd(["students"]))

@app.route('/api/students/add', methods=['POST'])
def api_add_student():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "add_student",
        data.get("id"),
        data.get("name"),
        data.get("email"),
        data.get("phone"),
        data.get("branch"),
        data.get("year"),
        data.get("division")
    ]))

@app.route('/api/professors', methods=['GET'])
def api_professors():
    return jsonify(run_cpp_cmd(["professors"]))

@app.route('/api/professors/add', methods=['POST'])
def api_add_professor():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "add_professor",
        data.get("id"),
        data.get("name"),
        data.get("email"),
        data.get("phone"),
        data.get("department"),
        data.get("designation")
    ]))

@app.route('/api/staff', methods=['GET'])
def api_staff():
    return jsonify(run_cpp_cmd(["staff"]))

@app.route('/api/staff/add', methods=['POST'])
def api_add_staff():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "add_staff",
        data.get("id"),
        data.get("name"),
        data.get("email"),
        data.get("phone"),
        data.get("department"),
        data.get("designation")
    ]))

@app.route('/api/courses', methods=['GET'])
def api_courses():
    return jsonify(run_cpp_cmd(["courses"]))

@app.route('/api/courses/add', methods=['POST'])
def api_add_course():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "add_course",
        data.get("courseId"),
        data.get("courseCode"),
        data.get("courseName"),
        data.get("credits"),
        data.get("department")
    ]))

@app.route('/api/courses/enroll', methods=['POST'])
def api_enroll_student():
    data = request.json or request.form
    return jsonify(run_cpp_cmd(["enroll_student", data.get("courseId"), data.get("studentId")]))

@app.route('/api/courses/assign-professor', methods=['POST'])
def api_assign_professor():
    data = request.json or request.form
    return jsonify(run_cpp_cmd(["assign_professor", data.get("courseId"), data.get("professorId")]))

@app.route('/api/facilities', methods=['GET'])
def api_facilities():
    return jsonify(run_cpp_cmd(["facilities"]))

@app.route('/api/bookings', methods=['GET'])
def api_bookings():
    return jsonify(run_cpp_cmd(["bookings"]))

@app.route('/api/bookings/create', methods=['POST'])
def api_create_booking():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "create_booking",
        data.get("bookingId"),
        data.get("facilityId"),
        data.get("bookedByPersonId"),
        data.get("date"),
        data.get("startTime"),
        data.get("endTime"),
        data.get("purpose")
    ]))

@app.route('/api/bookings/cancel', methods=['POST'])
def api_cancel_booking():
    data = request.json or request.form
    return jsonify(run_cpp_cmd(["cancel_booking", data.get("bookingId")]))

@app.route('/api/timetable', methods=['GET'])
def api_timetable():
    return jsonify(run_cpp_cmd(["timetable"]))

@app.route('/api/timetable/add', methods=['POST'])
def api_add_timetable():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "add_timetable",
        data.get("entryId"),
        data.get("courseId"),
        data.get("professorId"),
        data.get("facilityId"),
        data.get("day"),
        data.get("startTime"),
        data.get("endTime"),
        data.get("division"),
        data.get("year")
    ]))

@app.route('/api/events', methods=['GET'])
def api_events():
    return jsonify(run_cpp_cmd(["events"]))

@app.route('/api/events/create', methods=['POST'])
def api_create_event():
    data = request.json or request.form
    return jsonify(run_cpp_cmd([
        "create_event",
        data.get("eventId"),
        data.get("type"),
        data.get("eventName"),
        data.get("description"),
        data.get("date"),
        data.get("startTime"),
        data.get("endTime"),
        data.get("facilityId"),
        data.get("organizerId", 101),
        data.get("maxParticipants", 50),
        data.get("extra1", "General"),
        data.get("extra2", "N/A")
    ]))

@app.route('/api/events/register', methods=['POST'])
def api_register_event():
    data = request.json or request.form
    return jsonify(run_cpp_cmd(["register_event", data.get("eventId"), data.get("studentId")]))

@app.route('/api/analytics', methods=['GET'])
def api_analytics():
    return jsonify(run_cpp_cmd(["analytics"]))

if __name__ == '__main__':
    print(f"Starting SmartCampus Flask Web Interface on http://127.0.0.1:5000...")
    app.run(host='127.0.0.1', port=5000, debug=True)
