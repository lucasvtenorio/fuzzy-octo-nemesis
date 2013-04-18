//
//  Object.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Object__
#define __Render__Object__

#include "Mesh.h"
#include "ColorVector.cpp"


namespace data{
    class Object{
    private:
        Mesh mesh;
        rendering::ColorVector color;
        
    };
}

#endif /* defined(__Render__Object__) */
