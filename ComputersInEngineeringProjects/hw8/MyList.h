// MyList class
// Created by Rafael Rangel on 5/1/2021.
// Description: doubly linked list of integers class
// Method definitions are in MyList.cpp

#ifndef HW8_MYLIST_H
#define HW8_MYLIST_H

#include "Node.h" //inlude the Node class header file to use

class MyList {
public:
    //class default constructor initializes currentPtr to nullPtr this means the list is empty when first created
    explicit MyList(){currentPtr = nullptr;}

    //MyList class method that prints the integers stored in the list in ascending order
    //input: none
    //output: of type void so it does not return anything it just prints the list to the screen
    void printAscending() ;

    //MyList class method that prints the list in descending order starting at the last element of the list
    //input: none
    //output: does not return anything it is of type void, it just prints the list to the screen
    void printDescending() ;

    //MyList insert method this inserts the integer into the list in ascending order
    //input: the integer to insert at the end of the list
    //output: none, it is of type void it does not return anything
    void insert(int value);

    //remove method, this method removes and deletes the first node on the list with an integer value matching the passed in value
    //input: int value to be removed
    //output: does not return anything, it is of type void
    void remove(int value);

    //clear method, this removes all elements from the list
    //input: none
    //output: of type void, it does not return anything
    void clear();

    //class destructor
    ~MyList();

//private data member pointer variable that will point to the current Node on the list
private:
    Node* currentPtr;
};


#endif //HW8_MYLIST_H
