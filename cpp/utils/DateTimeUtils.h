#pragma once

#include <string>

using namespace std;

class DateTimeUtils {
public:
    static int timeToMinutes(const string& time);
    static bool isValidTime(const string& time);
    static bool isTimeOverlap(const string& start1, const string& end1,
                              const string& start2, const string& end2);
    static double calculateDuration(const string& start, const string& end);
};
