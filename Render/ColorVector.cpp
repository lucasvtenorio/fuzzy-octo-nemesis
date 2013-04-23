//
//  ColorVector.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "ColorVector.h"

namespace rendering{
    double clamp(double val, double min=0, double max=255){
        if(val < min) return min;
        if(val > max) return max;
        return val;
    }
    
    ColorVector::ColorVector(double r, double g, double b, double a) : math::Vector(4){
        (*this)(0) = clamp(r), (*this)(1) = clamp(g), (*this)(2) = clamp(b), (*this)(3) = clamp(a);
    }
    
    ColorVector::ColorVector(const math::Matrix & v) : math::Vector(v){
        r() = clamp(r());
        g() = clamp(g());
        b() = clamp(b());
        a() = clamp(a());
    }


    
    drawing::Color ColorVector::clip() const{
        return drawing::Color(byte(clamp(r())), byte(clamp(g())), byte(clamp(b())), byte(clamp(a())));
    }
}