//
//  AppDelegate.h
//  ios-gl-4
//
//  Created by Wesley Waugh on 20/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "system/GLView.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    GLView *m_view;
}

@property (strong, nonatomic) UIWindow *m_window;

@end
