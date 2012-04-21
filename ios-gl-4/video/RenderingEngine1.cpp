//
//  RenderingEngine.cpp
//  dumbgl
//
//  Created by Wesley Waugh on 14/04/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "RenderingEngine1.h"

struct Vertex {
    float position[2];
    float color[4];
};

const Vertex dumbarrow[] = {
    {{-0.5, -0.8}, {1, 0, 0, 1}},
    {{0.5, -0.8},  {1, 0, 0.5, 1}},
    {{0, 1},       {1, 0, 1, 1}},
    {{0.5, -0.8},  {0.5, 1, 0, 1}},
    {{-0.5, -0.8},  {0, 1, 0, 1}},
    {{0, -0.3},     {1, 1, 0, 1}}
};

RenderingEngine1::RenderingEngine1() {
    glGenRenderbuffersOES(1, &m_renderbuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderbuffer);
}

void RenderingEngine1::init(int w, int h) {
    glGenFramebuffersOES(1, &m_framebuffer);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_framebuffer);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_renderbuffer);
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    
    glViewport(0, 0, w, h);
    glOrthof(-2, 2, -3, 3, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void RenderingEngine1::render() {
    glPushMatrix();
    glRotatef(m_angle, 0, 0, 1);
    
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &dumbarrow[0].position[0]);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &dumbarrow[0].color[0]);
    
    GLsizei vertexCount = sizeof(dumbarrow) / sizeof(Vertex);
    
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glPopMatrix();
}

void RenderingEngine1::update_animation(float dt) {
    
}

void RenderingEngine1::on_rotate(DeviceOrientation orient) {
    switch(orient) {
        case DeviceOrientationLandscapeLeft:
            m_angle = 270;
            break;
        case DeviceOrientationLandscapeRight:
            m_angle = 90;
            break;
        case DeviceOrientationPortraitUpsideDown:
            m_angle = 180;
            break;
        default:
            m_angle = 0;
    }
}

IRenderingEngine *CreateRenderer1() {
    return new RenderingEngine1();
}
