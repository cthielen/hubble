//
//  GLView.h
//  dumbgl
//
//  Created by Wesley Waugh on 14/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import "IRenderingEngine.hpp"

@interface GLView : UIView {
    EAGLContext* m_context;
    struct IRenderingEngine *m_rendering_engine;
    float m_timestamp;
}

- (void) drawView: (CADisplayLink*) display_link;
- (void) didRotate: (NSNotification*) notification;

@end
