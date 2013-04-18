//
//  Triangle.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Triangle__
#define __Render__Triangle__

#include "Point3D.h"
#include "Vector3D.h"

namespace geometry {
    class Triangle {
    private:
        Point3D aa;
        Point3D bb;
        Point3D cc;
    public:
        Triangle(Point3D a, Point3D b, Point3D c);

        inline Point3D & a(){
            return aa;
        }

        inline const Point3D & a() const{
            return aa;
        }

        inline Point3D & b(){
            return bb;
        }

        inline const Point3D & b() const{
            return bb;
        }

        inline Point3D & c(){
            return cc;
        }

        inline const Point3D & c() const{
            return cc;
        }

        inline Vector3D getNormal() const;
    };
}

#endif /* defined(__Render__Triangle__) */
