cmake_minimum_required(VERSION 3.20)
project(DiaryProjectForKiity)

set(CMAKE_CXX_STANDARD 23)

add_executable(DiaryProjectForKiity main.cpp time_controller.cpp time_controller.h Diary.cpp Diary.h)
