//
//  Transformation.cpp
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Transformation.h"

#include <cassert>
#include "Vector.h"
#include "cmath"

namespace geometry{
    Transformation::Transformation(const math::Matrix & m) : trans(m){
        assert(trans.rowCount() == 4 && trans.columnCount() == 4);
    }

    void Transformation::append(const Transformation & t){
        this->trans = t.trans*trans;
    }

    Point3D Transformation::apply(const Point3D & p) const{
        math::Vector ret = trans * p.v;
        return Point3D(ret(0), ret(1), ret(2));
    }

    Vector3D Transformation::apply(const Vector3D & p) const{
        math::Vector ret = trans * p.v;
        return Vector3D(ret(0), ret(1), ret(2));
    }

    Transformation Transformation::Translation(double x, double y, double z){
        math::Matrix m = math::Matrix::createIdentity(4);
        m(0, 3) = x;
        m(1, 3) = y;
        m(2, 3) = z;
        return Transformation(m);
    }

    Transformation Transformation::Scale(double x, double y, double z){
        math::Matrix m = math::Matrix::createIdentity(4);
        m(0, 0) = x;
        m(1, 1) = y;
        m(2, 2) = z;
        return Transformation(m);
    }

    Transformation Transformation::Rotation(Vector3D rotationAxis, double radAngle){
        math::Matrix m = math::Matrix::createIdentity(4);
        math::Vector v = rotationAxis.asVector().normalized();
        double cosAngle = cos(radAngle);
        double sinAngle = cos(radAngle);
        
        double minusCos = 1 - cosAngle;
        
        double x = v(0);
        double y = v(1);
        double z = v(2);
        
        
        m(0, 0) = cosAngle + (x * x * minusCos);
        m(0, 1) = (x * y * minusCos) - (sinAngle * z);
        m(0, 2) = (x * z * minusCos) + (y * sinAngle);

        m(1, 0) = (x * y * minusCos) + (z * sinAngle);
        m(1, 1) = cosAngle + (y * y * minusCos);
        m(1, 2) = (y * z * minusCos) - (x * sinAngle);

        m(2, 0) = (x * z * minusCos) - (y * sinAngle);
        m(2, 1) = (z * y * minusCos) + (x * sinAngle);
        m(2, 2) = cosAngle + (z * z * minusCos);
        
        
        return Transformation(m);
    }

    Transformation Transformation::Projection(Vector3D planeNormal, Point3D planePosition){
        math::Vector v = planeNormal.asVector().normalized();
        math::Vector p = planeNormal.asVector();
        math::Matrix m(4, 4);
        double temp = (p*v);

        m(0, 0) = 1-v(0)*v(0),  m(0, 1) = -v(0)*v(1),   m(0, 2) = -v(0)*v(2),   m(0, 3) = v(0)*temp;
        m(1, 0) = -v(1)*v(0),   m(1, 1) = 1-v(1)*v(1),  m(1, 2) = -v(1)*v(2),   m(1, 3) = v(1)*temp;
        m(2, 0) = -v(2)*v(0),   m(2, 1) = -v(2)*v(1),   m(2, 2) = 1-v(2)*v(2),  m(2, 3) = v(2)*temp;
        m(3, 0) = 0,            m(0, 1) = 0,            m(0, 2) = 0,            m(3, 3) = 1;

        return Transformation(m);
    }


    Transformation Transformation::Reflection(Vector3D planeNormal, Point3D planePosition){
        math::Vector v = planeNormal.asVector().normalized();
        math::Vector p = planeNormal.asVector();
        math::Matrix m(4, 4);
        double temp = (p*v);

        m(0, 0) = 1-2*v(0)*v(0),  m(0, 1) = -2*v(0)*v(1),   m(0, 2) = -2*v(0)*v(2),   m(0, 3) = 2*v(0)*temp;
        m(1, 0) = -2*v(1)*v(0),   m(1, 1) = 1-2*v(1)*v(1),  m(1, 2) = -2*v(1)*v(2),   m(1, 3) = 2*v(1)*temp;
        m(2, 0) = -2*v(2)*v(0),   m(2, 1) = -2*v(2)*v(1),   m(2, 2) = 1-2*v(2)*v(2),  m(2, 3) = 2*v(2)*temp;
        m(3, 0) = 0,              m(0, 1) = 0,              m(0, 2) = 0,              m(3, 3) = 1;

        return Transformation(m);
    }

}