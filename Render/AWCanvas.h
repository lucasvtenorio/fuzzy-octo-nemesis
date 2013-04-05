//
//  AWCanvas.h
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__AWCanvas__
#define __Render__AWCanvas__

#include <iostream>
#include <dispatch/dispatch.h>


typedef struct {
    int x;
    int y;
} AWPoint;

typedef struct {
    int r;
    int g;
    int b;
    int a;
} AWColor;

class AWCanvas {
    
private:
    int width;
    int height;
    unsigned char *buffer;
    dispatch_queue_t drawQueue;
    inline void __draw(int x, int y, AWColor color);
public:
    AWCanvas(int width, int height);
    ~AWCanvas();
    void getWidth(void (^response)(int width));
    void getHeight(void (^response)(int height));
    void getBuffer(void (^response)(unsigned char *buffer, int width, int height));
    void setWidth(int width);
    void setHeight(int height);
    
    void draw(int x, int y, AWColor color);
    void drawLine(int x0, int y0, int x1, int y1, AWColor color);
    
};


#endif /* defined(__Render__AWCanvas__) */
