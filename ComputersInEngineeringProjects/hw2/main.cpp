/***************************************************
 * Creator: Rafael Rangel                          *
 * Date: 2/14/2021                                 *
 * Project Name: hw2                               *
 * Description: Program that tests a class to      *
 * perform basic matrix operations                 *
 ***************************************************/

#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

    //declaration and initialization of matrix objects
    Matrix m1; //this is bad practice but I am doing this to test the constructor, it should assign values of 0
    Matrix m2(1,4);
    Matrix m3(1,2,3,4);
    Matrix m4(-11,22,33,-44);
    Matrix m5(4,16,48,12);
    Matrix m6(9,1,9,1);

    //for the tests , not all operations are performed with the original matrices element values, since some of the
    //methods change the private members so the elements change and result in a different matrix.
    //For example if object m9 calls the inverse method, it changes the matrix into its inverse, and then if transpose
    //method is called for m9, the m9 matrix will be the transpose of the inverse of the original matrix.
    //Constructor tests and print method tests
    cout << "Matrix class constructor tests:" << endl
         << " Test one, should print out: " << endl
         << "0 0" << endl
         << "0 0" << endl
         << "test prints out: " << endl;
    m1.printMatrix();
    cout << " Test two, should print out: " << endl
         << "1 4" << endl
         << "0 0" << endl
         << "test prints out: " << endl;
    m2.printMatrix();

    //setters test
    cout << "setters tests for each elements of a matrix object" << endl
         << "test should print out: " << endl
         << "5 2" << endl
         << "-8 11" << endl;
    //call the setters for each private member of the object m1 to assign new values to the m1 matrix
    m1.setElement1(5);
    m1.setElement2(2);
    m1.setElement3(-8);
    m1.setElement4(11);
    cout << "test prints out: " << endl;
    m1.printMatrix();  //prints the new matrix

    //getters test
    cout << "getters test:" << endl
         << "test one should print out: "<< endl
         << "1 4 0 0" << endl
         << "test prints: " << endl;
    //call the getters for the m2 matrix object to return the values of each private members
    cout << m2.getElement1() << " " << m2.getElement2() << " " << m2.getElement3() << " "<< m2.getElement4() << endl;

    cout << "getters test:" << endl
         << "test two should print out: "<< endl
         << "16 48" << endl
         << "test prints: " << endl;
    //call the getters for the m5 matrix object to return the values of each private members
    cout << m5.getElement2() << " " << m5.getElement3() << endl;

    //determinant method tests
    cout << "determinant tests: " << endl
         << "test one should print out " << endl
         << "0" << endl
         << "test prints: " << endl;
    //call the determinant method of the m6 matrix object return the determinant of the matrix and display it
    cout << m6.determinant() << endl;
    cout << "test two should print out " << endl
         << "-242" << endl
         << "test prints: " << endl;
    //call the determinant method of the m4 matrix object return the determinant of the matrix and display it
    cout << m4.determinant() << endl;

    //inverse method tests
    cout << "inverse tests: " << endl
         << "test one should print out " << endl
         << "-2 1" << endl
         << "1.5 -0.5" << endl
         << "test prints: " << endl;
    //call the inverse method of the m3 matrix object to change the matrix into its inverse, or display it doesnt have
    //an inverse
    m3.inverse();
    //call the print method in m3 to display the matrix (now representing the inverse of the original matrix)
    m3.printMatrix();
    cout << "test two should print out " << endl
         << "Error, matrix is not invertible " << endl
         << "test prints: " << endl;
    //call the inverse method of the m6 matrix object to change the matrix into its inverse, or display it doesnt have
    //an inverse
    m6.inverse();

    //transpose method tests
    cout << "transpose tests: " << endl
         << "test one should print out " << endl
         << "-11 33 " << endl
         << "22 -44 " << endl
         << "test prints: " << endl;
    //call the transpose method of the m4 matrix object to change the matrix into its transpose
    m4.transpose();
    //call the m4 object printMatrix method to display the matrix, (now representing the transpose of the original matrix
    m4.printMatrix();
    cout << "transpose tests: " << endl
         << "test one should print out " << endl
         << "4 48 " << endl
         << "16 12 " << endl
         << "test prints: " << endl;
    //call the transpose method of the m5 matrix object to change the matrix into its transpose
    m5.transpose();
    //call the m5 object printMatrix method to display the matrix, (now representing the transpose of the original matrix
    m5.printMatrix();

    //add method tests
    cout << "add tests: " << endl
         << "test one should print out " << endl
         << "-7 81" << endl
         << "38 -32" << endl
         << "test prints out: " << endl;
    //call the m4 object add method with m5 object as input, in order to add them both and store the result in the m4
    //object
    m4.add(m5);
    //call the m4 object printMatrix method to display the matrix, (now the addition of the m4 and m5 matrices)
    m4.printMatrix();
    cout << "add tests: " << endl
         << "test one should print out " << endl
         << "7 2" << endl
         << "10.5 0.5" << endl
         << "test prints out: " << endl;
    //call the m3 object add method with m6 object as input, in order to add them both and store the result in the m3
    //object
    m3.add(m6);
    //call the m3 object printMatrix method to display the matrix, (now the addition of the m3 and m6 object matrices)
    m3.printMatrix();

    //multiply method tests
    cout << "add tests: " << endl
         << "test one should print out " << endl
         << "801.5 26.5" << endl
         << "-70 60" << endl
         << "test prints out: " << endl;
    //call the m4 object multiply method with m3 object as an input, in order to multiply both matrices,and have the
    //result be stored in the m4 object
    m4.multiply(m3);
    //call the m4 object printMatrix method to display the matrix, (now the resultant matrix of the multiplication of
    //the m4 and m3 matrices)
    m4.printMatrix();
    cout << "add tests: " << endl
         << "test one should print out " << endl
         << "468 52" << endl
         << "252 28" << endl
         << "test prints out: " << endl;
    //call the m5 object multiply method with m6 object as an input, in order to multiply both matrices, and have the
    //result be stored in the m5 object
    m5.multiply(m6);
    //call the m5 object printMatrix method to display the matrix, (now the resultant matrix of the multiplication of
    //the m5 and m6 matrices)
    m5.printMatrix();


    return 0;
}
