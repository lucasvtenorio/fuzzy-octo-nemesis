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
        this->cameraWidth = cameraWidth;
        this->cameraHeight = cameraHeight;
    }
}