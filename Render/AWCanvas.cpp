//
//  AWCanvas.cpp
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "AWCanvas.h"

#pragma mark -
#pragma mark Init/End

AWCanvas::AWCanvas(int width, int height){
    this->drawQueue = dispatch_queue_create("com.awesome.drawQueue", DISPATCH_QUEUE_SERIAL);
    this->width = width;
    this->height = height;
    dispatch_async(this->drawQueue, ^{
        this->buffer = (unsigned char *) malloc(sizeof(unsigned char) * 4 * width * height);
    });
}
AWCanvas::~AWCanvas() {
    dispatch_async(this->drawQueue, ^{
        free(this->buffer);
    });
}

#pragma mark -
#pragma mark Buffer Management
void resizeBuffer(){

}
#pragma mark -
#pragma mark Getters

void AWCanvas::getBuffer(void (^response)(unsigned char *buffer, int width, int height)) {
    dispatch_async(this->drawQueue, ^{
        response(this->buffer, this->width, this->height);
    });
}

void AWCanvas::getWidth(void (^response)(int width)){
    dispatch_async(this->drawQueue, ^{
        response(this->width);
    });
}
void AWCanvas::getHeight(void (^response)(int height)) {
    dispatch_async(this->drawQueue, ^{
        response(this->height);
    });
}

#pragma mark -
#pragma mark Setters

void AWCanvas::setWidth(int width) {
    dispatch_async(this->drawQueue, ^{
        this->width = width;

        buffer = (unsigned char *) malloc(sizeof(unsigned char) * 4 * this->width * this->height);
    });
}
void AWCanvas::setHeight(int height) {
    dispatch_async(this->drawQueue, ^{
        this->height = height;
        buffer = (unsigned char *) malloc(sizeof(unsigned char) * 4 * this->width * this->height);
    });
}
#pragma mark -
#pragma mark Util
inline void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
inline void AWCanvas::__draw(int x, int y, AWColor color){
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return;
    }
    buffer[x * 4 + y * this->width * 4] = color.r;
    buffer[(x * 4 + y * this->width * 4)  + 1] = color.g;
    buffer[(x * 4 + y * this->width * 4)  + 2] = color.b;
    buffer[(x * 4 + y * this->width * 4)  + 3] = color.a;
}
#pragma mark -
#pragma mark Painting
void AWCanvas::draw(int x, int y, AWColor color){
    dispatch_async(this->drawQueue, ^{
        if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
            return;
        }
        buffer[x * 4 + y * this->width * 4] = color.r;
        buffer[(x * 4 + y * this->width * 4)  + 1] = color.g;
        buffer[(x * 4 + y * this->width * 4)  + 2] = color.b;
        buffer[(x * 4 + y * this->width * 4)  + 3] = color.a;
    });
}

void AWCanvas::drawLine(int x0, int y0, int x1, int y1, AWColor color) {
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
            this->__draw(y, x, color);
        }else {
            this->__draw(x, y, color);
        }
        error = error - dy;

        if (error < 0) {
            y = y  + ystep;
            error = error +dx;
        }
    }
}


