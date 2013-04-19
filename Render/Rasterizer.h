//
//  Rasterizer.h
//  Render
//
//  Created by Rafael Farias Marinheiro on 19/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Rasterizer__
#define __Render__Rasterizer__

#include "Canvas.h"
#include "World.h"
#include "Camera.h"

namespace drawing{
    class Rasterizer{
    private:
        Canvas * canvas;
        double * _zbuffer;
        int width, height;
        
        double MAX_DEPTH;
        
        inline bool valid(int x, int y){
            return (0 <= x && x < width && 0 <= y && y < height);
        }
        
        inline double & zbuffer(int x, int y){
            return _zbuffer[y*width + x];
        }
        
        inline void drawPixel(int x, int y, double z, const Color & color){
            if(valid(x, y) && z < zbuffer(x, y)){
                canvas->draw(x, y, color);
                zbuffer(x, y) = z;
            }
        }
        
        math::Vector getBaricentricCoordinates(geometry::Point2D p, geometry::Point2D a, geometry::Point2D b, geometry::Point2D c);
        
        void resetZBuffer();
        bool collinear(geometry::Point2D a, geometry::Point2D b, geometry::Point2D c);
        geometry::Point3D interpolate(math::Vector baricentric, geometry::Point3D a, geometry::Point3D b, geometry::Point3D c);
        geometry::Vector3D interpolate(math::Vector baricentric, geometry::Vector3D a, geometry::Vector3D b, geometry::Vector3D c);
        
        rendering::ColorVector calculateDiffuse(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal);
        
        rendering::ColorVector calculateSpecular(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal);
        
        rendering::ColorVector calculateAmbient(rendering::World * world);
        
    public:
        Rasterizer(Canvas * canvas, double SET_MAX_DEPTH=1e9);
        ~Rasterizer();
        
        /*
         Metodo mais importante do projeto
         Assume que o zBuffer ja foi resetado e que todas as normais dos Meshs ja foram calculadas
        */
        void rasterize(rendering::World * world, rendering::Camera * camera);
    };
}

#endif /* defined(__Render__Rasterizer__) */
