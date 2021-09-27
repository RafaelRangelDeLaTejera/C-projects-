// Created by rlrangeldelatejera on 3/2/2021.
// Class name: Chair
// Description: class to create chair objects, it holds the chairs row, seat row number, whether or not it is for a
//right handed person and a student who will occupy it
// #include "Chair.h" to use this class in your main.cpp

#include "Chair.h"
#include "iostream"

using namespace std;

//Method name: printChairObject
//Description: Definition of the print method to display on the screen the values of the private members of the class
// If the student object has the default value of empty, then the Chair object isn't printed since no actual student
// was assigned to it
//input: none, it uses the data member values the chair object has
//output: its a void type function so it doesn't return anything, it just prints to the screen
void Chair::printChairObject() const{
    if (c_chairStudent.getFirstName() != "empty") {
        cout << "row: " << c_row << endl
             << "number: " << c_number << endl
             << "rightHanded: " << c_rightHanded << endl
             << "student: ";
        c_chairStudent.printStudent();
    }
}

