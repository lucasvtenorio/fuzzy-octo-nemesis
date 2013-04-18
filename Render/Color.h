//
//  Color.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Color__
#define __Render__Color__

#include "Types.h"

namespace drawing{
    struct Color{
        byte r;
        byte g;
        byte b;
        byte a;

        Color(byte r=255, byte g=255, byte b=255, byte a=255){
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
    };
}

#endif /* defined(__Render__Color__) */
