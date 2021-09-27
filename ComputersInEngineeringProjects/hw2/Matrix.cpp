// Created by rlrangeldelatejera on 2/14/2021.
// Class method definitions for Matrix class
//Matrix.h is the header file
// Description: class that holds methods to perform basic matrix operations

#include "Matrix.h"
#include "iostream"

using namespace std;

    //Description: method that prints the 2x2 matrix to the screen using the current values of the private members
    //input: none, it uses the values of the private members of the object(elements of the matrix)
    //output: no variable is returned, but it prints to the terminal the 2x2 matrix in the form:
    //element1 element2
    //element3 element4
    void Matrix::printMatrix() const{
        cout << m_element1 << " " << m_element2 << endl
             << m_element3 << " " << m_element4 << endl;
    }

    //Description: method that computes and returns the determinant of the 2x2 matrix
    //input: none, it uses the values of the private members of the object
    //output: returns the determinant of the matrix, a variable of type double
    double Matrix::determinant() const{
        double determinant = (m_element1 * m_element4) - (m_element3 * m_element2);
        return determinant;
    }

    //Description: method that changes the matrix into its inverse, by changing the values of the private members into the
    //new elements of the inverse function
    //input: none, it uses the values of the private members of the object
    //output: no variable is returned,just the matrix is changed into the inverse, but if the inverse of the matrix doesn't
    //exist, it prints an error statement saying that the matrix doesn't have an inverse
    void Matrix::inverse() {
        double element1ForInverse;
        double element2ForInverse;
        double element3ForInverse;
        double element4ForInverse;
        double determinant = Matrix::determinant();
        if (determinant != 0)
        {
            element1ForInverse = m_element4/determinant;
            element4ForInverse = m_element1/determinant;
            element2ForInverse = (m_element2 * -1)/determinant;
            element3ForInverse = (m_element3 * -1)/determinant;

            m_element1 = element1ForInverse;
            m_element2 = element2ForInverse;
            m_element3 = element3ForInverse;
            m_element4 = element4ForInverse;

        }
        else
        {
            cout << "Error, matrix is not invertible " << endl;
        }
    }

    //Description: method that changes the matrix into it's transpose matrix
    //input: none, it uses the current matrix
    //output: none, because it just changes the matrix into its transpose
    void Matrix::transpose(){
        double elementForTranspose2 = m_element3;
        double elementForTranspose3 = m_element2;
        m_element2 = elementForTranspose2;
        m_element3 = elementForTranspose3;
    }

    //Description:method that adds to functions together, and rewrites the matrix object that called the method into the
    //resultant matrix of the addition
    //input: a matrix object (to be added to the current matrix object)
    //output:none, it just changes the current matrix into the result of the matrices addition
    void Matrix::add(Matrix A) {
        m_element1 = m_element1 + A.m_element1;
        m_element2 = m_element2 + A.m_element2;
        m_element3 = m_element3 + A.m_element3;
        m_element4 = m_element4 + A.m_element4;
    }

    //Description:method that multiplies two matrices, the current one calling the method, and one input matrix object,
    // and changes the private member values of the current matrix into the result of the multiplication
    //input: matrix object
    //output:none, it just changes the current matrix object into the resultant matrix of the multiplication
    void Matrix::multiply(Matrix A) {
        double multiplicationElement1 = (m_element1 * A.m_element1) + (m_element2 * A.m_element3);
        double multiplicationElement2 = (m_element1 * A.m_element2) + (m_element2 * A.m_element4);
        double multiplicationElement3 = (m_element3 * A.m_element1) + (m_element4 * A.m_element3);
        double multiplicationElement4 = (m_element3 * A.m_element2) + (m_element4 * A.m_element4);
        m_element1 = multiplicationElement1;
        m_element2 = multiplicationElement2;
        m_element3 = multiplicationElement3;
        m_element4 = multiplicationElement4;
    }