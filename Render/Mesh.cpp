//
//  Mesh.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Mesh.h"

namespace data{
    Mesh::Mesh() : pts(), idxT(), _normals(){
        
    }
    
    void Mesh::computeNormals(){
        _normals.clear();
        for(int i = 0; i < points().size(); i++){
            _normals.push_back(geometry::Vector3D(0, 0, 0));
        }
        
        for(int i = 0; i < triangleIndexes().size(); i++){
            IndexedTriangle t = triangleIndexes()[i];
            math::Vector normal = getTriangle(t).getNormal().asVector();
            
            math::Vector temp = _normals[t.idA].asVector() + normal;
            _normals[t.idA] = geometry::Vector3D(temp(0), temp(1), temp(2));
            
            temp = _normals[t.idB].asVector() + normal;
            _normals[t.idB] = geometry::Vector3D(temp(0), temp(1), temp(2));
            
            temp = _normals[t.idC].asVector() + normal;
            _normals[t.idC] = geometry::Vector3D(temp(0), temp(1), temp(2));
        }
        
        for(int i = 0; i < points().size(); i++){
            _normals[i] = _normals[i].normalized();
        }
    }
}