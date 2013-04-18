//
//  LightSource.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "LightSource.h"

namespace rendering{
    LightSource::LightSource(geometry::Point3D position, geometry::Vector3D direction, ColorVector color){
        this->pos = position;
        this->dir = direction;
        this->col = color;
    }
}