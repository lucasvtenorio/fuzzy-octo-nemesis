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
    public:
        Mesh();

        std::vector<geometry::Point3D> points();
        std::vector<IndexedTriangle> triangleIndexes;

        inline geometry::Triangle getTriangle(const IndexedTriangle & t) const{
            return geometry::Triangle(pts[t.idA], pts[t.idB], pts[t.idC]);
        }
    };
}

#endif /* defined(__Render__Mesh__) */
