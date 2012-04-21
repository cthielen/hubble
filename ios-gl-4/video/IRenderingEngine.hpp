//
//  IRenderingEngine.h
//  dumbgl
//
//  Created by Wesley Waugh on 14/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef dumbgl_IRenderingEngine_h
#define dumbgl_IRenderingEngine_h

#import "sprite.hpp"
#import <list>

enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown,
};

struct IRenderingEngine {
    virtual void init(int w, int h) = 0;
    virtual void render() = 0;
    virtual ~IRenderingEngine() {};
    std::list<Sprite *> *to_render = new std::list<Sprite *>(64);
};

struct IRenderingEngine *CreateRenderer1();
struct IRenderingEngine *CreateRenderer2();

#endif
