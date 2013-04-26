//
//  PerspectiveCamera.h
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__PerspectiveCamera__
#define __Render__PerspectiveCamera__

#include "Camera.h"

namespace rendering{

    class PerspectiveCamera : public Camera{
        protected:
            double focalDistance;
            double cameraWidth;
            double cameraHeight;
        
        public:
            PerspectiveCamera(const geometry::Point3D & position, const geometry::Vector3D & direction, const geometry::Vector3D & head, double focalDistance, double cameraWidth, double cameraHeight);
        
            geometry::Point2D doTheDance(geometry::Point3D point);
    };
}

#endif /* defined(__Render__PerspectiveCamera__) */
