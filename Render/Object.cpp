//
//  Object.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Object.h"

namespace data{
    Object::Object(Mesh * mesh, const rendering::ColorVector & color, double ambientCoefficient, double diffuseCoefficient, double specularCoefficient, double shininess){
        this->_mesh = mesh;
        this->_color = color;
        this->_ambientCoefficient = ambientCoefficient;
        this->_diffuseCoefficient = diffuseCoefficient;
        this->_specularCoefficient = specularCoefficient;
        this->_shininess = shininess;
    }
}