//
//  LightSource.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__LightSource__
#define __Render__LightSource__

#include "Point3D.h"
#include "Vector3D.h"
#include "ColorVector.h"

namespace rendering{
    class LightSource{
    private:
        geometry::Point3D pos;
        geometry::Vector3D dir;
        ColorVector col;

    public:
        LightSource(geometry::Point3D position, geometry::Vector3D direction, ColorVector color);

        inline geometry::Point3D & position(){
            return pos;
        }

        inline const geometry::Point3D & position() const{
            return pos;
        }

        inline geometry::Vector3D & direction(){
            return dir;
        }

        inline const geometry::Vector3D & direction() const{
            return dir;
        }


        inline ColorVector & color(){
            return col;
        }

        inline const ColorVector & color() const{
            return col;
        }
        

    };
}
#endif /* defined(__Render__LightSource__) */
