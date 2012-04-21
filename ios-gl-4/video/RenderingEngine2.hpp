//
//  RenderingEngine.h
//  dumbgl
//
//  Created by Wesley Waugh on 14/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef dumbgl_RenderingEngine_h
#define dumbgl_RenderingEngine_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "IRenderingEngine.hpp"

#define STRINGIFY(A) #A
#include "shaders/blap.frag"
#include "shaders/blap.vert"

#include "sprite.hpp"
#include <list>

class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void init(int w, int h);
    void render();
private:
    GLuint build_shader(const char *src, GLenum shader_type) const;
    GLuint build_program(const char *vert_shader, 
                         const char *frag_shader) const;
    void apply_ortho(float max_x, float max_y) const;
    void apply_rotation(float degrees) const;
    
    GLuint m_framebuffer;
    GLuint m_renderbuffer;

    struct {
        GLint position, color;
    } m_blap_slots;
    GLuint m_blap_program;
    
    // debug
    GLuint last_position_slot, last_color_slot;
};

IRenderingEngine *CreateRenderer2();

#endif
