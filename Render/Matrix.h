//
//  Matrix.h
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Matrix__
#define __Render__Matrix__

#include <cstdio>

namespace math{
    template <class Number>
    class Matrix {
    private:

        int row, column;
        Number ** data;
        void clear(){
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

    public:

        static Matrix<Number> createIdentity(int n){
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
        }
        
        Matrix(int row, int column){
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

        Matrix(const Matrix<Number> & m){
            this->data = new Number*[m.rowCount()];
            for (int i = 0; i < m.rowCount(); i++) {
                this->data[i] = new Number[m.columnCount()];
                for (int j = 0; j < m.columnCount(); j++) {
                    this->data[i][j] = m.data[i][j];
                }
            }
        }

        Matrix<Number>& operator=(const Matrix<Number> & m){
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

        virtual ~Matrix(){
            this->clear();
        }

        inline int rowCount() const{
            return this->row;
        }

        inline int columnCount() const{
            return this->column;
        }

        Number& operator()(int i, int j){
            return this->data[i][j];
        }

        Matrix<Number> operator+(const Matrix<Number> & m) const{
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
        
        Matrix<Number> operator-(const Matrix<Number> & m) const{
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
        
        Matrix<Number> operator*(const Matrix<Number> & m) const{
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
        
        Matrix<Number> operator*(const Number & m) const{
            Matrix<Number> ret = Matrix<Number>(this->rowCount(), this->columnCount());
            for(int i = 0; i < ret.rowCount(); i++){
                for(int j = 0; j < ret.columnCount(); j++){
                    ret.data[i][j] = this->data[i][j]*m;
                }
            }

            return ret;
        }
        Matrix<Number> operator/(const Number & m) const{
            Matrix<Number> ret = Matrix<Number>(this->rowCount(), this->columnCount());
            for(int i = 0; i < ret.rowCount(); i++){
                for(int j = 0; j < ret.columnCount(); j++){
                    ret.data[i][j] = this->data[i][j]/m;
                }
            }

            return ret;
        }

        void print(){
            for(int i = 0; i < this->rowCount(); i++){
                for(int j = 0; j < this->columnCount(); j++){
                    printf("%.2lf ", this->data[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    };

}


#endif /* defined(__Render__Matrix__) */
