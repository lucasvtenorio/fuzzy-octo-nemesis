//
//  ColorVector.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "ColorVector.h"

namespace rendering{
    ColorVector::ColorVector(double r, double g, double b, double a) : math::Vector(4){
        (*this)(0) = r, (*this)(1) = g, (*this)(2) = b, (*this)(3) = a;
    }

    drawing::Color ColorVector::clip() const{
        return drawing::Color(byte(r()), byte(g()), byte(b()), byte(a()));
    }
}