//
//  IndexedTriangle.h
//  Render
//
//  Created by Lucas Tenório on 18/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#ifndef Render_IndexedTriangle_h
#define Render_IndexedTriangle_h

namespace data{
    struct IndexedTriangle{
        unsigned int idA;
        unsigned int idB;
        unsigned int idC;

        IndexedTriangle(unsigned int aa=0, unsigned int bb=0, unsigned cc=0){
            idA = aa, idB = bb, idC = cc;
        }
    };
}

#endif
