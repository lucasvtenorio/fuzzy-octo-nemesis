//
//  Vector.cpp
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Vector.h"

#include <cassert>
#include <cmath>

namespace math{
    Vector::Vector(int n) : Matrix(n, 1){

    }

    Vector::Vector(const Matrix & m) : Matrix(m.rowCount(), 1){
        for(int i = 0; i < m.rowCount(); i++){
            (*this)(i) = m(i, 0);
        }
    }

    double Vector::operator*(const Vector & v) const{
        double ret = 0;
        for(int i = 0; i < dimension(); i++){
            ret += (*this)(i) * v(i);
        }
        return ret;
    }

    double Vector::length() const{
        return sqrt((*this)*(*this));
    }

    Vector Vector::normalized() const{
        if(length() == 0){
            return (*this);
        }
        return (*this)/length();
    }

    Vector Vector::projection(const Vector & v) const{
        if(v.length() == 0){
            return Vector(dimension());
        }

        double k = ((*this)*v)/(v*v);
        return v*k;
    }
}
