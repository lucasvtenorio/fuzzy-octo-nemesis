//
//  Point2D.h
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Point2D__
#define __Render__Point2D__

#include "Vector.h"

namespace geometry{
    class Point2D{
    private:
        math::Vector v;
    public:
        Point2D(double x=0, double y=0, double d=1);

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

        inline double & depth(){
            return v(2);
        }

        inline const double & depth() const{
            return v(2);
        }

        inline math::Vector asVector() const{
            math::Vector ret(2);
            ret(0) = x(), ret(1) = y();
            return ret;
        }

        void print() const{
            v.print();
        }
        friend class Transformation;
    };
}

#endif /* defined(__Render__Point2D__) */
