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

@implementation AWDrawerView {
    drawing::Canvas * canvas;
    rendering::World * world;
    rendering::Camera * camera;
    std::Vector<data::Mesh>
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
    canvas = new drawing::Canvas(1440, 900);
    [self registerForDraggedTypes:@[NSFilenamesPboardType]];
    
}

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{

    NSPasteboard *p = [sender draggingPasteboard];
    NSURL *url = [NSURL URLFromPasteboard:p];
    
    url = nil;
    return NSDragOperationNone;
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
//    AWPoint origin = (AWPoint) {200,200};
//    AWPoint end;
//    end.x = (int)[theEvent locationInWindow].x;
//    end.y = (int)[theEvent locationInWindow].y;
    drawing::Color color = (drawing::Color) {255,255,255,255};
//    NSLog(@"(%d, %d) (%d, %d)", origin.x, origin.y, end.x, end.y);
//    [self lineWithOrigin:origin end:end andColor:color];
    int x = (int)[theEvent locationInWindow].x;
    int y = (int)[theEvent locationInWindow].y;

    int radius = 300;
    
    for ( int i = -radius; i < radius; i++) {
        canvas->drawLine(x, y, x - radius, y + i, color);
        canvas->drawLine(x, y, x + radius, y + i, color);
        canvas->drawLine(x, y, x + i, y + radius, color);
        canvas->drawLine(x, y, x + i, y - radius, color);
    }
    
    [self setNeedsDisplay:YES];
}

@end
