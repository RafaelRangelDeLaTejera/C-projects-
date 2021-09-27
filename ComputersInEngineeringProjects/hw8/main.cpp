/***************************************************
 * Creator: Rafael Rangel                          *
 * Date: 05/01/2021                                *
 * Project Name: hw8                               *
 * Description: program that implements a doubly   *
 * linked list class of integers                   *
 ***************************************************/

#include <iostream>
#include "MyList.h" //include MyList class header file which already includes the Node header file so both classes are included

using namespace std;

int main() {

    //Node class tests begin
    cout << "----------Node class tests----------" << endl;
    //create a Node object node1 without input values to test the default values in the constructor
    Node node1;
    cout << "Node constructor test default values and getters for each private members variables" << endl;
    //test the getters and the constructor with this if statement and show proof to the screen when the program is executed
    //print "default constructor and getters test passed" and the prove if previous tests were passed
    if (node1.getInteger() == 0 && node1.getPreviousNode() == nullptr && node1.getNextNode() == nullptr){
        cout<< "default constructor and getters test passed" << endl;
        cout << "Prove that default values were assigned correctly by the constructor and that getters work: " << endl; //let the user know what is happening
        cout << "getInteger test should return 0, return: " << node1.getInteger() << endl; //prove the test getInteger method and default constructor
        cout << "getNextNode test should return a nullptr, so this should print a 0, this prints: " << node1.getNextNode() << endl; //prove the test getNextPtr and default constructor
        cout << "getPreviousNode test should return a nullptr, so this should print a 0, this prints:" << node1.getPreviousNode() << endl; //prove the test getPreviousPtr and default constructor
    }

    node1.setInteger(1); //set the n_integer from node1 to 1 for future convenience when testing

    cout << "test the constructor with input values" << endl;
    //test constructor and print() method
    Node node2(4, nullptr, &node1); // construct a new node object with input values for the data members
    //if the constructor built the object properly this if statement will enter and display the prove
    if (node2.getInteger() == 4 && node2.getNextNode() == nullptr && node2.getPreviousNode() == &node1){
        cout << "constructor test was successfully " << endl;
        cout << "print method test, should print out 1 and 4" << endl;
        cout << "int in node1: " << endl;
        node1.print(); //print the integer stored in node1 n_integer variable
        cout << "int in node2: " << endl;
        node2.print(); //print the integer stored in node2 n_integer variable
        cout << "print the value stored in the Node n_integer that node2 previousNodePtr is pointing to, should be 1 " << endl;
        node2.getPreviousNode()->print(); //print the value stored the n_integer member of the node that node2's previousNodePtr is pointing to which should be from node1, sp 1

        //test the setters
        cout << "next test the setters" << endl;
        Node node3 ; //create a new node object node3
        node3.setInteger(3); //check if node2 previousNodePtr points to node1 by assigning the n_integer of the previousNode (node1) to the n_integer of node3
        node2.setNextNodePtr(&node3); //test setNextNode by having node2's nextNodePtr point to node 3
        node3.setPreviousNodePtr(&node2); //have node3's previousNodePtr point to node2
        cout << "test the setters used, this should print values of 3 and 4" << endl;
        node2.getNextNode()->print(); //should print 3 since it prints the integer of the node that node2's nextNodePtr is pointing to
        node3.getPreviousNode()->print(); //should print 4 since it prints the integer of the node that node3's previousNodePtr is pointing to
    }

    //test the constructor of MyList class
    MyList list1;
    cout << "test the printAscending and printDescending methods of the MyList class on an empty list, both should print that the list is empty" << endl;
    list1.printAscending();
    list1.printDescending();

    //test insert method on an empty list and also the print methods with just one element
    cout << "test insert method on an empty list and also the print methods with just one element" << endl;
    cout << "both should print out 10" << endl;
    list1.insert(10);
    list1.printAscending();
    list1.printDescending();

    //test insert method and print methods
    cout << "test insert method and print method " << endl;
    cout << "first print in ascending order" << endl;
    list1.insert(20);
    list1.insert(4);
    list1.insert(2);
    list1.insert(80);
    list1.insert(5);
    list1.insert(244);
    list1.insert(1);
    list1.insert(4);
    list1.insert(7);
    list1.insert(21);
    list1.insert(19);
    list1.insert(1001);
    list1.insert(1);
    list1.printAscending();
    cout << "now print in descending order" << endl;
    list1.printDescending();

    //remove method tests
    cout << "remove method tests, first remove 1,there are two 1 so it should only remove the first 1 encountered " << endl;
    list1.remove(1);
    list1.printAscending();
    cout << "now remove 10" << endl;
    list1.remove(10);
    list1.printAscending();
    cout << "now remove 1001" << endl;
    list1.remove(1001);
    list1.printAscending();
    cout << "now remove one of the two 4" << endl;
    list1.remove(4);
    list1.printAscending();
    cout << "try to remove a value that is not on the list, 9" << endl;
    list1.remove(9);

    //clear method test
    cout << "clear method test" << endl;
    list1.clear();
    cout << "aster it has been clear print the list with both print methods" << endl;
    list1.printAscending();
    list1.printDescending();
    cout << "try to clear an empty list" << endl;
    list1.clear();
    cout << "clear a list with just one element " << endl;
    cout << "so insert 1 and then clear" << endl;
    list1.insert(1);
    list1.clear();

    //further test methods
    cout << "further test insert method by creating a new list" << endl;
    list1.insert(44);
    list1.insert(2);
    list1.insert(22);
    list1.insert(100);
    list1.insert(1);
    cout << "list in ascending order" << endl;
    list1.printAscending();
    cout << "list in descending order " << endl;
    list1.printDescending();

    cout << "test remove method by removing nodes with values of 1,100 and 22, the first, last and a middle value " << endl;
    list1.remove(1);
    list1.remove(100);
    list1.remove(22);
    list1.printAscending();
    cout << "now remove the remaining 2 and 44 values one by one and print the list" << endl;
    list1.remove(2);
    list1.remove(44);
    list1.printAscending();
    cout << "try to delete a number from an empty list" << endl;
    list1.remove(44);

    cout << "finally create a list to test the destructor " << endl;
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(4);
    cout << "list in ascending order" << endl;
    list1.printAscending();
    cout << "list in descending order " << endl;
    list1.printDescending();

    return 0;
}
