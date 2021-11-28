#include <iostream>
#include "Diary.h"


int main() {
    setlocale(LC_ALL, "ru");
    auto my_diary = Diary("diary.txt");
    my_diary.load_diary();
//    my_diary.input_task();
//    my_diary.input_task();
//    my_diary.input_task();
    my_diary.print_task(my_diary.sort_task());

//    my_diary.filter_by_date();
//    my_diary.input_task();
//    my_diary.save_diary();

//    my_diary.erase();
    my_diary.save_diary();
}
