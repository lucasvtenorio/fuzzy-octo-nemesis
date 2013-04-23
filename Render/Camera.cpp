                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   //
//  Camera.cpp
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Camera.h"

#include "Vector.h"

namespace rendering{
    using namespace geometry;

    Camera::Camera(const Point3D & position, const Vector3D & direction, const Vector3D & head){
        this->_position = position;
        math::Vector d = direction.asVector().normalized();
        math::Vector h = head.asVector();

        h = h - h.projection(d);
        h = h.normalized();
        
        this->direction = Vector3D(d(0), d(1), d(2));
        this->head = Vector3D(h(0), h(1), h(2));
        this->lateral = (this->direction%this->head).normalized();
    }
}