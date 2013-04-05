//
//  AWDrawerView.m
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#import "AWDrawerView.h"
#include <OpenGL/gl.h>
#include "AWCanvas.h"

@implementation AWDrawerView {
    //unsigned char *buffer;
    AWCanvas *canvas;
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
    canvas = new AWCanvas(self.width, self.height);
    [self setupBuffer];
}



-(void) drawRect: (NSRect) bounds
{
    canvas->getBuffer(^(unsigned char *buffer, int width, int height) {
        dispatch_async(dispatch_get_main_queue(), ^{
            glClearColor(0, 0, 0, 0);
            glDisable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawPixels(width, height,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
            //[self drawBuffer];
            glEnable(GL_DEPTH_TEST);
            glFlush();
        });
    });
    
    
}

//- (void) lineWithOrigin:(AWPoint) origin end:(AWPoint) end andColor:(AWColor) color {
//    BOOL steep = abs(end.y - origin.y) > abs(end.x - origin.x);
//    if (steep) {
//        int temp = origin.x;
//        origin.x = origin.y;
//        origin.y = temp;
//
//        temp = end.x;
//        end.x = end.y;
//        end.y = temp;
//    }
//    if (origin.x > end.x) {
//        AWPoint temp;
//        temp.x = origin.x;
//        temp.y = origin.y;
//
//        origin.x = end.x;
//        origin.y = end.y;
//
//        end.x = temp.x;
//        end.y = temp.y;
//    }
//    int dx = end.x - origin.x;
//    int dy = abs(end.y - origin.y);
//
//    int error = dx / 2;
//    int ystep;
//    int y = origin.y;
//    if (origin.y < end.y) {
//        ystep = 1;
//    } else {
//        ystep = -1;
//    }
//    for (int x = origin.x; x<end.x; x++) {
//        AWPoint temp;
//        if (steep) {
//            temp.x = y;
//            temp.y = x;
//        }else {
//            temp.x = x;
//            temp.y = y;
//        }
//        [self paintPoint:temp withColor:color];
//        error = error - dy;
//
//        if (error < 0) {
//            y = y  + ystep;
//            error = error +dx;
//        }
//    }
//}

//- (void) paintPoint:(AWPoint) point withColor:(AWColor) color {
//    if (point.x < 0 || point.x >= self.width || point.y < 0 || point.y >= self.height) {
//        return;
//    }
//    buffer[point.x * 4 + point.y * self.width * 4] = color.r;
//    buffer[(point.x * 4 + point.y * self.width * 4)  + 1] = color.g;
//    buffer[(point.x * 4 + point.y * self.width * 4)  + 2] = color.b;
//    buffer[(point.x * 4 + point.y * self.width * 4)  + 3] = color.a;
//    [self setNeedsDisplay:YES];
//}
- (void) mouseDown:(NSEvent *)theEvent {
//    AWPoint origin = (AWPoint) {200,200};
//    AWPoint end;
//    end.x = (int)[theEvent locationInWindow].x;
//    end.y = (int)[theEvent locationInWindow].y;
    AWColor color = (AWColor) {255,255,255,255};
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
- (void) setupBuffer {
    //buffer = (unsigned char *) malloc(sizeof(unsigned char) * 4 * self.width * self.height);

    //    AWPoint origin = (AWPoint) {20,2};
    //    AWPoint end = (AWPoint) {40,30};
    //    AWColor color = (AWColor) {255,255,255,255};
    //    [self lineWithOrigin:origin end:end andColor:color];
}


- (void) setFrame:(NSRect)frameRect  {
    [super setFrame:frameRect];
    canvas->setHeight(self.frame.size.height);
    canvas->setWidth(self.frame.size.width);
    self.height = self.frame.size.height;
    self.width = self.frame.size.width;
    [self setupBuffer];
}
- (void) drawBuffer {
    
}
void drawAnObject ()
{
    //glColor3f(1.0f, 0.85f, 0.35f);
    //    glBegin(GL_TRIANGLES);
    //    {
    //        glVertex3f(  0.0,  0.6, 0.0);
    //        glVertex3f( -0.2, -0.3, 0.0);
    //        glVertex3f(  0.2, -0.3 ,0.0);
    //    }

    //    glBegin(GL_POINTS);
    //    for (double i = 0.0; i < 1.0; i += 0.0001) {
    //        glVertex2f(i, 0.5);
    //    }
    //    glEnd();
    //    buffer = malloc(sizeof(unsigned char) * self.frame.size.width * self.frame.size.height);
    //
    //    glDrawPixels(200,200,GL_RGBA,GL_UNSIGNED_BYTE,buffer);
}
@end
