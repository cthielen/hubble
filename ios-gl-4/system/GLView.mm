//
//  GLView.m
//  dumbgl
//
//  Created by Wesley Waugh on 14/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GLView.h"
#import "sprite.hpp"
#import "../game/game.hpp"
#include "../game/game.hpp"

@implementation GLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];
        if(!m_context || ![EAGLContext setCurrentContext:m_context]) {
            api = kEAGLRenderingAPIOpenGLES1;
            m_context = [[EAGLContext alloc] initWithAPI:api];
            if(!m_context || ![EAGLContext setCurrentContext:m_context]) {
                return nil;
            }
            else{
                m_rendering_engine = CreateRenderer1();
            }
        }
        else {
            m_rendering_engine = CreateRenderer2();
        }
        
        [m_context
            renderbufferStorage: GL_RENDERBUFFER_OES
            fromDrawable: eaglLayer];
        
        m_rendering_engine->init(CGRectGetWidth(frame), 
                                 CGRectGetHeight(frame));

        [self drawView:nil];
        
        m_timestamp = CACurrentMediaTime();
        
        CADisplayLink *display_link = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        
        [display_link addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        [[NSNotificationCenter defaultCenter]
            addObserver:self selector:@selector(didRotate:) name:UIDeviceOrientationDidChangeNotification object:nil];
    }
    // This is in a really illogical place, but it just happens to be where 
    // we are aware of the rendering engine
    game->init(m_rendering_engine);
    return self;
}

+ (Class) layerClass {
    return [CAEAGLLayer class];
}

/******************************************************************************
 * This is the closest analog to the main loop. Not far off, but... I'm not
 * 100% sure how to handle  terminating. I think that is some iOS-specific
 * code. 
 *
 * while(1) {
 *    drawView();
 * }
 *****************************************************************************/
- (void) drawView: (CADisplayLink*) display_link {
    if(display_link) {
        float dt = display_link.timestamp - m_timestamp;
        m_timestamp = display_link.timestamp;
        game->update(dt);
    }
    m_rendering_engine->render();
    // Kind of don't like that this is outside of the engine, but it's
    // inherently related to iOS :(
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void) didRotate:(NSNotification *)notification {
    //UIDeviceOrientation orient = [[UIDevice currentDevice] orientation];
    //m_rendering_engine->on_rotate((DeviceOrientation)orient);
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    //UITouch *touch = [touches anyObject];
    //CGPoint location = [touch locationInView:self];
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    //UITouch *touch = [touches anyObject];
    //CGPoint location = [touch locationInView:self];
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    //UITouch *touch = [touches anyObject];
    //CGPoint previous = [touch previousLocationInView:self];
    //CGPoint current = [touch locationInView:self];
}

@end
