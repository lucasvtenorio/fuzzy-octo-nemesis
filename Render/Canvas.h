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
#include "Color.h"

namespace drawing {
    class Canvas {

    private:
        int width;
        int height;
        unsigned char *buffer;
    public:
        Canvas(int width, int height);
        ~Canvas();

        int getWidth();
        int getHeight();
        unsigned char * getBuffer();
        void draw(int x, int y, drawing::Color color);
        void drawLine(int x0, int y0, int x1, int y1, drawing::Color color);
        
    };
}



#endif /* defined(__Render__AWCanvas__) */
