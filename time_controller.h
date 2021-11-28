//
// Created by Расим Гаджиев on 28.11.2021.
//

#ifndef DIARYPROJECTFORKIITY_TIME_CONTROLLER_H
#define DIARYPROJECTFORKIITY_TIME_CONTROLLER_H

#include <time.h>
#include <stdio.h>

class time_controller {


//    time_t input_time();

public:
    static long generate_time(int year, int month, int day, int hour, int minute);
    static tm * datetime_from_timestamp(long timestamp);
};


#endif //DIARYPROJECTFORKIITY_TIME_CONTROLLER_H
