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
    std::vector<data::Mesh*> meshes;
    rendering::Camera * camera;
    drawing::Rasterizer * rasterizer;
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
    rasterizer = new drawing::Rasterizer(canvas);
    [[self window] makeFirstResponder:self];
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

- (BOOL) acceptsFirstResponder {
    return YES;
}
-(void) loadResourcesWithCameraPath:(NSString *) cameraPath objectPath:(NSString *) objectPath andLightSourcePath:(NSString *)lightSourcePath {
    camera = io::Reader::readCamera([cameraPath UTF8String]);
    std::pair<rendering::World *, std::vector<data::Mesh *> > worldMeshPair = io::Reader::readWorld([lightSourcePath UTF8String], [objectPath UTF8String]);
    world = worldMeshPair.first;
    meshes = worldMeshPair.second;

    rasterizer->rasterizeAsync(world, camera, ^{
        [self setNeedsDisplay:YES];
    });
}
- (void) keyDown:(NSEvent *)theEvent {
    unsigned short keyCode = [theEvent keyCode];
    if(keyCode == 0 || keyCode == 123){
        camera->moveLeft();
    } else if(keyCode == 13 || keyCode == 126){
        //UP
        camera->moveFront(50);
    } else if(keyCode == 2 || keyCode == 124){
        //RIGHT
        camera->moveRight();
    } else if(keyCode == 1 || keyCode == 125){
        //DOWN
        camera->moveBack(50);
    }
    canvas->clear();
    rasterizer->rasterize(world, camera);
    [self setNeedsDisplay:YES];

//        rasterizer->rasterizeAsync(world, camera, ^{
//            [self setNeedsDisplay:YES];
//        });
}
- (void) mouseDown:(NSEvent *)theEvent {
//    //Metodo GAMBI para testar o render
//    NSString * pathCamera = [[NSBundle mainBundle] pathForResource:@"camera" ofType:@"cfg"];
//    NSString * pathMesh = [[NSBundle mainBundle] pathForResource:@"objeto" ofType:@"byu"];
//    NSString * pathLight = [[NSBundle mainBundle] pathForResource:@"iluminacao" ofType:@"txt"];
//
//    camera = io::Reader::readCamera([pathCamera UTF8String]);
//    std::pair<rendering::World *, std::vector<data::Mesh *> > worldMeshPair = io::Reader::readWorld([pathLight UTF8String], [pathMesh UTF8String]);
//    
//    world = worldMeshPair.first;
//    meshes = worldMeshPair.second;
//
//    rasterizer->rasterizeAsync(world, camera, ^{
//        [self setNeedsDisplay:YES];
//    });
//    //rasterizer->rasterize(world, camera);

    [self setNeedsDisplay:YES];
}

@end
