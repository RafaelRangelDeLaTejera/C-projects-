// Created by rlrangeldelatejera on 2/26/2021.
// Class method definitions for Student class
// Student.h is the header file
// Description: student object, for a classrooms student name and wheter or not they are right handed

#include "Student.h"
#include "iostream"
using namespace std;

//print method to display a student object private members
//description: prints to the screen the the objects private members
//input: none
//output: void return type, but prints the data members
void Student::printStudent() const
{

    cout << s_firstName << " " << s_lastName << " " << s_rightHanded << endl;
}

