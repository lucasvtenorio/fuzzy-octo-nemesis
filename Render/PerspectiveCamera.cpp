//
//  PerspectiveCamera.cpp
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "PerspectiveCamera.h"

namespace rendering{
    using namespace geometry;
    
    PerspectiveCamera::PerspectiveCamera(const Point3D & position, const Vector3D & direction, const Vector3D & head, double focalDistance, double cameraWidth, double cameraHeight) : Camera(position, direction, head){

        this->focalDistance = focalDistance;
        this->cameraWidth = cameraWidth/2;
        this->cameraHeight = cameraHeight/2;
    }

    Point2D PerspectiveCamera::doTheDance(Point3D point) {
        math::Vector p = point.asVector() - position.asVector();
        double x = p*lateral.asVector();
        double y = p*head.asVector();
        double z = p*direction.asVector();

        double fx = ((x*this->focalDistance)/(z*this->cameraWidth) + 1)/2;
        double fy = ((y*this->focalDistance)/(z*this->cameraHeight) + 1)/2;

        return Point2D(fx, fy, z);
    }
}