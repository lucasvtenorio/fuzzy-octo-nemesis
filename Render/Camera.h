//
//  Camera.h
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Camera__
#define __Render__Camera__

#include "Point3D.h"
#include "Point2D.h"
#include "Vector3D.h"

namespace rendering{
    class Camera{
    private:
        geometry::Point3D position;
        geometry::Vector3D direction;
        geometry::Vector3D head;

        double focalDistance;
        double cameraWidth;
        double cameraHeight;

    public:
        Camera(const geometry::Point3D & position, const geometry::Vector3D & direction, const geometry::Vector3D & head, double focalDistance, double cameraWidth, double cameraHeight);
        
        geometry::Point2D doTheDance(geometry::Point3D point);
    };
}

#endif /* defined(__Render__Camera__) */
