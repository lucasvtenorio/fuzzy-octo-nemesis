//
//  Vector.h
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//


#ifndef __Render__Vector__
#define __Render__Vector__

#include "Matrix.h"

namespace math{
    template <class Number>
    class Vector : public Matrix<Number> {

    public:
        Vector(int n);

        Number & operator()(int i){
            return this->data[i][0];
        }
        

    };
}
//int my_main();
#endif /* defined(__Render__Vector__) */
