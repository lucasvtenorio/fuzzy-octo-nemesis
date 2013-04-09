//
//  Vector.cpp
//  Render
//
//  Created by Lucas Tenório on 09/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#include "Vector.h"

namespace math{
    template<class Number>
    Vector<Number>::Vector(int n) : Matrix<Number>(3, 2){
        
    }
}

#include <cstdio>

//int my_main(){
//    printf("Hello, world!\n");
////    using namespace math;
//    
//    math::Vector<double> m(3);
//    
////    Matrix<double> m2(3, 3);
////    double t = 1;
////    for(int i = 0; i < m.rowCount(); i++){
////        for(int j = 0; j < m.columnCount(); j++){
////            m(i, j) = t;
////            m2(i, j) = t;
////            t++;
////        }
////    }
////    Matrix<double> m3 = Matrix<double>::createIdentity(4);
////    m.print();
////    m2.print();
////    m3.print();
//    return 0;
//}
