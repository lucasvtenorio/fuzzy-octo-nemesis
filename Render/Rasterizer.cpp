//
//  Rasterizer.cpp
//  Render
//
//  Created by Rafael Farias Marinheiro on 19/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Rasterizer.h"

#include <algorithm>
#include <cmath>

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
        math::Vector ba = (b.asVector() - a.asVector());
        math::Vector ca = (c.asVector() - a.asVector());
        
        double det = ba(0)*ca(1) - ca(0)*ba(1);
        
        math::Matrix mat = math::Matrix(2, 2);
        mat(0, 0) = ca(1)/det;
        mat(0, 1) = -ca(0)/det;
        mat(1, 0) = -ba(1)/det;
        mat(1, 1) = ba(0)/det;
        
        return mat;
    }
    
    math::Vector getBaricentricCoordinates(const geometry::Point2D & p, const math::Matrix & m){
        math::Vector v = (m * (p.asVector()));
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
    
    geometry::Point3D interpolate(const math::Vector & baricentric, const geometry::Point3D & a, const geometry::Point3D & b, const geometry::Point3D & c){
        return geometry::Point3D(baricentric(0)*a.x() + baricentric(1)*b.x() + baricentric(2)*c.x(),
                                 baricentric(0)*a.y() + baricentric(1)*b.y() + baricentric(2)*c.y(),
                                 baricentric(0)*a.z() + baricentric(1)*b.z() + baricentric(2)*c.z());
    }
    
    geometry::Vector3D interpolate(const math::Vector & baricentric, const geometry::Vector3D & a, const geometry::Vector3D & b, const geometry::Vector3D & c){
        
        return geometry::Vector3D(baricentric(0)*a.x() + baricentric(1)*b.x() + baricentric(2)*c.x(),
                                  baricentric(0)*a.y() + baricentric(1)*b.y() + baricentric(2)*c.y(),
                                  baricentric(0)*a.z() + baricentric(1)*b.z() + baricentric(2)*c.z());
    }
    
    rendering::ColorVector calculateDiffuse(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal){
        
        using namespace rendering;
        
        ColorVector color(0, 0, 0, 0);
        
        for(int light_id = 0; light_id < world->lights().size(); light_id++){
            LightSource light = world->lights()[light_id];
            math::Vector l = (light.position().asVector() - position.asVector());
            double t = l.normalized()*(normal.asVector());
            
            if(t > 0){
                double coef = t * object.diffuseCoefficient();
                color = color + ColorVector(object.color().r()*light.color().r() + object.color().g()*light.color().g() + object.color().b()*light.color().b())*coef;
            }
        }
        return color;
    }
    
    rendering::ColorVector calculateSpecular(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal){
        using namespace rendering;
        
        using namespace rendering;
        
        ColorVector color(0, 0, 0, 0);
        
        for(int light_id = 0; light_id < world->lights().size(); light_id++){
            LightSource light = world->lights()[light_id];
            math::Vector l = (light.position().asVector() - position.asVector());
            math::Vector o = l - l.projection(normal.asVector());
            math::Vector r = l - o*2;
            o = camera->position().asVector() - position.asVector();
            double t = r.normalized()*o.normalized();
            if(t > 0){
                double coef = pow(t, object.shininess()) * object.specularCoefficient();
                color = color + light.color()*coef;
            }
        }
        return color;
        
    }
    

    rendering::ColorVector calculateAmbient(rendering::World * world, const data::Object & object){
        
        return world->ambientLightColor()*object.ambientCoefficient();
    }

    const double _EPS = 1e-2;
    
    void Rasterizer::rasterize(rendering::World *world, rendering::Camera * camera){
        using namespace geometry;

        resetZBuffer();

        for(int object_id = 0; object_id < world->objects().size(); object_id++){
            data::Object object = world->objects()[object_id];
            //printf("Object_id: %d/%d", object_id, world->objects().size());
            for(int triangle_id = 0; triangle_id <
                object.mesh().triangleIndexes().size(); triangle_id++){
                
                if(triangle_id%1000 == 0) printf("Triangle_id: %d/%d\n", triangle_id, object.mesh().triangleIndexes().size());
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

//                printf("----------\n");
//
//                printf("Camera: ");
//                camera->print();
//                printf("---\n");
//
//
//                pA.print(), pB.print(), pC.print();

                pA.x() *= canvas->getWidth();
                pA.y() *= canvas->getHeight();

                pB.x() *= canvas->getWidth();
                pB.y() *= canvas->getHeight();

                pC.x() *= canvas->getWidth();
                pC.y() *= canvas->getHeight();


                if(collinear(pA, pB, pC)) continue;
               // printf("Hi\n");
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
                
                if(int(pA.y()) == int(pB.y()) && pB.x() < pA.x()){
                    std::swap(pA, pB);
                    std::swap(nA, nB);
                    std::swap(pA3, pB3);
                }
                //Fim do Manual sorting

                double dx1 = 0, dx2 = 0, dx3 = 0;
                if(pB.y() - pA.y()) dx1 = (pB.x() - pA.x())/(pB.y() - pA.y());
                if(pC.y() - pA.y()) dx2 = (pC.x() - pA.x())/(pC.y() - pA.y());
                if(pC.y() - pB.y()) dx3 = (pC.x() - pB.x())/(pC.y() - pB.y());
                
                double xBegin = pA.x(), xEnd = pA.x();
                if(int(pA.y()) == int(pB.y())){
                    xEnd = pB.x();
                }
                int y = int(pA.y());
                double incBegin, incEnd;
                
                math::Matrix baric = getBaricentricTransformation(pA, pB, pC);
                //baric.print();

                bool horario = (pB.x() - pA.x())*(pC.y() - pA.y()) - (pC.x() - pA.x())*(pB.y() - pA.y()) > 0;
                
                if(horario){
                    incBegin = dx2;
                    incEnd = dx1;
                } else{
                    incBegin = dx1;
                    incEnd = dx2;
                }
                
                y = int(y);
                for(; y <= int(pC.y()); y++){
                    if(y == int(pB.y())){
                        if(horario){
                            xEnd = pB.x();
                            incEnd = dx3;
                        } else{
                            xBegin = pB.x();
                            incBegin = dx3;
                        }
                    } else{
                        
                    }
                    for(int x = int(xBegin); x <= int(xEnd); x++){
                        math::Vector baricentric = getBaricentricCoordinates(Point2D(x + 0.5 - pA.x(), y + 0.5 -pA.y()), baric);
                        
                        if(baricentric(0) < -_EPS || baricentric(0) > 1 + _EPS || baricentric(1) < -_EPS || baricentric(1) > 1 + _EPS || baricentric(2) < -_EPS || baricentric(2) > 1 + _EPS) continue;
                        
                        Point3D point = interpolate(baricentric, pA3, pB3, pC3);
                        Vector3D normal = interpolate(baricentric, nA, nB, nC).normalized();
                        
                        rendering::ColorVector color = calculateAmbient(world, object);
                        color = color + calculateDiffuse(world, camera, object, point, normal);
                        color = color + calculateSpecular(world, camera, object, point, normal);
                        
                        drawPixel(x, y, pA.depth() * baricentric(0) + pB.depth() * baricentric(1) + pC.depth() * baricentric(2), color.clip());
               
                    }
                    xBegin += incBegin;
                    xEnd += incEnd;
                }
                
            }
        }
    }
}