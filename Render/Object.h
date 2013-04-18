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
#include "ColorVector.h"


namespace data{
    class Object{
    private:
        Mesh _mesh;
        rendering::ColorVector _color;
        double _ambientCoefficient;
        double _diffuseCoefficient;
        double _specularCoefficient;
        double _shininess;
        
    public:
        Object(const Mesh & mesh, const rendering::ColorVector & color, double ambientCoefficient, double diffuseCoefficient, double specularCoefficient, double shininess);
        
        inline Mesh & mesh(){
            return _mesh;
        }
        
        inline const Mesh & mesh() const{
            return _mesh;
        }
        
        inline rendering::ColorVector & color(){
            return _color;
        }
        
        inline const rendering::ColorVector & color() const{
            return _color;
        }
        
        inline double & shininess(){
            return _shininess;
        }
        
        inline const double & shininess() const{
            return _shininess;
        }
        
        inline double & ambientCoefficient(){
            return _ambientCoefficient;
        }
        
        inline const double & ambientCoefficient() const{
            return _ambientCoefficient;
        }
        
        inline double & diffuseCoefficient(){
            return _diffuseCoefficient;
        }
        
        inline const double & diffuseCoefficient() const{
            return _diffuseCoefficient;
        }
        
        inline double & specularCoefficient(){
            return _specularCoefficient;
        }
        
        inline const double & specularCoefficient() const{
            return _specularCoefficient;
        }
    };
}

#endif /* defined(__Render__Object__) */
