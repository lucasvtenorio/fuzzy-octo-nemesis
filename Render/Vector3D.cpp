//
//  Vector3D.cpp
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Vector3D.h"

namespace geometry{
    Vector3D::Vector3D(double x, double y, double z):v(4){
        v(0) = x;
        v(1) = y;
        v(2) = z;
        v(3) = 0;
    }
}