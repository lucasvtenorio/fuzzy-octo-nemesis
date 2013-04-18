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
namespace io {
    class Reader {
    public:
        rendering::PerspectiveCamera readCamera(const char * filePath);
    };
}
#endif /* defined(__Render__Reader__) */
