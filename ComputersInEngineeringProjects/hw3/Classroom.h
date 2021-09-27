// Created by rlrangeldelatejera on 3/2/2021.
// Class name: Classrooom
// Description: class to create classroom objects, it's private member is a vector of type chair, this class has
//methods to assign students to random seats (depending on wheter or not they are righ handed) for an exam in the
// classroom layout provided
// #include "Classroom.h" to use this class in your main.cpp

#ifndef HW3_CLASSROOM_H
#define HW3_CLASSROOM_H

#endif //HW3_CLASSROOM_H
#include "Chair.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Classroom{
public:

    //constructors for the chair class
    //default constructor for when no vector was passed to be assigned to the classroom object data members
    explicit Classroom():cr_chairList(1,Chair()){};

    //constructor for when the object is assigned by the user
    explicit Classroom(vector<Chair> chairList):cr_chairList(chairList){};

    //setter for the cr_chairList private data member
    void setChairVector (vector<Chair> chairList){cr_chairList = chairList;};

    //getter for the cr_chairList private data member, it returns the vector that cr_chairList holds
    vector<Chair> getChairVector (){return cr_chairList;};

    //method name: printChairVector
    //Description: prototype for the method that when called prints to the screen the classroom object (the vector
    // that cr_chairList holds)
    //input: none
    //output: none, its a void function, it just prints to the screen
    void printChairVector()const;

    //method name: buildChairs
    //Description: definition of the method that opens a classroom layout file, reads in the data and creates one chair
    //object for each chair in the classroom, it assigns a row, a seat number and a blank student object and adds it to the
    //chair vector in the Classroom class
    //Input: string which is the layout filename
    //Output: none, its of type void
    void buildChairs(const string & filename);

    //method name: assignStudent
    //Description: method that assigns students random chairs in a classroom according to their handedness
    //input: vector of type students
    //output: none, its of type void
    void assignStudent(const vector<Student> & chairList);

private:
    vector<Chair> cr_chairList;
};