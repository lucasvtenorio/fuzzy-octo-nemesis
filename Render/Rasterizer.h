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
#include "dispatch/dispatch.h"
typedef void(^RenderCallback)(void);
namespace drawing{
    class Rasterizer{
    private:
        Canvas * canvas;
        double * _zbuffer;
        int * xBegin, *xEnd;
        int width, height;
        
        double MAX_DEPTH;

        inline void setMin(int y, int x);
        inline void setMax(int y, int x);

        bool intersectWithScreen(const geometry::Point2D & aa, const geometry::Point2D & bb, geometry::Point2D & ret, int k);
        void fillPointList(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c, std::vector<geometry::Point2D> & list);
        
        inline int clampScreen(int a);
        void drawLine(int x0, int y0, int x1, int y1, double z, const drawing::Color & color);
        void calcLine(int x0, int y0, int x1, int y1, bool mini);
        bool inScreen(const geometry::Point2D & a);
        void rasterizeTriangle(geometry::Point2D a, geometry::Point2D b, geometry::Point2D c);

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
        
        void resetZBuffer();
        inline bool outaSight(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c) ;
        
    public:
        Rasterizer(Canvas * canvas, double SET_MAX_DEPTH=1e9);
        ~Rasterizer();
        
        /*
         Metodo mais importante do projeto
         Assume que o zBuffer ja foi resetado e que todas as normais dos Meshs ja foram calculadas
        */
        void rasterize(rendering::World * world, rendering::Camera * camera);

        void rasterizeAsync(rendering::World * world, rendering::Camera * camera, RenderCallback  callBack);
    };
}

#endif /* defined(__Render__Rasterizer__) */
