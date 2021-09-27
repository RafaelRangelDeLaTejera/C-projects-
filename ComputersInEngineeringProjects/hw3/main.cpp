/***************************************************
 * Creator: Rafael Rangel                          *
 * Date: 2/26/2021                                 *
 * Project Name: hw3                               *
 * Description: Program that assign students to    *
 * random chairs in a classroom to take an exam    *
 ***************************************************/

//libraries to include
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Classroom.h"

//namespace directive
using namespace std;

int main() {
    srand(time(0));
    //vector of type Student object
    vector<Student> classList;

    //open student.txt file
    ifstream fin("students.txt"); // Attempt to open file
     if (fin.fail()) //check file opens correctly
     {
         cout << "Error: could not open data.txt.";
         return -1;
     }

     //declare strings to read in from file
    string firstName;
    string  lastName;
    //declare char variable to read in the dominant hand of the student
    char hand;
    //declare boolean variable to be assigned to true if the student is right handed, or false is otherwise
    bool rightHanded;

    //while loop to read in from file until the end of file
    while (!fin.eof()){
        fin >> firstName;
        fin >> lastName;
        fin >> hand;

        //if statements to be determine if the student is right handed or not
        if (hand == 'R')
        {
            rightHanded = true;
        }
        else
        {
            rightHanded = false;
        }

        //check previous stream to avoid repeating reading in values
        if(!fin.fail()) {
            Student listStudent(firstName, lastName,rightHanded);
            classList.push_back(listStudent);
        }
     };

    fin.close();

    //loop to print out the whole vector
    for (int i = 0; i<classList.size(); i++ ) {
        classList.at(i).printStudent();
    }

    //Classroom object created using layout ECD1101 and taking in the list of students I created, it then prints
    //the chair assignments to the screen
    Classroom uiowaCr1;
    uiowaCr1.buildChairs("layoutECD1101.txt");
    uiowaCr1.assignStudent(classList);
    cout << "Chair assignments for classroom uiowaCr1" << endl;
    uiowaCr1.printChairVector();

    //Classroom object created using layout ECD1204 and taking in the list of students I created, it then prints
    //the chair assignments to the screen
    Classroom uiowaCr2;
    uiowaCr2.buildChairs("layoutECD1204.txt");
    uiowaCr2.assignStudent(classList);
    cout << "Chair assignments for classroom uiowaCr2" << endl;
    uiowaCr2.printChairVector();

    //Classroom object created using layout ECD1214 and taking in the list of students I created, it then prints
    //the chair assignments to the screen
    Classroom uiowaCr3;
    uiowaCr3.buildChairs("layoutECD1214.txt");
    uiowaCr3.assignStudent(classList);
    cout << "Chair assignments for classroom uiowaCr3" << endl;
    uiowaCr3.printChairVector();


    return 0;
}
