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

- (IBAction)openFile:(id)sender {
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    [panel setCanChooseFiles:YES];
    [panel setCanChooseDirectories:NO];
    [panel setAllowsMultipleSelection:NO];
    [panel setAllowedFileTypes:@[@"cfg", @"byu", @"txt"]];
    [panel setDelegate:self];

    [panel beginSheetModalForWindow:self.window completionHandler:^(NSInteger result) {
        if (result == NSFileHandlingPanelOKButton) {
            for (NSURL *url in [panel URLs]) {
                NSString *extension = [url pathExtension];

                if ([extension isEqualToString:@"cfg"]) {
                    [self.drawerView loadCameraWithPath:[url path]];
                    [self.drawerView refresh];
                } else if ([extension isEqualToString:@"byu"]) {
                    [self.drawerView loadObjectWithPath:[url path]];
                    [self.drawerView refresh];
                } else if ([extension isEqualToString:@"txt"]) {
                    [self.drawerView loadLightSourceWithPath:[url path]];
                    [self.drawerView refresh];
                }
            }
        }
    }];
}
- (BOOL) panel:(id)sender validateURL:(NSURL *)url error:(NSError *__autoreleasing *)outError {
    NSString *extension = [url pathExtension];
    
    if ([extension isEqualToString:@"cfg"]) {
        return YES;
    } else if ([extension isEqualToString:@"byu"]) {
        return YES;
    } else if ([extension isEqualToString:@"txt"]) {
        return YES;
    }
    NSBeep();
    return NO;
}
@end
