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

    Camera::Camera(const Point3D & position, const Vector3D & direction, const Vector3D & head, double focalDistance, double cameraWidth, double cameraHeight){
        this->position = position;
        this->direction = direction;
        this->focalDistance = focalDistance;
        this->cameraWidth = cameraWidth;
        this->cameraHeight = cameraHeight;

        math::Vector d = direction.asVector();
        math::Vector h = head.asVector();
        h = h - h.projection(d);
        this->head = Vector3D(h(0), h(1), h(2));
    }
}