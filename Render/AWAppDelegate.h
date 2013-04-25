//
//  AWAppDelegate.h
//  Render
//
//  Created by Lucas Tenório on 04/04/13.
//  Copyright (c) 2013 AwesomeInc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AWDrawerView.h"
@interface AWAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet AWDrawerView *drawerView;

@end
