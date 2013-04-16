//
//  Matrix.cpp
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Matrix.h"

#include <cstdio>
#include <cassert>

using namespace math;

Matrix Matrix::createIdentity(int n) {
    Matrix identity(n, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){
                identity(i, j) = 1;
            } else{
                identity(i, j) = 0;
            }
        }
    }
    return identity;
}

#pragma mark -
#pragma mark Constructors
Matrix::Matrix(int row, int column) {
    if(row == 0 || column == 0){
        this->data = nullptr;
        this->row = 0;
        this->column = 0;
    } else{
        this->data = new double[row * column];
        this->row = row;
        this->column = column;
    }
}
Matrix::Matrix(const Matrix & m) {
    
    this->data = new double[m.rowCount() * m.columnCount()];
    this->column = m.columnCount();
    this->row = m.rowCount();
    for (int i = 0; i < m.rowCount(); i++) {
        for (int j = 0; j < m.columnCount(); j++) {
            
            (*this)(i, j) = m(i, j);
        }
    }
}

#pragma mark -
#pragma mark Operators

Matrix& Matrix::operator=(const Matrix & m) {
    if(this != &m){
        if(this->rowCount() != m.rowCount() || this->columnCount() != m.columnCount()){
            this->clear();
            this->column = m.columnCount();
            this->row = m.rowCount();
            this->data = new double[this->rowCount() * this->columnCount()];
            for (int i = 0; i < m.rowCount(); i++) {
                for (int j = 0; j < m.columnCount(); j++) {
                    (*this)(i, j) = m(i, j);
                }
            }
        } else{
            for (int i = 0; i < m.rowCount(); i++) {
                for (int j = 0; j < m.columnCount(); j++) {
                    (*this)(i,j) = m(i,j);
                }
            }
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix & m) const{
    assert(this->rowCount() == m.rowCount());
    assert(this->columnCount() == m.columnCount());

    Matrix ret(this->rowCount(), this->columnCount());
    for(int i = 0; i < ret.rowCount(); i++){
        for(int j = 0; j < ret.columnCount(); j++){
            ret(i, j) = (*this)(i, j) + m(i, j);
        }
    }

    return ret;
}

Matrix Matrix::operator-(const Matrix & m) const{
    assert(this->rowCount() == m.rowCount());
    assert(this->columnCount() == m.columnCount());

    Matrix ret(this->rowCount(), this->columnCount());
    for(int i = 0; i < ret.rowCount(); i++){
        for(int j = 0; j < ret.columnCount(); j++){
            ret(i, j) = (*this)(i, j) - m(i, j);
        }
    }

    return ret;
}


Matrix Matrix::operator*(const Matrix & m) const{
    assert(this->columnCount() == m.rowCount());

    Matrix ret(this->rowCount(), this->columnCount());
    for(int i = 0; i < ret.rowCount(); i++){
        for(int j = 0; j < ret.columnCount(); j++){
            ret(i, j) = 0;
            for(int k = 0; k < this->columnCount(); k++){
                ret(i, j) = ret(i, j) + (*this)(i, k) * m(k, j);
            }
        }
    }
    return ret;
}

Matrix Matrix::operator*(double m) const {
    Matrix ret(this->rowCount(), this->columnCount());
    
    for(int i = 0; i < ret.rowCount(); i++){
        for(int j = 0; j < ret.columnCount(); j++){
            ret(i ,j) = (*this)(i, j) * m;
        }
    }

    return ret;
}

Matrix Matrix::operator/(double m) const{
     Matrix ret(this->rowCount(), this->columnCount());
    for(int i = 0; i < ret.rowCount(); i++){
        for(int j = 0; j < ret.columnCount(); j++){
            ret(i, j) = (*this)(i, j)/m;
        }
    }

    return ret;
}

#pragma mark -
#pragma mark Util

void Matrix::print() const{
    for(int i = 0; i < this->rowCount(); i++){
        for(int j = 0; j < this->columnCount(); j++){
            printf("%.2lf ", (*this)(i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void Matrix::clear() {
    if(this->data != nullptr){
        delete[] this->data;
        this->data = nullptr;
    }
    this->row = 0;
    this->column = 0;
}

















