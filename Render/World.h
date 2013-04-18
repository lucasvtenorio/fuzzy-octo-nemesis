//
//  World.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__World__
#define __Render__World__

#include <vector>
#include "Object.h"
#include "LightSource.h"
#include "ColorVector.h"

namespace rendering{
    class World{
    private:
        std::vector<data::Object> _objects;
        std::vector<rendering::LightSource> _lights;
        rendering::ColorVector _ambientLight;
        
    public:
        World();
    };
}
#endif /* defined(__Render__World__) */
