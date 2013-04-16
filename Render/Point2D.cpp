//
//  Point2D.cpp
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Point2D.h"
namespace geometry{
    Point2D::Point2D(double x, double y):v(3){
        v(0) = x;
        v(1) = y;
        v(2) = 1;
    }
}