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
#include "Reader.h"


@implementation AWAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
//    NSImageView *view = [[NSImageView alloc] initWithFrame:CGRectMake(0.0, 0.0, 340.0, 340.0)];
//    view.image = [NSImage imageNamed:@"teste.png"];

    NSString *path = [[NSBundle mainBundle] pathForResource:@"camera" ofType:@"cfg"];
    
    rendering::PerspectiveCamera * camera = io::Reader::readCamera([path UTF8String]);
    
    path = [[NSBundle mainBundle] pathForResource:@"objeto" ofType:@"byu"];

    data::Mesh * mesh =  io::Reader::readMesh([path UTF8String]);
}

@end
