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

namespace math{
    
    class Vector : public Matrix {

    private:

    public:
        Vector(int n);

        Vector(const Matrix & m);

        inline double & operator()(int i){
            return Matrix::operator()(i, 0);
        }

        inline const double & operator()(int i) const{
            return this->data[i];
        }

        inline int dimension() const{
            return this->rowCount();
        }

        Vector operator*(double k) const;
        double operator*(const Vector & v) const;

        double length() const;

        inline double operator!() const{
            return this->length();
        }

        Vector normalized() const;
        Vector projection(const Vector & v) const;

    };
}

#endif /* defined(__Render__Vector__) */
