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
    template <class Number>
    class Matrix {
    private:

        int row, column;
        Number ** data;
        void clear();

    public:

        static Matrix<Number> createIdentity(int n);
        
        Matrix(int row, int column);
        Matrix(const Matrix<Number> & m);
        Matrix<Number>& operator=(const Matrix<Number> & m);

        virtual ~Matrix();

        inline int rowCount() const{
            return this->row;
        }

        inline int columnCount() const{
            return this->column;
        }

        Number& operator()(int i, int j){
            return this->data[i][j];
        }

        Matrix<Number> operator+(const Matrix<Number> & m) const;
        Matrix<Number> operator-(const Matrix<Number> & m) const;
        Matrix<Number> operator*(const Matrix<Number> & m) const;
        
        Matrix<Number> operator*(const Number & m) const;
        Matrix<Number> operator/(const Number & m) const;

        void print();
    };

}
int my_main();


#endif /* defined(__Render__Matrix__) */
