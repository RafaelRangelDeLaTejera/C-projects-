// Node class
// Created by Rafael Rangel on 5/1/2021.
// Description: Node class to be used in a double linked list of integers
// Method definitions in Node.cpp

#ifndef HW8_NODE_H
#define HW8_NODE_H
#include "iostream"

class Node {
public:
    //constructor to initialize all data members and set default values for those not provided
    explicit Node(int integer = 0, Node* nextNode = nullptr, Node* previousNode = nullptr):
    n_integer{integer},nextNodePtr{nextNode},previousNodePtr{previousNode}{};

    //n_integer setter method
    //input: integer to assign to the n_integer data member
    //output: none, its of type void
    void setInteger (int inputInt);

    //nextNodePtr setter method
    //input: Node pointer to assign to the nextNodePtr
    //output: none, its of type void
    void setNextNodePtr (Node* inputNextNode);

    //previousNodePtr setter method
    //input: Node pointer to assign to the previousNodePtr
    //output: none, its of type void
    void setPreviousNodePtr (Node* inputPreviousNode);

    //n_integer getter method
    //input: none
    //output: integer stored in n_integer
    int getInteger()const;

    //nextNodePtr getter method
    //input: none
    //output: pointer stored in nextNodePtr
    Node* getNextNode()const;

    //nextNodePtr getter method
    //input: none
    //output: pointer stored in previousNodePtr
    Node* getPreviousNode()const;

    //print method
    //input: none
    //output: doesn't return anything, it's of type pointer, but it does print to the screen the integer stored in the node
    void print()const;

//private data members
private:
    int n_integer;
    Node* nextNodePtr;
    Node* previousNodePtr;

};


#endif //HW8_NODE_H
