//
//  AWCanvas.cpp
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Canvas.h"

namespace drawing {
#pragma mark -
#pragma mark Init/End

    Canvas::Canvas(int width, int height){
        this->width = width;
        this->height = height;

        this->buffer = (unsigned char *) malloc(sizeof(unsigned char) * 4 * width * height);
    }
    Canvas::~Canvas() {
        free(this->buffer);
    }

#pragma mark -
#pragma mark Getters
    int Canvas::getWidth() {
        return this->width;
    }
    int Canvas::getHeight() {
        return this->height;
    }
    unsigned char * Canvas::getBuffer() {
        return this->buffer;
    }


#pragma mark -
#pragma mark Util
    inline void swap(int *a, int *b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }

#pragma mark -
#pragma mark Painting

    inline void Canvas::draw(int x, int y, drawing::Color color){
        if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
            return;
        }
        buffer[x * 4 + y * this->width * 4] = color.r;
        buffer[(x * 4 + y * this->width * 4)  + 1] = color.g;
        buffer[(x * 4 + y * this->width * 4)  + 2] = color.b;
        buffer[(x * 4 + y * this->width * 4)  + 3] = color.a;
    }

    void Canvas::drawLine(int x0, int y0, int x1, int y1, drawing::Color color) {
        bool steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep) {
            swap(&x0, &y0);
            swap(&x1, &y1);
        }

        if (x0 > x1) {
            swap(&x1, &x0);
            swap(&y1, &y0);
        }
        int dx = x1 - x0;
        int dy = abs(y1 - y0);

        int error = dx / 2;
        int ystep;
        int y = y0;

        if (y0 < y1) {
            ystep = 1;
        } else {
            ystep = -1;
        }
        for (int x = x0; x < x1; x++) {
            if (steep) {
                this->draw(y, x, color);
            }else {
                this->draw(x, y, color);
            }
            error = error - dy;
            
            if (error < 0) {
                y = y  + ystep;
                error = error +dx;
            }
        }
    }
}




