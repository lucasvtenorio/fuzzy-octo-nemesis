//
//  Reader.cpp
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Reader.h"

#include "stdio.h"

namespace io {
    rendering::PerspectiveCamera * Reader::readCamera(const char * filePath) {
        FILE *file = fopen(filePath, "r");

        double x, y, z;
        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Point3D position(x , y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Vector3D head(x, y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Vector3D direction(x, y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        double focalDistance = x;
        double cameraWidth = y;
        double cameraHeight = z;

        fclose(file);

        position.print();
        head.print();
        direction.print();
        
        return new rendering::PerspectiveCamera(position, direction, head, focalDistance, cameraWidth, cameraHeight);
    }
    
    data::Mesh * Reader::readMesh(const char * filePath){
        FILE * file = fopen(filePath, "r");
        printf("%s\n", filePath);
        int n, t;
        data::Mesh * mesh = new data::Mesh();
        
        fscanf(file, "%d %d", &n, &t);
        
        for(int i = 0; i < n; i++){
            double x, y, z;
            fscanf(file, "%lf %lf %lf", &x, &y, &z);
            mesh->points().push_back(geometry::Point3D(x, y, z));
        }
        
        for(int i = 0; i < t; i++){
            int a, b, c;
            fscanf(file, "%d %d %d", &a, &b, &c);
            mesh->triangleIndexes().push_back(data::IndexedTriangle(a-1, b-1, c-1));
        }
        
        mesh->computeNormals();
        
        return mesh;
    }
}


