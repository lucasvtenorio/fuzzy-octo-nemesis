//
//  Reader.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Reader.h"

#include "stdio.h"

namespace io {
    rendering::PerspectiveCamera Reader::readCamera(const char * filePath) {
        FILE *file = fopen(filePath, "r");

        double x, y, z;
        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Point3D position(x , y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Vector3D head(x, y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Vector3D direction(x, y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        double focalDistance = x;
        double cameraWidth = y;
        double cameraHeight = z;
        
        return rendering::PerspectiveCamera(position, direction, head, focalDistance, cameraWidth, cameraHeight);
    }
}


