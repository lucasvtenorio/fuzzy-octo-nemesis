//
//  Transformation.h
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//



#ifndef __Render__Transform__
#define __Render__Transform__

#include "Matrix.h"

#include "Point3D.h"
#include "Vector3D.h"

namespace geometry{
    class Transformation{
    private:
        math::Matrix trans;

    public:
        Transformation(const math::Matrix & m);

        void append(const Transformation & t);

        Point3D apply(const Point3D & p) const;
        Vector3D apply(const Vector3D & p) const;

        void print(){
            trans.print();
        }

        static Transformation Translation(double x, double y, double z);
        static Transformation Scale(double x, double y, double z);
        static Transformation Rotation(Vector3D rotationAxis, double radAngle);
        static Transformation Projection(Vector3D planeNormal, Point3D planePosition);
        static Transformation Reflection(Vector3D planeNormal, Point3D planePosition);
    };
}

#endif /* defined(__Render__Transform__) */
