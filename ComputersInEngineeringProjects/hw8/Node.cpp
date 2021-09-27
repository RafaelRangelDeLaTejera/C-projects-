// Node class
// Created by Rafael Rangel on 5/1/2021.
// Description: Node class to be used in a double linked list of integers
// Node.h header file

#include "Node.h"
//#include "iostream"

using namespace std;

//n_integer setter method
//input: integer to assign to the n_integer data member
//output: none, its of type void
void Node::setInteger (int inputInt){
    n_integer = inputInt;
}

//nextNodePtr setter method
//input: Node pointer to assign to the nextNodePtr
//output: none, its of type void
void Node::setNextNodePtr (Node* inputNextNode){
    nextNodePtr = inputNextNode;
}

//previousNodePtr setter method
//input: Node pointer to assign to the previousNodePtr
//output: none, its of type void
void Node::setPreviousNodePtr (Node* inputPreviousNode){
    previousNodePtr = inputPreviousNode;
}

//n_integer getter method
//input: none
//output: integer stored in n_integer
int Node::getInteger()const{
    return n_integer;
}

//nextNodePtr getter method
//input: none
//output: pointer stored in nextNodePtr
Node* Node::getNextNode()const{
    return nextNodePtr;
}

//nextNodePtr getter method
//input: none
//output: pointer stored in previousNodePtr
Node* Node::getPreviousNode()const{
    return previousNodePtr;
}

//print method
//input: none
//output: doesn't return anything, it's of type pointer, but it does print to the screen the integer stored in the node
void Node::print()const{
    cout << "Node: " << n_integer << endl;
}