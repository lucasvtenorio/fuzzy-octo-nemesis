//
//  Rasterizer.cpp
//  Render
//
//  Created by Rafael Farias Marinheiro on 19/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Rasterizer.h"

#include <algorithm>

namespace drawing{
    Rasterizer::Rasterizer(Canvas * canvas, double SET_MAX_DEPTH){
        this->canvas = canvas;
        this->width = canvas->getWidth();
        this->height = canvas->getHeight();
        this->MAX_DEPTH = SET_MAX_DEPTH;
        this->_zbuffer = (double *) malloc(sizeof(double) *width * height);
    }
    
    Rasterizer::~Rasterizer(){
        free(this->_zbuffer);
        this->_zbuffer = nullptr;
    }
    
    void Rasterizer::resetZBuffer(){
        for(int i = 0; i < width*height; i++){
            this->_zbuffer[i] = MAX_DEPTH;
        }
    }

    math::Matrix getBaricentricTransformation(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c){
        math::Vector ba = b.asVector() - a.asVector();
        math::Vector ca = c.asVector() - a.asVector();
        
        double det = ba(0)*ca(1) - ca(0)*ba(1);
        
        math::Matrix mat = math::Matrix(2, 2);
        mat(0, 0) = ca(1);
        mat(0, 1) = -ca(0);
        mat(1, 0) = -ba(1);
        mat(1, 1) = ba(0);
        
        return mat/det;
    }
    
    math::Vector getBaricentricCoordinates(const geometry::Point2D & p, const math::Matrix & m){
        math::Vector v = m * p.asVector();
        math::Vector baric(3);
        baric(0) = 1 - v(0) - v(1);
        baric(1) = v(0);
        baric(2) = v(1);
        return baric;
    }
    
    bool collinear(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c){
        math::Vector ba = b.asVector() - a.asVector();
        math::Vector ca = c.asVector() - a.asVector();
        
        double pv = ba(0)*ca(1) - ca(0)*ba(1);
        
        if(pv == 0) return true;
        return false;
    }
    
    geometry::Point3D interpolate(math::Vector baricentric, const geometry::Point3D & a, const geometry::Point3D & b, const geometry::Point3D & c){
        math::Vector v = a.asVector()*baricentric(0) + b.asVector()*baricentric(1) + c.asVector()*baricentric(2);
        return geometry::Point3D(v(0), v(1), v(2));
    }
    
    geometry::Vector3D interpolate(math::Vector baricentric, const geometry::Vector3D & a, const geometry::Vector3D & b, const geometry::Vector3D & c){
        math::Vector v = a.asVector()*baricentric(0) + b.asVector()*baricentric(1) + c.asVector()*baricentric(2);
        return geometry::Vector3D(v(0), v(1), v(2));
    }
    
    //FALTA IMPLEMENTAR
    rendering::ColorVector calculateDiffuse(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal){
        
        using namespace rendering;
        
        ColorVector color(0, 0, 0, 0);
        
        for(int light_id = 0; light_id < world->lights().size(); light_id++){
            LightSource light = world->lights()[light_id];
            math::Vector l = (light.position().asVector() - position.asVector());
            double coef = (l.normalized()*(normal.asVector().normalized())) * object.diffuseCoefficient();
            color = color + object.color()*coef;
        }
        return color;
    }
    
    //FALTA IMPLEMENTAR
    rendering::ColorVector calculateSpecular(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal){
        using namespace rendering;
        return ColorVector(0, 0, 0, 0);
    }
    

    rendering::ColorVector calculateAmbient(rendering::World * world, const data::Object & object){
        return world->ambientLightColor()*object.ambientCoefficient();
    }

    void Rasterizer::rasterize(rendering::World *world, rendering::Camera * camera){
        using namespace geometry;
        
        for(int object_id = 0; object_id < world->objects().size(); object_id++){
            data::Object object = world->objects()[object_id];
            
            for(int triangle_id = 0; triangle_id < object.mesh().triangleIndexes().size(); triangle_id++){
                data::IndexedTriangle indexedTriangle = object.mesh().triangleIndexes()[triangle_id];
                geometry::Triangle triangle = object.mesh().getTriangle(indexedTriangle);
                
                Point2D pA = camera->doTheDance(triangle.a());
                Vector3D nA = object.mesh().normals()[indexedTriangle.idA];
                Point3D pA3 = triangle.a();
                
                Point2D pB = camera->doTheDance(triangle.b());
                Vector3D nB = object.mesh().normals()[indexedTriangle.idB];
                Point3D pB3 = triangle.b();
                
                Point2D pC = camera->doTheDance(triangle.c());
                Vector3D nC = object.mesh().normals()[indexedTriangle.idC];
                Point3D pC3 = triangle.c();
                
                if(collinear(pA, pB, pC)) continue;
                
                //Manual sorting == Sort dos manos
                if(pB.y() < pA.y()){
                    std::swap(pA, pB);
                    std::swap(nA, nB);
                    std::swap(pA3, pB3);
                }
                
                if(pC.y() < pB.y()){
                    std::swap(pB, pC);
                    std::swap(nB, nC);
                    std::swap(pB3, pC3);
                    
                    if(pB.y() < pA.y()){
                        std::swap(pA, pB);
                        std::swap(nA, nB);
                        std::swap(pA3, pB3);
                    }
                }
                //Fim do Manual sorting
                
                double dx1 = 0, dx2 = 0, dx3 = 0;
                if(pB.y() - pA.y()) dx1 = (pB.x() - pA.x())/(pB.y() - pA.y());
                if(pC.y() - pA.y()) dx2 = (pC.x() - pA.x())/(pC.y() - pA.y());
                if(pC.y() - pB.y()) dx3 = (pC.x() - pB.x())/(pC.y() - pB.y());
                
                double xBegin = pA.x(), xEnd = pA.x();
                int y = int(pA.y());
                
                
                math::Matrix baric = getBaricentricTransformation(pA, pB, pC);
                
                
                if(dx1 > dx2){
                    for(; y <= int(pB.y()); y++){
                        for(int x = int(xBegin); x <= int(xEnd); x++){
                            math::Vector baricentric = getBaricentricCoordinates(Point2D(x, y), baric);
                            Point3D point = interpolate(baricentric, pA3, pB3, pC3);
                            Vector3D normal = interpolate(baricentric, nA, nB, nC);
                            
                            rendering::ColorVector color = calculateAmbient(world, object);
                            color = color + calculateDiffuse(world, camera, object, point, normal);
                            color = color + calculateSpecular(world, camera, object, point, normal);
                            
                            drawPixel(x, y, point.z(), color.clip());
                        }
                        xBegin = xBegin + dx2;
                        xEnd = xEnd + dx1;
                    }
                    y = int(pB.y());
                    xEnd = pB.x();
                    for(; y <= int(pC.y()); y++){
                        for(int x = int(xBegin); x <= int(xEnd); x++){
                            math::Vector baricentric = getBaricentricCoordinates(Point2D(x, y), baric);
                            Point3D point = interpolate(baricentric, pA3, pB3, pC3);
                            Vector3D normal = interpolate(baricentric, nA, nB, nC);
                            
                            rendering::ColorVector color = calculateAmbient(world, object);
                            color = color + calculateDiffuse(world, camera, object, point, normal);
                            color = color + calculateSpecular(world, camera, object, point, normal);
                            
                            drawPixel(x, y, point.z(), color.clip());
                        }
                        xBegin = xBegin + dx2;
                        xEnd = xEnd + dx3;
                    }
                } else{
                    for(; y <= int(pB.y()); y++){
                        for(int x = int(xBegin); x <= int(xEnd); x++){
                            math::Vector baricentric = getBaricentricCoordinates(Point2D(x, y), baric);
                            Point3D point = interpolate(baricentric, pA3, pB3, pC3);
                            Vector3D normal = interpolate(baricentric, nA, nB, nC);
                            
                            rendering::ColorVector color = calculateAmbient(world, object);
                            color = color + calculateDiffuse(world, camera, object, point, normal);
                            color = color + calculateSpecular(world, camera, object, point, normal);
                            
                            drawPixel(x, y, point.z(), color.clip());
                        }
                        xBegin = xBegin + dx1;
                        xEnd = xEnd + dx2;
                    }
                    xBegin = pB.x();
                    y = int(pB.y());
                    for(; y <= int(pC.y()); y++){
                        for(int x = int(xBegin); x <= int(xEnd); x++){
                            math::Vector baricentric = getBaricentricCoordinates(Point2D(x, y), baric);
                            Point3D point = interpolate(baricentric, pA3, pB3, pC3);
                            Vector3D normal = interpolate(baricentric, nA, nB, nC);
                            
                            rendering::ColorVector color = calculateAmbient(world, object);
                            color = color + calculateDiffuse(world, camera, object, point, normal);
                            color = color + calculateSpecular(world, camera, object, point, normal);
                            
                            drawPixel(x, y, point.z(), color.clip());
                        }
                        xBegin = xBegin + dx3;
                        xEnd = xEnd + dx2;
                    }
                }
                
            }
        }
    }
}