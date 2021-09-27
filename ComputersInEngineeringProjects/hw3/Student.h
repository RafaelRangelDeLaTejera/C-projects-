// Created by rlrangeldelatejera on 2/26/2021.
// Class name: Student
// Description: class to create student objects for a students first name, last name and wheter he is right handed or not
// some method definitions are in Student.cpp
// #include "Student.h" to use this class in your main.cpp

#ifndef HW3_STUDENT_H
#define HW3_STUDENT_H

#endif //HW3_STUDENT_H

#include "iostream"
#include <string>
#include <utility>


class Student{
public:
    explicit Student(std::string firstName = "empty", std::string lastName = "student", bool rightHanded = true):
            s_firstName{std::move(firstName)},s_lastName{std::move(lastName)},s_rightHanded{rightHanded}{
    };

    //setter methods for first name and for last name
    //description: assigns a string value to the private data members
    //input: variable of string type to be assigned to the data members
    //output: none, its a void function
    void setFirstName(std::string firstName){s_firstName = std::move(firstName);};

    void setLastName(std::string lastName){s_lastName = std::move(lastName);};

    //setter method for rightHanded data members
    //description: assigns a boolean value to the data member
    //input: variable of bool type to be assigned to the data members
    //output: none, its a void function
    void setRightHand(bool rightHanded){s_rightHanded = rightHanded;};

    //getters methods for firstName and lastName
    //description: returns the current string value of the corresponding data member
    //input: none
    //output: variable of type string with the string that the private members hold
    std::string getFirstName()const{return s_firstName;};
    std::string getLastName()const{return s_lastName;};

    //getters method for s_rightHand
    //description: returns the current value of the private member
    //input: none
    //output: variable of type boolean with the value that the private member holds
    bool getRightHand()const{return s_rightHanded;};

    //print method to display a student object private members
    //description: prints to the screen the the objects private members
    //input: none
    //output: void return type, but prints the data members
    void printStudent()const;


private:
    std::string s_firstName;
std::string s_lastName;
bool s_rightHanded;

};
