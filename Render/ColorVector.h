//
//  ColorVector.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__ColorVector__
#define __Render__ColorVector__

#include "Color.h"
#include "Vector.h"

namespace rendering{

    class ColorVector : public math::Vector{
    public:
        ColorVector(double r=255.0, double g=255.0, double b=255.0, double a=255.0);
        ColorVector(const math::Matrix & v);
        
        drawing::Color clip() const;

        inline double & r(){
            return (*this)(0);
        }

        inline const double & r() const{
            return (*this)(0);
        }

        inline double & g(){
            return (*this)(1);
        }

        inline const double & g() const{
            return (*this)(1);
        }

        inline double & b(){
            return (*this)(2);
        }

        inline const double & b() const{
            return (*this)(2);
        }

        inline double & a(){
            return (*this)(3);
        }

        inline const double & a() const{
            return (*this)(3);
        }

    };
}

#endif /* defined(__Render__ColorVector__) */
