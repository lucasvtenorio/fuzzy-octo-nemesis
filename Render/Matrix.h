//
//  Matrix.h
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Matrix__
#define __Render__Matrix__

namespace math{
    class Matrix {
    private:

        int row, column;
        double * data;
        void clear();

    public:

        static Matrix createIdentity(int n);
        
        Matrix(int row, int column);

        Matrix(const Matrix & m);
        
        virtual ~Matrix(){
            this->clear();
        }

        inline int rowCount() const{
            return this->row;
        }

        inline int columnCount() const{
            return this->column;
        }
        
        inline double& operator()(int i, int j){
            return this->data[i * this->columnCount() + j];
        }
        
        inline const double& operator()(int i, int j) const{
            return this->data[i * this->columnCount() + j];
        }

        Matrix& operator=(const Matrix & m);
        Matrix operator+(const Matrix & m) const;
        Matrix operator-(const Matrix & m) const;
        Matrix operator*(const Matrix & m) const;
        Matrix operator*(double m) const;
        Matrix operator/(double m) const;
        void print() const;
    };

}


#endif /* defined(__Render__Matrix__) */
