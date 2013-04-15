//
//  AWAppDelegate.m
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#import "AWAppDelegate.h"
#import "AWDrawerView.h"
#include "Vector.h"

@implementation AWAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
//    NSImageView *view = [[NSImageView alloc] initWithFrame:CGRectMake(0.0, 0.0, 340.0, 340.0)];
//    view.image = [NSImage imageNamed:@"teste.png"];
    math::Matrix<double> m(3, 3);
    math::Matrix<double> m2(3, 3);
    double t = 1;
    for(int i = 0; i < m.rowCount(); i++){
        for(int j = 0; j < m.columnCount(); j++){
            m(i, j) = t;
            m2(i, j) = t;
            t++;
        }
    }
    math::Matrix<double> m3 = math::Matrix<double>::createIdentity(4);
    m.print();
    m2.print();
    m3.print();


    math::Matrix<double> M(3, 1);
    math::Matrix<double> M1(3, 1);
    math::Matrix<double> M2(M);
    math::Vector<double> v(3);
    math::Vector<double> u(3);
    v(0) = 4, v(1) = 5, v(2) = 6;
    u(0) = 1, u(1) = 2, u(2) = 3;
    u.print();
    math::Matrix<double> uahsduashdu = u + v;
    uahsduashdu.print();


    
}

@end
