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
    
    NSString * cameraPath = [[NSBundle mainBundle] pathForResource:@"camera" ofType:@"cfg"];
    NSString * objectPath = [[NSBundle mainBundle] pathForResource:@"objeto" ofType:@"byu"];
    NSString * lightSourcePath = [[NSBundle mainBundle] pathForResource:@"iluminacao" ofType:@"txt"];

    [self.drawerView loadResourcesWithCameraPath:cameraPath objectPath:objectPath andLightSourcePath:lightSourcePath];
    
}

@end
