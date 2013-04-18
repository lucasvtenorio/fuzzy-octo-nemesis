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
        protected:
            geometry::Point3D position;
            geometry::Vector3D direction;
            geometry::Vector3D head;

        public:
            Camera(const geometry::Point3D & position, const geometry::Vector3D & direction, const geometry::Vector3D & head);
            
            virtual geometry::Point2D doTheDance(geometry::Point3D point) =0;
    };
}

#endif /* defined(__Render__Camera__) */
