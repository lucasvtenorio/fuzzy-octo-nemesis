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

        inline std::vector<data::Object> & objects(){
            return _objects;
        }
        inline const std::vector<data::Object> & objects() const{
            return _objects;
        }

        inline std::vector<rendering::LightSource> & lights(){
            return _lights;
        }
        inline const std::vector<rendering::LightSource> & lights() const{
            return _lights;
        }

        inline rendering::ColorVector & ambientLightColor(){
            return _ambientLight;
        }
        inline const rendering::ColorVector & ambientLightColor() const{
            return _ambientLight;
        }
    };
}
#endif /* defined(__Render__World__) */
