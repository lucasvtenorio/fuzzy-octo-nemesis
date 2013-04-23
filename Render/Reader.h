//
//  Reader.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Reader__
#define __Render__Reader__
        
#include <iostream>
#include "PerspectiveCamera.h"
#include "Mesh.h"

namespace io {
    class Reader {
    public:
        static rendering::PerspectiveCamera * readCamera(const char * filePath);
        static data::Mesh * readMesh(const char * filePath);
        static 
    };
}
#endif /* defined(__Render__Reader__) */
