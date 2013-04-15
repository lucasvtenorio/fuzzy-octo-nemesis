//
//  Vector.h
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//


#ifndef __Render__Vector__
#define __Render__Vector__

#include "Matrix.h"

#include <cassert>
#include <cmath>

namespace math{
    template <class Number>
    class Vector : public Matrix<Number> {

    public:
        Vector(int n) : Matrix<Number>(n, 1){
            
        }

        Vector(Matrix<Number> m) : Matrix<Number>(m.rowCount(), 1){
            for(int i = 0; i < m.rowCount(); i++){
                this->operator()(i) = m(i, 0);
            }
        }

        Number & operator()(int i){
            return Matrix<Number>::operator()(i, 0);
        }

        int dimension(){
            return this->rowCount();
        }

        Vector<Number> operator*(const Vector<Number> & v){
            Number ret = 0;
            for(int i = 0; i < dimension(); i++){
                ret += (*this)(i)*v(i);
            }
            return ret;
        }

        Number length(){
            return sqrt((*this)*(*this));
        }

        Number operator!(){
            
        }

    };
}

#endif /* defined(__Render__Vector__) */
