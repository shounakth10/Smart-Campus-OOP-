#include "DateTimeUtils.h"
#include <cstdio>
#include <algorithm>

using namespace std;

int DateTimeUtils::timeToMinutes(const string& time) {
    int h = 0, m = 0;
    if (sscanf(time.c_str(), "%d:%d", &h, &m) == 2) {
        return h * 60 + m;
    }
    return 0;
}

bool DateTimeUtils::isValidTime(const string& time) {
    if (time.length() != 5 || time[2] != ':') return false;
    int h = -1, m = -1;
    if (sscanf(time.c_str(), "%d:%d", &h, &m) != 2) return false;
    return (h >= 0 && h < 24 && m >= 0 && m < 60);
}

bool DateTimeUtils::isTimeOverlap(const string& start1, const string& end1,
                                 const string& start2, const string& end2) {
    int s1 = timeToMinutes(start1);
    int e1 = timeToMinutes(end1);
    int s2 = timeToMinutes(start2);
    int e2 = timeToMinutes(end2);

    return (max(s1, s2) < min(e1, e2));
}

double DateTimeUtils::calculateDuration(const string& start, const string& end) {
    int s = timeToMinutes(start);
    int e = timeToMinutes(end);
    if (e <= s) return 0.0;
    return static_cast<double>(e - s) / 60.0;
}
