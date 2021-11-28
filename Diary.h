//
// Created by Расим Гаджиев on 28.11.2021.
//

#ifndef DIARYPROJECTFORKIITY_DIARY_H
#define DIARYPROJECTFORKIITY_DIARY_H

#include <string>
#include <utility>
#include <vector>
#include "time_controller.h"

struct Task {
    std::string text;
    long dead_line;
    bool done;
};

struct Date {
    int year;
    int month;
    int day;
};

class Diary {
private:
    std::string diary_path;
    time_controller time_controller;

    void add_task(const Task& task);

public:
    explicit Diary(std::string path) {
        this->diary_path = std::move(path);
    }

    void load_diary();

    void save_diary();

    void input_task();

    static void print_task(std::vector<Task> target);

    std::string format_diary();

    void filter_by_date();

    std::vector<Task> fetch_task_by_date(Date date);

    std::vector<Task> sort_task();

    void erase();

    std::vector<Task> diary_array;
};


#endif //DIARYPROJECTFORKIITY_DIARY_H
