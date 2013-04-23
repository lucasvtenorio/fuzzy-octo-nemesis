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
        geometry::Vector3D direction(x, y, z);

        fscanf(file, "%lf %lf %lf", &x, &y, &z);
        geometry::Vector3D head(x, y, z);

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
    
    std::pair<rendering::World *, std::vector<data::Mesh *> > Reader::readWorld(const char * lightSourceFilepath, const char * meshFilepath) {

        FILE *lightFile = fopen(lightSourceFilepath, "r");

        double x, y, z;
        double ambientCoefficient;
        double kd;
        double ks;
        double n;

        fscanf(lightFile, "%lf %lf %lf", &x, &y, &z);
        geometry::Point3D lightPosition(x, y, z);

        fscanf(lightFile, "%lf", &ambientCoefficient);
        fscanf(lightFile, "%lf %lf %lf", &x, &y, &z);
        rendering::ColorVector ia(x, y, z);
        fscanf(lightFile, "%lf", &kd);

        fscanf(lightFile, "%lf %lf %lf", &x, &y, &z);
        rendering::ColorVector od(255*x, 255*y, 255*z);

        fscanf(lightFile, "%lf", &ks);

        fscanf(lightFile, "%lf %lf %lf", &x, &y, &z);
        rendering::ColorVector lightColor(x, y, z);
        fscanf(lightFile, "%lf", &n);

        fclose(lightFile);

        rendering::LightSource lightSource(lightPosition, lightColor);

        std::vector<data::Mesh *> meshes;

        data::Mesh * mesh = Reader::readMesh(meshFilepath);
        meshes.push_back(mesh);

        rendering::World * world = new rendering::World();
        world->lights().push_back(lightSource);
        world->objects().push_back(data::Object(meshes[0], od, ambientCoefficient, kd, ks, n));
        world->ambientLightColor() = ia;

        return std::pair<rendering::World *, std::vector<data::Mesh *> >(world, meshes);
    }
}


