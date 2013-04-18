//
//  Triangle.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Triangle.h"

namespace geometry{
    Triangle::Triangle(Point3D a, Point3D b, Point3D c){
        this->aa = a;
        this->aa = b;
        this->aa = c;
    }

    Vector3D Triangle::getNormal() const{
        math::Vector a = bb.asVector() - aa.asVector();
        math::Vector b = cc.asVector() - aa.asVector();

        return Vector3D(a(0), a(1), a(2))%Vector3D(b(0), b(1), b(2));
    }
}