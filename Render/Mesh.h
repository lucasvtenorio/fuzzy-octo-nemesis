//
//  Mesh.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Mesh__
#define __Render__Mesh__

#include <vector>

#include "Point3D.h"
#include "Triangle.h"
#include "IndexedTriangle.h"

namespace data{
    class Mesh{
    private:
        std::vector<geometry::Point3D> pts;
        std::vector<IndexedTriangle> idxT;
        std::vector<geometry::Vector3D> _normals;
    public:
        Mesh();

        inline std::vector<geometry::Point3D> & points(){
            return pts;
        }
        
        inline std::vector<IndexedTriangle> & triangleIndexes(){
            return idxT;
        }

        inline std::vector<geometry::Vector3D> & normals(){
            return _normals;
        }
        
        inline geometry::Triangle getTriangle(const IndexedTriangle & t) const{
            return geometry::Triangle(pts[t.idA], pts[t.idB], pts[t.idC]);
        }
        
        void computeNormals();
    };
}

#endif /* defined(__Render__Mesh__) */
