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
#include "Transformation.h"

@implementation AWAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
//    NSImageView *view = [[NSImageView alloc] initWithFrame:CGRectMake(0.0, 0.0, 340.0, 340.0)];
//    view.image = [NSImage imageNamed:@"teste.png"];
    math::Matrix m = math::Matrix::createIdentity(4);
    m(1, 1) = 2;
    m(0, 3) = 1;

    geometry::Transformation t(m);
    geometry::Transformation t2 = t;
    geometry::Point3D p(1, 2, 3);
    geometry::Vector3D v(1, 2, 3);
    t.print();
    t2.print();
    geometry::Point3D res = t.apply(p);
    geometry::Vector3D resv = t.apply(v);
    res.print();
    resv.print();
}

@end
