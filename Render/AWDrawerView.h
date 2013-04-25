//
//  AWDrawerView.h
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface AWDrawerView : NSOpenGLView
- (void) drawRect: (NSRect) bounds;
@property (nonatomic) int width;
@property (nonatomic) int height;
@property (nonatomic) int lineWidth;


-(void) loadResourcesWithCameraPath:(NSString *) cameraPath objectPath:(NSString *) objectPath andLightSourcePath:(NSString *)lightSourcePath;
@end
