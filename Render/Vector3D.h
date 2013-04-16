//
//  Vector3D.h
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Vector3D__
#define __Render__Vector3D__

#include "Vector.h"

namespace geometry{
    class Vector3D{
    private:
        math::Vector v;
    public:
        Vector3D(double x=0, double y=0, double z=0);

        inline double & x(){
            return v(0);
        }

        inline const double & x() const{
            return v(0);
        }

        inline double & y(){
            return v(1);
        }

        inline const double & y() const{
            return v(1);
        }

        inline double & z(){
            return v(2);
        }

        inline const double & z() const{
            return v(2);
        }

        inline math::Vector asVector() const{
            math::Vector ret(3);
            ret(0) = x(), ret(1) = y(), ret(2) = z();
            return ret;
        }

        void print(){
            v.print();
        }

        friend class Transformation;
    };
}

#endif /* defined(__Render__Vector3D__) */
