//
//  AWDrawerView.m
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#import "AWDrawerView.h"
#include <OpenGL/gl.h>
#include "Canvas.h"
#include "World.h"
#include "Camera.h"
#include <vector>
#include "Reader.h"
#include "Rasterizer.h"
@implementation AWDrawerView {
    drawing::Canvas * canvas;
    rendering::World * world;
    std::vector<data::Mesh> * mesh;
}


- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format {
    self = [super initWithFrame:frameRect pixelFormat:format];

    if (self) {
        [self config];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self config];
    }
    return self;
}
- (void) config {
    self.lineWidth = 1;
    self.width = self.frame.size.width;
    self.height = self.frame.size.height;
    canvas = new drawing::Canvas(self.frame.size.width, self.frame.size.height);
    
}
-(void) drawRect: (NSRect) bounds
{
    glClearColor(0, 0, 0, 0);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(canvas->getWidth(),canvas->getHeight(),GL_RGBA,GL_UNSIGNED_BYTE,canvas->getBuffer());
    glEnable(GL_DEPTH_TEST);
    glFlush();
}



- (void) mouseDown:(NSEvent *)theEvent {
    //Metodo GAMBI para testar o render
    NSString * pathCamera = [[NSBundle mainBundle] pathForResource:@"camera" ofType:@"cfg"];

    rendering::PerspectiveCamera * camera = io::Reader::readCamera([pathCamera UTF8String]);

    NSString * pathMesh = [[NSBundle mainBundle] pathForResource:@"objeto" ofType:@"byu"];

    NSString * pathLight = [[NSBundle mainBundle] pathForResource:@"iluminacao" ofType:@"txt"];

    std::pair<rendering::World *, std::vector<data::Mesh *> > worldMeshPair = io::Reader::readWorld([pathLight UTF8String], [pathMesh UTF8String]);
    
    drawing::Rasterizer raster(canvas);

    raster.rasterize(worldMeshPair.first, camera);
    
    [self setNeedsDisplay:YES];
}

@end
