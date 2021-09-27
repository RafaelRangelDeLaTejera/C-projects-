// Created by rlrangeldelatejera on 3/2/2021.
// Class name: Classrooom
// Description: class to create classroom objects, it's private member is a vector of type chair, this class has
//methods to assign students to random seats (depending on wheter or not they are righ handed) for an exam in the
// classroom layout provided
// #include "Classroom.h" to use this class in your main.cpp

#include "Classroom.h"
#include <fstream>
#include <ctime>

//method name: printChairVector
//Description: definition of the method that when called prints to the screen the classroom object (the vector
// that cr_chairList holds), it uses a for loop controlled by the size of the vector, in order to print all of the
// elements that the vector holds.
//input: none
//output: none, its a void function, it just prints to the screen
void Classroom::printChairVector() const
{
    if (!cr_chairList.empty()) {
        int size = cr_chairList.size();
        for (int i = 0; i < size; i++) {
            cr_chairList.at(i).printChairObject();
        }
    }
}

//method name: buildChairs
//Description: definition of the method that opens a classroom layout file, reads in the data and creates one chair
//object for each chair in the classroom, it assigns a row, a seat number and a blank student object and adds it to the
//chair vector in the Classroom class
//Input: string which is the layout filename
//Output: none, its of type void
void Classroom::buildChairs(const string & filename)
{
    //open file according to input string, it uses c_str() to pass string to a c style string so that it can be used
    //to open the file
    ifstream fin(filename.c_str()); // Attempt to open file
    if (fin.fail()) //check file opens correctly
    {
        cout << "Error: could not open file.";
        return;
    }

    //vector store in the read in values, to later use it to assing the private data member to it
    vector<Chair> listOfChairs;
    string row;
    int firstSeat;
    int lastSeat;
    bool rightHanded;

    //loop to read in from file until end of file
    while (!fin.eof()) {

        fin >> row;
        fin >> firstSeat;
        fin >> lastSeat;

        if(!fin.fail()) {
            for (int i = firstSeat; i <= lastSeat; i++)
            {
                if (i==lastSeat)
                {
                    rightHanded=false;
                }
                else
                {
                    rightHanded=true;
                }
                Chair chairs(row,i,rightHanded );
                listOfChairs.push_back(chairs);
            }
        }
        }
    //assign the private data member to the vector that stored the values
    cr_chairList = listOfChairs;
    }

//method name: assignStudent
//Description: method that assigns students random chairs in a classroom according to their handedness
//input: vector of type students
//output: none, its of type void
void Classroom::assignStudent(const vector<Student> & chairList){

    //vectors to sort out students from the input Student vector according to their handedness
    vector<Student> rightHandedStudents;
    vector<Student> leftHandedStudents;

    //size variable to control loop according to
    int size = chairList.size();

    //bool that will help sort out the students according to handedness
    bool sortOutHandedness;

    //loop to sort out students in right handed or left handed
    for (int i = 0; i < size; i++)
    {
        sortOutHandedness = chairList.at(i).getRightHand();
        if (sortOutHandedness)
        {
            rightHandedStudents.push_back(chairList.at(i));
        }
        else
        {
           leftHandedStudents.push_back(chairList.at(i));
        }
    }

    //int that holds size of the rightHandedStudents size
    int rightHandSize = rightHandedStudents.size();
    //for loop to rearrange the order of the students in rightHandStudents vector
    for (int i = 0; i < rightHandSize; i++)
    {
        int randomNumber;

        randomNumber = (rand() % rightHandSize);
        Student substitutedStudentR(rightHandedStudents.at(i));
        Student newStudentR(rightHandedStudents.at(randomNumber));

        rightHandedStudents.at(i) = newStudentR;
        rightHandedStudents.at(randomNumber) = substitutedStudentR;
    }

    //int that holds in the size of the leftHandedStudents
    int leftHandSize = leftHandedStudents.size();
    //for loop to rearrange the order of the students in leftHandStudents vector
    for (int i = 0; i < leftHandSize; i++)
    {
        int randomNumber;

        randomNumber = (rand() % leftHandSize);
        Student substitutedStudentL(leftHandedStudents.at(i));
        Student newStudentL(leftHandedStudents.at(randomNumber));

        leftHandedStudents.at(i) = newStudentL;
        leftHandedStudents.at(randomNumber) = substitutedStudentL;
    }

    //int that stores the number of chairs in the classroom
    int numChairs = cr_chairList.size();

    //int variables to keep the loop in check for both vectors
    int rightCount = 0;
    int leftCount = 0;

    //loop that goes through the whole classroom chairs, but also through the right and left handed students so that
    //they can be assigned a chair according to their handedness
    for (int i = 0; i < numChairs; i++)
    {
        if (getChairVector().at(i).getRightHanded() && rightCount != rightHandSize)
        {
            if (!rightHandedStudents.empty()) {
                cr_chairList.at(i).setChairStudent(rightHandedStudents.back());
                rightHandedStudents.pop_back();
            }
            else
            {
                cout << "no more right handed students" << endl;

            }
            rightCount++;
        }
        else if (!getChairVector().at(i).getRightHanded() && leftCount != leftHandSize)
        {
            if(!leftHandedStudents.empty()) {
                cr_chairList.at(i).setChairStudent(leftHandedStudents.back());
                leftHandedStudents.pop_back();
            }
            else {
                cout << "no more left handed students" << endl;

            }
            leftCount++;
        }
        else if (leftHandedStudents.empty() && rightHandedStudents.empty()){
            return;
        }

    }

    //if there where more right handed students than right handed chairs, then it prints an error to the screen and
    //the students that were not assigned
    if (!leftHandedStudents.empty())
    {
        cout << "error, there are not enough left handed desks for students" << endl
             << "the missing students are: " << endl;
        for (int i = 0; i<leftHandedStudents.size(); i++ ) {
            leftHandedStudents.at(i).printStudent();
        }
    }

    //if there where more left handed students than right handed chairs, then it prints an error to the screen and
    //the students that were not assigned
    if (!rightHandedStudents.empty())
    {
        cout << "error, there are not enough right handed desks for students" << endl
             << "the missing students are: " << endl;
        for (int i = 0; i<rightHandedStudents.size(); i++ ) {
            rightHandedStudents.at(i).printStudent();
        }
    }
}
