//
//  Camera.h
//  Render
//
//  Created by Lucas Tenório on 16/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef __Render__Camera__
#define __Render__Camera__

#include "Point3D.h"
#include "Point2D.h"
#include "Vector3D.h"
#include "Transformation.h"

namespace rendering{
    class Camera{
        protected:
            geometry::Point3D _position;
            geometry::Vector3D direction;
            geometry::Vector3D head;
            geometry::Vector3D lateral;
        
            void fixCamera();
        public:
            Camera(const geometry::Point3D & position, const geometry::Vector3D & direction, const geometry::Vector3D & head);
            
            virtual geometry::Point2D doTheDance(geometry::Point3D point) =0;
        
            inline geometry::Point3D & position(){
                return _position;
            }
            
            inline const geometry::Point3D & position() const{
                return _position;
            }

            inline void apply(const geometry::Transformation & t){
                this->_position = t.apply(this->_position);
                this->direction = t.apply(this->direction);
                this->head = t.apply(this->head);
                
                fixCamera();
            }
            
            inline void moveFront(double dist=1){
                this->_position.x() += direction.x()*dist;
                this->_position.y() += direction.y()*dist;
                this->_position.z() += direction.z()*dist;
            }
            
            inline void moveBack(double dist=1){
                this->_position.x() -= direction.x()*dist;
                this->_position.y() -= direction.y()*dist;
                this->_position.z() -= direction.z()*dist;
            }
            
            inline void moveLeft(double dist=1){
                this->_position.x() -= lateral.x()*dist;
                this->_position.y() -= lateral.y()*dist;
                this->_position.z() -= lateral.z()*dist;
            }
            
            inline void moveRight(double dist=1){
                this->_position.x() += lateral.x()*dist;
                this->_position.y() += lateral.y()*dist;
                this->_position.z() += lateral.z()*dist;
            }
        
        void print(){
            _position.print();
            direction.print();
            head.print();
            lateral.print();
        }
            
    };
}

#endif /* defined(__Render__Camera__) */
