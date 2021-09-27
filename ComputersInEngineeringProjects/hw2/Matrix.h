// Created by rlrangeldelatejera on 2/14/2021.
// Class name: Matrix
// Description: class that holds methods to perform basic matrix operations
//Method definitions are in Matrix.cpp
// #include "Matrix.h" to use this class in your main.cpp

#ifndef HW2_MATRIX_H
#define HW2_MATRIX_H

#endif //HW2_MATRIX_H


class Matrix{
public:
    //constructor to set the private members to valid values to build elements of a 2x2 matrix,a default value
    // of 0 is assign to the inputs that are missing
    //the matrix is build by taking element one as the first entry, element 2 as the second, and so on
    //forming a matrix of the type:
    //element1 element2
    //element3 element4
    explicit Matrix(double element1 = 0, double element2 = 0, double element3 = 0, double element4 = 0):
    m_element1{element1},m_element2{element2},m_element3{element3},m_element4{element4}{
    };

    //setter methods
    //description: one setter for each private member that assigns a value to each of the member (one for each member)
    //input: double value to be assigned to the member
    //output: none (void)
    void setElement1(double element1){m_element1 = element1;};

    void setElement2(double element2){m_element2 = element2;};

    void setElement3(double element3){m_element3 = element3;};

    void setElement4(double element4){m_element4 = element4;};

    //getter methods
    //description: one getter for each private member that returns the current value of each object member
    //input: none
    //output: double variable that is the current value of the objects member
    double getElement1() const{return m_element1;};

    double getElement2() const{return m_element2;};

    double getElement3() const{return m_element3;};

    double getElement4() const{return m_element4;};

    //Description: method that prints the 2x2 matrix to the screen using the current values of the private members
    //input: none, it uses the values of the private members of the object(elements of the matrix)
    //output: no variable is returned, but it prints to the terminal the 2x2 matrix in the form:
    //element1 element2
    //element3 element4
    void printMatrix()const;

    //Description: method that computes and returns the determinant of the 2x2 matrix
    //input: none, it uses the values of the private members of the object
    //output: returns the determinant of the matrix, a variable of type double
    double determinant()const;

    //Description: method that changes the matrix into its inverse, by changing the values of the private members into the
    //new elements of the inverse function
    //input: none, it uses the values of the private members of the object
    //output: no variable is returned,just the matrix is changed into the inverse, but if the inverse of the matrix doesn't
    //exist, it prints an error statement saying that the matrix doesn't have an inverse
    void inverse();

    //Description: method that changes the matrix into it's transpose matrix
    //input: none, it uses the current matrix
    //output: none, because it just changes the matrix into its transpose
    void transpose();

    //Description:method that adds to functions together, and rewrites the matrix object that called the method into the
    //resultant matrix of the addition
    //input: a matrix object (to be added to the current matrix object)
    //output:none, it just changes the current matrix into the result of the matrices addition
    void add(Matrix A);

    //Description:method that multiplies two matrices, the current one calling the method, and one input matrix object,
    // and changes the private member values of the current matrix into the result of the multiplication
    //input: matrix object
    //output:none, it just changes the current matrix object into the resultant matrix of the multiplication
    void multiply(Matrix A);

private:
    //definition of four private members to be assigned the value of each element in the 2x2 matrix
    double m_element1;
    double m_element2;
    double m_element3;
    double m_element4;

};



