//
//  Matrix.cpp
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Matrix.h"

#include <cassert>
#include <cstdio>

namespace math{

    template<class Number>
    Matrix<Number> Matrix<Number>::createIdentity(int n){
        Matrix<Number> identity(n, n);
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
    };


    template<class Number>
    void Matrix<Number>::clear(){
        if(this->data != nullptr){
            for(int i = 0; i < this->rowCount(); i++){
                if(this->data[i] != nullptr){
                    delete[] this->data[i];
                    this->data[i] = nullptr;
                }
            }
            delete[] this->data;
            this->data = nullptr;
        }
        this->row = 0;
        this->column = 0;
    }

    template<class Number>
    Matrix<Number>::Matrix(int row, int column) {
        if(row == 0 || column == 0){
            this->data = nullptr;
            this->row = 0;
            this->column = 0;
        } else{
            this->data = new Number*[row];
            for (int i = 0; i < row; i++) {
                this->data[i] = new Number[column];
            }
            this->row = row;
            this->column = column;
        }
    }

    template<class Number>
    Matrix<Number>::Matrix(const Matrix<Number> & m){
        this->data = new Number*[m.rowCount()];
        for (int i = 0; i < m.rowCount(); i++) {
            this->data[i] = new Number[m.columnCount()];
            for (int j = 0; j < m.columnCount(); j++) {
                this->data[i][j] = m.data[i][j];
            }
        }
    }

    template<class Number>
    Matrix<Number> & Matrix<Number>::operator=(const Matrix & m){
        if(this != &m){
            if(this->rowCount() != m.rowCount() || this->columnCount() != m.columnCount()){
                this->clear();
                this->data = new Number*[m.rowCount()];
                for (int i = 0; i < m.rowCount(); i++) {
                    this->data[i] = new Number[m.columnCount()];
                    for (int j = 0; j < m.columnCount(); j++) {
                        this->data[i][j] = m.data[i][j];
                    }
                }
            } else{
                for (int i = 0; i < m.rowCount(); i++) {
                    for (int j = 0; j < m.columnCount(); j++) {
                        this->data[i][j] = m.data[i][j];
                    }
                }
            }
        }
        return *this;
    }

    template<class Number>
    Matrix<Number>::~Matrix(){
        this->clear();
    }

    template<class Number>
    Matrix<Number> Matrix<Number>::operator+(const Matrix<Number> & m) const{
        assert(this->rowCount() == m.rowCount());
        assert(this->columnCount() == m.columnCount());

        Matrix<Number> ret = Matrix<Number>(this->rowCount(), this->columnCount());
        for(int i = 0; i < ret.rowCount(); i++){
            for(int j = 0; j < ret.columnCount(); j++){
                ret.data[i][j] = this->data[i][j] + m.data[i][j];
            }
        }

        return ret;
    }

    template<class Number>
    Matrix<Number> Matrix<Number>::operator-(const Matrix<Number> & m) const{
        assert(this->rowCount() == m.rowCount());
        assert(this->columnCount() == m.columnCount());

        Matrix<Number> ret = Matrix<Number>(this->rowCount(), this->columnCount());
        for(int i = 0; i < ret.rowCount(); i++){
            for(int j = 0; j < ret.columnCount(); j++){
                ret.data[i][j] = this->data[i][j] - m.data[i][j];
            }
        }

        return ret;
    }

    template<class Number>
    Matrix<Number> Matrix<Number>::operator*(const Matrix<Number> & m) const{
        assert(this->columnCount() == m.rowCount());

        Matrix<Number> ret = Matrix<Number>(this->rowCount(), m.columnCount());
        for(int i = 0; i < ret.rowCount(); i++){
            for(int j = 0; j < ret.columnCount(); j++){
                ret.data[i][j] = 0;
                for(int k = 0; k < this->columnCount(); k++){
                    ret.data[i][j] = ret.data[i][j] + this->data[i][k] * m.data[k][j];
                }
            }
        }

        return ret;
    }

    template<class Number>
    Matrix<Number> Matrix<Number>::operator*(const Number & m) const{
        Matrix<Number> ret = Matrix<Number>(this->rowCount(), this->columnCount());
        for(int i = 0; i < ret.rowCount(); i++){
            for(int j = 0; j < ret.columnCount(); j++){
                ret.data[i][j] = this->data[i][j]*m;
            }
        }

        return ret;
    }

    template<class Number>
    Matrix<Number> Matrix<Number>::operator/(const Number & m) const{
        Matrix<Number> ret = Matrix<Number>(this->rowCount(), this->columnCount());
        for(int i = 0; i < ret.rowCount(); i++){
            for(int j = 0; j < ret.columnCount(); j++){
                ret.data[i][j] = this->data[i][j]/m;
            }
        }

        return ret;
    }

    template<class Number>
    void Matrix<Number>::print(){
        for(int i = 0; i < this->rowCount(); i++){
            for(int j = 0; j < this->columnCount(); j++){
                printf("%.2lf ", this->data[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


int my_main(){
    printf("Hello, world!\n");
    math::Matrix<double> m(3, 3);
    math::Matrix<double> m2(3, 3);
    double t = 1;
    for(int i = 0; i < m.rowCount(); i++){
        for(int j = 0; j < m.columnCount(); j++){
            m(i, j) = t;
            m2(i, j) = t;
            t++;
        }
    }
    math::Matrix<double> m3 = math::Matrix<double>::createIdentity(4);
    m.print();
    m2.print();
    m3.print();
    return 0;
}
































