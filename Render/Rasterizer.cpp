//
//  Rasterizer.cpp
//  Render
//
//  Created by Rafael Farias Marinheiro on 19/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Rasterizer.h"

namespace drawing{
    Rasterizer::Rasterizer(Canvas * canvas, double SET_MAX_DEPTH){
        this->canvas = canvas;
        this->width = canvas->getWidth();
        this->height = canvas->getHeight();
        this->MAX_DEPTH = SET_MAX_DEPTH;
        this->_zbuffer = (double *) malloc(sizeof(double) *width * height);
    }
    
    Rasterizer::~Rasterizer(){
        free(this->_zbuffer);
        this->_zbuffer = nullptr;
    }
    
    void Rasterizer::resetZBuffer(){
        for(int i = 0; i < width*height; i++){
            this->_zbuffer[i] = MAX_DEPTH;
        }
    }
}