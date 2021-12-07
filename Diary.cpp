//
// Created by Расим Гаджиев on 28.11.2021.
//

#include "Diary.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

bool compare_by_time(const Task &a, const Task &b) {
    return a.dead_line < b.dead_line;
}

void Diary::load_diary() {
    std::cout << "Производится чтение дневника и запись данных в оперативную память.." << std::endl;
    std::ifstream ip(this->diary_path);
    if (!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
    std::vector<Task> data;
    while (ip.good()) {
        std::string input_text;
        std::string input_dead_line;
        std::string input_done;
        std::string text;
        long dead_line;
        bool done;
        getline(ip, input_text, ',');
        text = input_text.c_str();
        getline(ip, input_dead_line, ',');
        dead_line = atoi(input_dead_line.c_str());
        getline(ip, input_done, '\n');
        done = atoi(input_done.c_str());
        if (!dead_line) {
            break;
        }
        data.push_back({
                               text,
                               dead_line,
                               done
                       });
    }

    ip.close();
    this->diary_array = data;
    std::cout << "Чтение прошло успешно!" << std::endl;

}


void Diary::save_diary() {
    std::cout << "Производится запись дневника из оперативной памяти в текстовый файл.." << std::endl;
    std::ofstream out(this->diary_path);
    out << this->format_diary();
    out.close();
    std::cout << "Запись прошла успешно!" << std::endl;
}

std::vector<Task> Diary::fetch_task_by_date(Date date) {
    std::vector<Task> target;
    char buffer[160];
    for (auto &i: this->diary_array) {
        tm *i_datetime = time_controller::datetime_from_timestamp(i.dead_line);
        strftime(buffer, 160, "%d.%m.%Y %H:%M.", i_datetime);
        if (i_datetime->tm_year + 1900 == date.year && i_datetime->tm_mday == date.day &&
            i_datetime->tm_mon + 1 == date.month) {
            target.push_back(i);
        }
    }
    return target;
}

void Diary::add_task(const Task &task) {
    this->diary_array.push_back(task);
}

std::vector<Task> Diary::sort_task() {
    std::vector<Task> target;
    for (auto &i: this->diary_array) {
        target.push_back(i);
    }
    std::sort(target.begin(), target.end(), compare_by_time);
    return target;
}


void Diary::erase() {
    this->diary_array.clear();
}

void Diary::input_task() {
    std::string task_text;
    int year, month, day, hour, min;
    std::cout << "Чтож, введите текст задачи: ";
    std::cin >> task_text;
    std::cout << "Теперь договоримся о дед лайне.. " << std::endl;
    std::cout << "Введите год: ";
    std::cin >> year;
    std::cout << "Введите месяц: ";
    std::cin >> month;
    std::cout << "Введите день: ";
    std::cin >> day;
    std::cout << "Введите час: ";
    std::cin >> hour;
    std::cout << "Введите минуты: ";
    std::cin >> min;
    auto timestamp = time_controller::generate_time(year, month, day, hour, min);
    Task temp_task = {
            task_text,
            timestamp,
            false};
    add_task(temp_task);
}

void Diary::print_task(std::vector<Task> target) {
    char buffer[160];
    for (auto &i: target) {
        if (i.done) {
            continue;
        }
        strftime(buffer, 160, "%d.%m.%Y %H:%M", time_controller::datetime_from_timestamp(i.dead_line));
        std::cout << "{\n\t'Текст задачи': " << i.text << ",\n\t'Дед лайн': "
                  << buffer <<
                  ",\n\t'Выполнено': "
                  << i.done << ",\n"
                  << "}, " << std::endl;
    }
}

std::string Diary::format_diary() {
    std::string target;
    for (const auto &i: this->diary_array) {
        target += i.text + "," + std::to_string(i.dead_line) + "," + std::to_string(i.done) + "\n";
    }
    return target;
}

void Diary::filter_by_date() {
    int year, month, day;
    std::cout << "Назовите интересующую дату.." << std::endl;
    std::cout << "Введите год: ";
    std::cin >> year;
    std::cout << "Введите месяц: ";
    std::cin >> month;
    std::cout << "Введите день: ";
    std::cin >> day;
    print_task(this->fetch_task_by_date({
                                                year,
                                                month,
                                                day
                                        }));
}

void Diary::task_delete(const std::string& text) {
    std::vector<Task> target;
    for (int i = 0; i < this->diary_array.size(); i ++){
        if (this->diary_array[i].text == text) {
            this->diary_array.erase(this->diary_array.begin() + i);
        }
    }
}

void Diary::drop_task() {
    std::string text;
    std::cout<<"Введите название задачи, которую нужно удалить"<<std::endl;
    std::cin>>text;
    this->task_delete(text);
    std::cout<<"Успешно удалён элемент с именем - "<<text<<std::endl;
}
