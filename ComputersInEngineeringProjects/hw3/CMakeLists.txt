cmake_minimum_required(VERSION 3.17)
project(hw3)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw3 main.cpp Student.cpp Student.h Chair.cpp Chair.h Classroom.cpp Classroom.h)
configure_file(students.txt students.txt COPYONLY)
configure_file(layoutECD1101.txt layoutECD1101.txt COPYONLY)
configure_file(layoutECD1204.txt layoutECD1204.txt COPYONLY)
configure_file(layoutECD1214.txt layoutECD1214.txt COPYONLY)
