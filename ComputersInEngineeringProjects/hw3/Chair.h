// Created by rlrangeldelatejera on 3/2/2021.
// Class name: Chair
// Description: class to create chair objects, it holds the chairs row, seat row number, whether or not it is for a
//right handed person and a student who will occupy it
// #include "Chair.h" to use this class in your main.cpp

#ifndef HW3_CHAIR_H
#define HW3_CHAIR_H

#endif //HW3_CHAIR_H
#include "iostream"
#include <string>
#include <utility>
#include "Student.h"

class Chair{
public:
    //since there is an object in this class and a constructor can't call another constructor, I created two
    // constructors, one that can take in no arguments and one that takes at least the studentChair object

    //constructor that can take in no arguments or just row, or number or right handed
    explicit Chair(std::string row = "A", int number = 0,bool rightHanded = true):
    c_chairStudent(Student()), c_row(std::move(row)), c_number(number), c_rightHanded(rightHanded){};

    //constructor that takes in at least the student object arguments
    explicit Chair(Student student,std::string row = "A", int number = 0,bool rightHanded = true):
     c_chairStudent(student),c_row(std::move(row)), c_number(number), c_rightHanded(rightHanded){};

    //setters for the private members of the chair class
    void setRow(std::string row){c_row=std::move(row);};
    void setNumber(int number){c_number=number;};
    void setRightHanded(bool rightHanded){c_rightHanded=rightHanded;};
    void setChairStudent(Student student){c_chairStudent=std::move(student);};

    //getters for the private members of the chair class
    std::string getRow(){return c_row;};
    int getNumber(){return c_number;};
    bool getRightHanded(){return c_rightHanded;};
    Student getChairStudent(){return c_chairStudent;};

    //Method name: printChairObject
    //Description: prototype of the print method to display on the screen the values of the private members of the class
    //input: none, it uses the data member values the chair object has
    //output: its a void type function so it doesn't return anything, it just prints to the screen
    void printChairObject()const;


private:
    //private data members of the chair class
    Student c_chairStudent;
    std::string c_row;
    int c_number;
    bool c_rightHanded;


};
