//
// Created by Расим Гаджиев on 28.11.2021.
//

#include "time_controller.h"
#include <map>
#include <time.h>

long time_controller::generate_time(int year, int month, int day, int hour, int minute) {
    struct tm *timeinfo;
    time_t *rawtime = new time_t(std::time(nullptr));
    timeinfo = localtime(rawtime);
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = month - 1;
    timeinfo->tm_mday = day;
    timeinfo->tm_hour = hour;
    timeinfo->tm_min = minute;
    mktime(timeinfo);
    return abs(timelocal(timeinfo));
}

tm *time_controller::datetime_from_timestamp(long timestamp) {
    time_t *generated;
    generated = new time_t(timestamp + 60*60*3);
    auto answer =gmtime(generated);
    answer->tm_year += 0;
    return answer;
}
