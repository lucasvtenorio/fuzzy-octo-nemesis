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

#include "PerspectiveCamera.h"

namespace drawing{
    Rasterizer::Rasterizer(Canvas * canvas, double SET_MAX_DEPTH){
        this->canvas = canvas;
        this->width = canvas->getWidth();
        this->height = canvas->getHeight();
        this->MAX_DEPTH = SET_MAX_DEPTH;
        this->_zbuffer = (double *) malloc(sizeof(double) *width * height);
        this->xBegin = (int *) malloc(sizeof(int) * height);
        this->xEnd = (int *) malloc(sizeof(int) * height);
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

    inline bool collinear(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c){
        math::Vector ba = b.asVector() - a.asVector();
        math::Vector ca = c.asVector() - a.asVector();

        double pv = ba(0)*ca(1) - ca(0)*ba(1);

        if(pv == 0) return true;
        return false;
    }

    inline bool Rasterizer::outaSight(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c) {

        int maxX = this->canvas->getWidth();
        int maxY = this->canvas->getHeight();

        if (a.depth() < 0 && b.depth() < 0 && c.depth() < 0) {
            return true;
        }
        
        if (a.x() < 0 && b.x() < 0 && c.x() < 0) {
            return true;
        }

        if (a.y() < 0 && b.y() < 0 && c.y() < 0) {
            return true;
        }

        if (a.x() > maxX && b.x() > maxX && c.x() > maxX) {
            return true;
        }

        if (a.y() > maxY && b.y() > maxY && c.y() > maxY) {
            return true;
        }
        
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

            if(t < 0) t--;

            if(t > 0){
                double coef = t * object.diffuseCoefficient();

                ColorVector temp = ColorVector(object.color().r()*light.color().r() , object.color().g()*light.color().g() , object.color().b()*light.color().b());
                //temp.print();
                color = color + temp*coef;
            }
        }
        return color;
    }

    rendering::ColorVector calculateSpecular(rendering::World * world, rendering::Camera * camera, const data::Object & object, const geometry::Point3D & position, const geometry::Vector3D normal){
        using namespace rendering;
        
        ColorVector color(0, 0, 0, 0);

        for(int light_id = 0; light_id < world->lights().size(); light_id++){
            LightSource light = world->lights()[light_id];
            math::Vector l = (light.position().asVector() - position.asVector());
            math::Vector o = l - l.projection(normal.asVector());
            math::Vector r = l - o*2;
            o = camera->position().asVector() - position.asVector();
            double t = r.normalized()*o.normalized();

            if(t < 0) t--;

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

    inline int Rasterizer::clampScreen(int a){
        if(a < 0){
            return 0;
        }
        if(a > this->width - 1){
            return this->width - 1;
        }
        return a;
    }

    void Rasterizer::setMin(int y, int x){
        if(0 <= y && y < this->height){
            this->xBegin[y] = clampScreen(x);
        }
    }

    void Rasterizer::setMax(int y, int x){
        if(0 <= y && y < this->height){
            this->xEnd[y] = clampScreen(x);
        }
    }


    void Rasterizer::drawLine(int x0, int y0, int x1, int y1, double z, const drawing::Color & color){
        bool steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep) {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1) {
            std::swap(x1, x0);
            std::swap(y1, y0);
        }
        int dx = x1 - x0;
        int dy = abs(y1 - y0);

        int error = dx / 2;
        int ystep;
        int y = y0;

        if (y0 < y1) {
            ystep = 1;
        } else {
            ystep = -1;
        }

        for (int x = x0; x <= x1; x++) {
            if (steep) {
                this->drawPixel(y, x, z, color);
            }else {
                this->drawPixel(x, y, z, color);
            }
            error = error - dy;

            if (error < 0) {
                y = y  + ystep;
                error = error +dx;
            }
        }
    }

    void Rasterizer::calcLine(int x0, int y0, int x1, int y1, bool mini){
        bool steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep) {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1) {
            std::swap(x1, x0);
            std::swap(y1, y0);
        }
        int dx = x1 - x0;
        int dy = abs(y1 - y0);

        int error = dx / 2;
        int ystep;
        int y = y0;

        if (y0 < y1) {
            ystep = 1;
        } else {
            ystep = -1;
        }

        for (int x = x0; x <= x1; x++) {
            if (steep) {
                if(mini) setMin(x, y);
                else setMax(x, y);
            }else {
                if(mini) setMin(y, x);
                else setMax(y, x);
            }
            error = error - dy;

            if (error < 0) {    
                y = y  + ystep;
                error = error +dx;
            }
        }
    }

    double pv(const geometry::Point2D & v, const geometry::Point2D & u, const geometry::Point2D & c){
        return (v.x()-c.x()) * (u.y()-c.y()) - (u.x()-c.x())*(v.y() - c.y());
    }

    bool inTriangle(const geometry::Point2D & p, const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c){
        if(pv(p, b, a)*pv(p, c, a) < 0 && pv(p, c, b)*pv(p, a, b) < 0){
            return true;
        } else{
            return false;
        }
    }

    void Rasterizer::rasterizeTriangle(geometry::Point2D pA, geometry::Point2D pB, geometry::Point2D pC){

        if(pB.y() < pA.y()){
            std::swap(pA, pB);
        }

        if(pC.y() < pB.y()){
            std::swap(pB, pC);

            if(pB.y() < pA.y()){
                std::swap(pA, pB);
            }
        }

        if(int(pA.y()) == int(pB.y()) && pB.x() < pA.x()){
            std::swap(pA, pB);
        }

        bool horario = pv(pB, pC, pA) > 0;


        if(horario){
            this->calcLine(pA.x(), pA.y(), pB.x(), pB.y(), false);
            this->calcLine(pB.x(), pB.y(), pC.x(), pC.y(), false);
            this->calcLine(pA.x(), pA.y(), pC.x(), pC.y(), true);
        } else{
            this->calcLine(pA.x(), pA.y(), pB.x(), pB.y(), true);
            this->calcLine(pB.x(), pB.y(), pC.x(), pC.y(), true);
            this->calcLine(pA.x(), pA.y(), pC.x(), pC.y(), false);
        }
    }

    bool Rasterizer::inScreen(const geometry::Point2D & a){
        if(0 <= a.x() && a.x() <= this->width && 0 <= a.y() && a.y() <= this->height){
            return true;
        }
        return false;
    }

    bool Rasterizer::intersectWithScreen(const geometry::Point2D & aa, const geometry::Point2D & bb, geometry::Point2D & ret, int k){
        geometry::Point2D a = aa;
        geometry::Point2D b = bb;
        if(a.y() > b.y()){
            std::swap(a, b);
        }
        if(k == 0){
            if(a.y()*b.y() < 0){
                ret = a;
                ret.y() = 0;
                double dx = std::abs(b.x() - a.x());
                double dy = std::abs(b.y() - a.y());
                double d = std::abs(a.y() - 0);
                double xa = (dx*d)/dy;
                if(b.x() > a.x()){
                    ret.x() += xa;
                } else{
                    ret.x() -= xa;
                }
                if(inScreen(ret)) return true;
                return false;
            } else{
                return false;
            }
        } else if(k == 1){
            if((a.y() - this->height)*(b.y() - this->height) < 0){
                ret = a;
                ret.y() = this->height;
                double dx = std::abs(b.x() - a.x());
                double dy = std::abs(b.y() - a.y());
                double d = std::abs(this->height - a.y());
                double xa = (dx*d)/dy;
                if(b.x() > a.x()){
                    ret.x() += xa;
                } else{
                    ret.x() -= xa;
                }
                if(inScreen(ret)) return true;
                return false;
            } else{
                return false;
            }
        } else if(k == 2){
            if((a.x() * b.x()) < 0){
                ret = a;
                ret.x() = 0;
                double dx = std::abs(b.x() - a.x());
                double dy = std::abs(b.y() - a.y());
                double d = std::abs(a.x());
                double ya = (d*dy)/dx;
                ret.y() += ya;

                if(inScreen(ret)) return true;
                return false;
                
            } else{
                return false;
            }
        } else{
            if((a.x()-this->width) * (b.x()-this->width) < 0){
                ret = a;
                ret.x() = this->width;
                double dx = std::abs(b.x() - a.x());
                double dy = std::abs(b.y() - a.y());
                double d = std::abs(a.x() - this->width);
                double ya = (d*dy)/dx;
                ret.y() += ya;


                if(inScreen(ret)) return true;
                return false;

            } else{
                return false;
            }
        }
    }

    geometry::Point2D pivot;

    bool cmpPolar(const geometry::Point2D & a, const geometry::Point2D & b){
        if(pv(a, b, pivot) > 0){
            return true;
        }
        return false;
    }

    void sortPoints(std::vector<geometry::Point2D> & list){
        if(list.size() == 0) return;
        int ind = 0;
        for(int i = 1; i < list.size(); i++){
            if(list[i].x() < list[ind].x()){
                ind = i;
            } else if(list[i].x() == list[ind].x()){
                if(list[i].y() < list[ind].y()){
                    ind = i;
                }
            }
        }
        std::swap(list[0], list[ind]);
        pivot = list[0];
        std::vector<geometry::Point2D>::iterator begin = list.begin();
        std::vector<geometry::Point2D>::iterator end = list.end();

        ++begin;

        std::sort(begin, end, cmpPolar);

    }

    void Rasterizer::fillPointList(const geometry::Point2D & a, const geometry::Point2D & b, const geometry::Point2D & c, std::vector<geometry::Point2D> & list){

        using namespace geometry;
        list.clear();

        if(inScreen(a)){
            list.push_back(a);
        }
        for(int i = 0; i < 4; i++){
            Point2D p;
            if(intersectWithScreen(a, b, p, i)){
                list.push_back(p);
            }
        }

        if(inScreen(b)){
            list.push_back(b);
        }
        for(int i = 0; i < 4; i++){
            Point2D p;
            if(intersectWithScreen(b, c, p, i)){
                list.push_back(p);
            }
        }


        if(inScreen(c)){
            list.push_back(c);
        }
        for(int i = 0; i < 4; i++){
            Point2D p;
            if(intersectWithScreen(c, a, p, i)){
                list.push_back(p);
            }
        }

        Point2D rect(0, 0);
        if(inTriangle(rect, a, b, c)) list.push_back(rect);
        rect.x() = this->width;
        if(inTriangle(rect, a, b, c)) list.push_back(rect);
        rect.y() = this->height;
        if(inTriangle(rect, a, b, c)) list.push_back(rect);
        rect.x() = 0;
        if(inTriangle(rect, a, b, c)) list.push_back(rect);
    }

    void Rasterizer::rasterize(rendering::World *world, rendering::Camera * camera){
        using namespace geometry;

        resetZBuffer();

        for(int object_id = 0; object_id < world->objects().size(); object_id++){
            data::Object object = world->objects()[object_id];
            for(int triangle_id = 0; triangle_id <
                object.mesh().triangleIndexes().size(); triangle_id++){

                //if(triangle_id%1000 == 0) printf("Triangle_id: %d/%d\n", triangle_id, object.mesh().triangleIndexes().size());
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

                pA.x() *= canvas->getWidth();
                pA.y() *= canvas->getHeight();

                pB.x() *= canvas->getWidth();
                pB.y() *= canvas->getHeight();

                pC.x() *= canvas->getWidth();
                pC.y() *= canvas->getHeight();


                
                //if (outaSight(pA, pB, pC)) continue;
                if(collinear(pA, pB, pC)){
                    this->drawLine(std::min(std::min(pA.x(), pB.x()), pC.x()), std::min(std::min(pA.y(), pB.y()), pC.y()), std::max(std::max(pA.x(), pB.x()), pC.x()), std::max(std::max(pA.y(), pB.y()), pC.y()), 0.01, Color(0, 255, 0));
                    continue;
                }

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

                math::Matrix baric = getBaricentricTransformation(pA, pB, pC);

                std::vector<Point2D> pointList;

                this->fillPointList(pA, pB, pC, pointList);
                if(pointList.size() > 3) sortPoints(pointList);

                for(int i = 0; i + 2 < pointList.size(); i++){
                    rasterizeTriangle(pointList[0], pointList[i+1], pointList[i+2]);

                    int mini = std::min(std::min(pointList[0].y(), pointList[i+1].y()), pointList[i+2].y());
                    int maxi = std::max(std::max(pointList[0].y(), pointList[i+1].y()), pointList[i+2].y());
                    //Color ccolor = Color(rand()%255, rand()%255, rand()%255);

                    mini = std::max(mini, 0);
                    maxi = std::min(maxi, this->height - 1);
                    
                    for(int y = mini; y <= maxi; y++){

                        int minX = std::max(0, this->xBegin[y]);
                        int maxX = std::min(this->width, this->xEnd[y]);

                        for(int x = minX; x <= maxX; x++){
                            math::Vector baricentric = getBaricentricCoordinates(Point2D(x + 0.5 - pA.x(), y + 0.5 -pA.y()), baric);

                            double depth = pA.depth() * baricentric(0) + pB.depth() * baricentric(1) + pC.depth() * baricentric(2);
                            if(depth < 0 || depth > zbuffer(x, y)){
                                continue;
                            }

                            Point3D point = interpolate(baricentric, pA3, pB3, pC3);
                            Vector3D normal = interpolate(baricentric, nA, nB, nC).normalized();
                            rendering::ColorVector color = calculateAmbient(world, object);
                            color = color + calculateDiffuse(world, camera, object, point, normal);
                            color = color + calculateSpecular(world, camera, object, point, normal);

                            //drawPixel(x, y, depth, ccolor);
                            drawPixel(x, y, depth, color.clip());

                            //Vaca Louca
                            //drawPixel(x, y, depth, rendering::ColorVector(255*normal.x(), 255*normal.y(), 255*normal.z()).clip());
                        }
                    }
                }

            }
        }
    }
}