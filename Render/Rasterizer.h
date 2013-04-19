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
        
        void resetZBuffer();
    public:
        Rasterizer(Canvas * canvas, double SET_MAX_DEPTH=1e9);
        ~Rasterizer();
        
        //Metodo mais importante do projeto
        void rasterize(rendering::World * world, rendering::Camera camera);
    };
}

#endif /* defined(__Render__Rasterizer__) */
