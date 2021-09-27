//
// Created by pollo on 5/1/2021.
//

#include "MyList.h"

using namespace std;

//MyList class method that prints the integers stored in the list in ascending order
//input: none
//output: of type void so it does not return anything it just prints the list to the screen
void MyList::printAscending() {
    if (currentPtr == nullptr) //check if the list is empty, it is empty when the currentPtr is a nullPtr
    {
        cout << "the list is empty" << endl;
    }
    else
    {
        while(currentPtr->getPreviousNode() != nullptr) //move currentPtr to the first element of the list
        {
            currentPtr = currentPtr->getPreviousNode();
        }

        if (currentPtr->getPreviousNode() == nullptr && currentPtr->getNextNode() == nullptr)//when there is just one node on the list
        {
            currentPtr->print(); //print a single node when there is just one node on the list
        }
        else
        {
            while (currentPtr->getNextNode() != nullptr) // go over the whole list in ascending order to print the list, the loop will stop at the last element
            {
                currentPtr->print(); //print the current element of the node currentPtr is pointing to
                currentPtr = currentPtr->getNextNode(); //move currentPtr to the next node on the list
            }
            currentPtr->print(); //print the last element on the list
        }

    }
}

//MyList class method that prints the list in descending order starting at the last element of the list
//input: none
//output: does not return anything it is of type void, it just prints the list to the screen
void MyList::printDescending()
{
    if (currentPtr == nullptr) //check if the list is empty, it is empty when the currentPtr is a nullPtr
    {
        cout << "the list is empty" << endl;
    }
    else
    {
        while(currentPtr->getNextNode() != nullptr) //move currentPtr to the last element of the list
        {
            currentPtr = currentPtr->getNextNode();
        }
        if (currentPtr->getPreviousNode() == nullptr && currentPtr->getNextNode() == nullptr)//when there is just one node on the list
        {
            currentPtr->print(); //print a single node when there is just one node on the list
        }
        else
        {
            while (currentPtr->getPreviousNode() != nullptr) // go over the whole list in descending order to print the list, the loop starts at the last element and stops at the first element
            {
                currentPtr->print(); //print the current element of the node currentPtr is pointing to
                currentPtr = currentPtr->getPreviousNode(); //move to the previous node on the list
            }
            currentPtr->print(); //print the first element of the list
        }
    }
}

//MyList insert method this inserts the integer into the list in ascending order
//input: the integer to insert at the end of the list
//output: none, it is of type void it does not return anything
void MyList::insert(int value)
{
    Node* newNode = new Node; // create new Node for the passed in value, this calls the node constructor which automatically sets the previous and next node pointers to nullptr

    //check that the new command successfully created a new node
    if (newNode != nullptr) //always true because memory was correctly allocated and the new node was correctly created
    {
        newNode->setInteger(value); //set the integer of the node to the passed in value
    }
    else //in case node was not properly created
    {
        cout << "new node not created properly" << endl;
        return; //exit the method if memory was not properly allocated
    }

    if (currentPtr == nullptr) //if list is empty
    {
        currentPtr = newNode; //the previousNode and nextNode are automatically initialized to null pointers when the new node was created by the Node constructor I implemented
    }
    else if (currentPtr->getPreviousNode() == nullptr && currentPtr->getNextNode() == nullptr)//if there is just one element on the list
    {
        //check where to insert it, if before or after the node
        if (newNode->getInteger() <= currentPtr->getInteger()) //the new node integer is smaller than the currentPtr integer insert it before the currentPtr
        {
            //insert it before the currentPtr
            newNode->setNextNodePtr(currentPtr);
            currentPtr->setPreviousNodePtr(newNode);
        }
        else //if it is greater or equal insert it in after, this can only happen when there is just one element on the list
        {
            //insert it in after
            newNode->setPreviousNodePtr(currentPtr);
            currentPtr->setNextNodePtr(newNode);
        }
    }
    else //find where to insert the new node on a list with more than one node
    {
        while (currentPtr->getPreviousNode() != nullptr) //move currentPtr to the first element of the list
        {
            currentPtr = currentPtr->getPreviousNode();
        }
        if (newNode->getInteger() <= currentPtr->getInteger()) //check if the new node integer is smaller than the first node integer, if so insert it before the currentPtr
        {
            //insert it before the currentPtr
            newNode->setNextNodePtr(currentPtr);
            currentPtr->setPreviousNodePtr(newNode);
        }
        else
        {
            //in a list with more than one node, find where to insert the new Node by going through this while loop, it will
            while (currentPtr->getNextNode() != nullptr && newNode->getInteger() >= currentPtr->getInteger()) // go over the whole list in ascending order and stop when currentPtr is greater than newNode
            {
                currentPtr = currentPtr->getNextNode();
            }
            if (currentPtr->getNextNode() == nullptr && newNode->getInteger() >= currentPtr->getInteger()) //in case current node is the last element on the list and is actually smaller than newNode
            {
                //insert to the right
                newNode->setPreviousNodePtr(currentPtr);
                currentPtr->setNextNodePtr(newNode);
            }
            else //else to be inserted in the middle where newNode is smaller than currentPtr and is inserted to the left following the while loop that positions the currentPtr on the place where to insert it to the left
            {
                //insert to the left after the while loop determined the position where to insert it the currentPtr node is greater than the new node
                newNode->setNextNodePtr(currentPtr);
                newNode->setPreviousNodePtr(currentPtr->getPreviousNode());
                currentPtr->getPreviousNode()->setNextNodePtr(newNode);
                currentPtr->setPreviousNodePtr(newNode);
            }
        }
    }
}

//remove method, this method removes and deletes the first node on the list with an integer value matching the passed in value
//input: int value to be removed
//output: does not return anything, it is of type void
void MyList::remove(int value)
{
    if (currentPtr == nullptr) //if the list is empty
    {
        cout << "nothing can be removed, the list is empty" << endl;
    }
    else if (currentPtr->getPreviousNode() == nullptr && currentPtr->getNextNode() == nullptr)//if there is just one element on the list
    {
        if (currentPtr->getInteger() == value)
        {
            delete currentPtr; //delete the node to avoid memory leaks
            currentPtr = nullptr; //set currentPtr back to currentPtr
        }
        else
        {
            cout << "number " << value << " is not found on the list so it can't be removed " << endl;
        }
    }
    else //look through the list for the node that matches the value to be deleted
    {
        while(currentPtr->getPreviousNode() != nullptr) //move currentPtr to the first element of the list
        {
            currentPtr = currentPtr->getPreviousNode();
        }

        while (currentPtr->getNextNode() != nullptr && currentPtr->getInteger() != value)//position currentPtr at the Node that matches the value, or at the end of the list
        {
            currentPtr = currentPtr->getNextNode();
        }

        if (currentPtr->getPreviousNode() == nullptr && currentPtr->getInteger() == value) //in case element to be removed is at the start of the list
        {
            //remove the first element of the list
            currentPtr = currentPtr->getNextNode();
            currentPtr->getPreviousNode()->setNextNodePtr(nullptr);
            delete currentPtr->getPreviousNode();
            currentPtr->setPreviousNodePtr(nullptr);
        }
        else if (currentPtr->getNextNode() == nullptr && currentPtr->getInteger() == value) //in case element to be removed is at the end of the list
        {
            //remove the last element of the list
            currentPtr = currentPtr->getPreviousNode();
            currentPtr->getNextNode()->setPreviousNodePtr(nullptr);
            delete currentPtr->getNextNode(); //clear memory
            currentPtr->setNextNodePtr(nullptr);
        }
        else if (currentPtr->getInteger() == value) //if it is in the middle
        {
            //remove the element at the middle of the list
            Node* nodeToDelete; //create a node pointer to point to the node to be deleted so that it can be succesfully deleted
            nodeToDelete = currentPtr;
            currentPtr = currentPtr->getNextNode();
            currentPtr->setPreviousNodePtr(nodeToDelete->getPreviousNode());
            nodeToDelete->getPreviousNode()->setNextNodePtr(currentPtr);
            nodeToDelete->setNextNodePtr(nullptr);
            nodeToDelete->setPreviousNodePtr(nullptr);
            delete nodeToDelete; //clear memory
        }
        else //if the value is not on the list print the following messages
        {
            cout << "number "<< value << " is not on the list" << endl;
        }
    }
}

//clear method, this removes all elements from the list
//input: none
//output: of type void, it does not return anything
void MyList::clear()
{
    int valueDeleted; //variable to print the value of the node deleted

    if (currentPtr == nullptr) //when list is empty
    {
        cout << "the list is empty" << endl;
    }
    else if (currentPtr->getNextNode() == nullptr && currentPtr->getPreviousNode() == nullptr) //in case the list only has one node
    {
        valueDeleted = currentPtr->getInteger(); //assign integer of the node to be deleted to the valueDeleted variable to print it
        //remove the only node
        delete currentPtr; //
        currentPtr = nullptr; //set currentPtr back to nullptr
        cout << "value of node deleted: " << valueDeleted << endl; //print to the screen the node deleted
    }
    else
    {
        while (currentPtr->getPreviousNode() != nullptr) //move currentPtr to the first element of the list
        {
            currentPtr = currentPtr->getPreviousNode();
        }
        while (currentPtr->getNextNode() != nullptr) // go through the entire list to delete every node, except for the last one
        {
            currentPtr = currentPtr->getNextNode();
            //remove the node previous from the currentPtr
            valueDeleted = currentPtr->getPreviousNode()->getInteger();
            currentPtr->getPreviousNode()->setNextNodePtr(nullptr);
            delete currentPtr->getPreviousNode(); //delete the previous node on the list
            currentPtr->setPreviousNodePtr(nullptr);
            cout << "value of node deleted: " << valueDeleted << endl; //print the value deleted
        }
        //delete the last element of the list
        valueDeleted = currentPtr->getInteger();
        cout << "value of node deleted: " << valueDeleted << endl;
        delete currentPtr;
        currentPtr = nullptr; //set currentPtr back to nullPtr and the list is clear
    }
}

//class destructor this clears all of the list
MyList::~MyList()
{
    cout << "destructor called " << endl;
    clear();
}