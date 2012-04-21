//
//  RenderingEngine.h
//  dumbgl
//
//  Created by Wesley Waugh on 14/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef dumbgl_RenderingEngine_h
#define dumbgl_RenderingEngine_h

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRenderingEngine.hpp"

class RenderingEngine1 : public IRenderingEngine {
public:
    RenderingEngine1();
    void init(int w, int h);
    void render();
    void update_animation(float dt);
    void on_rotate(DeviceOrientation orient);
    
private:
    float m_angle;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
};

IRenderingEngine *CreateRenderer1();

#endif
