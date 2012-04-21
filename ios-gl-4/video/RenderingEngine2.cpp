// OpenGL ES 2.0 rendering engine

#import "RenderingEngine2.hpp"
#import <vector>
#import <list>

RenderingEngine2::RenderingEngine2() {
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
}

void RenderingEngine2::init(int w, int h) {
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                              GL_RENDERBUFFER, m_renderbuffer);
    
    glViewport(0, 0, w, h);

    m_blap_program = build_program(blap_vert, blap_frag);
    glUseProgram(m_blap_program);
    // After a program object has been linked successfully, the index values
    // for attribute variables remain fixed until the next link command occurs.
    // The strings are the variable names used in the shader source.
    m_blap_slots.position = glGetAttribLocation(m_blap_program, "pos");
    m_blap_slots.color = glGetAttribLocation(m_blap_program, "src_color");

    if(m_blap_slots.position < 0 || m_blap_slots.color < 0) {
        printf("Unable to get a slot in the shader. Check variable names.\n");
        exit(-1);
    }

    apply_ortho(2, 3);
    glClearColor(0, 0, 0, 1);
}

/*
void RenderingEngine2::on_rotate(DeviceOrientation orient) {
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
 */

IRenderingEngine *CreateRenderer2() {
    return new RenderingEngine2();
}

GLuint RenderingEngine2::build_program(const char *vert_src, 
                                       const char *frag_src) const {
    GLuint vertex_shader = build_shader(vert_src, GL_VERTEX_SHADER);
    GLuint frag_shader = build_shader(frag_src, GL_FRAGMENT_SHADER);
    
    GLuint prg_handle = glCreateProgram();
    glAttachShader(prg_handle, vertex_shader);
    glAttachShader(prg_handle, frag_shader);
    glLinkProgram(prg_handle);
    
    GLint link_ok;
    glGetProgramiv(prg_handle, GL_LINK_STATUS, &link_ok);
    if(link_ok == GL_FALSE){
        GLchar messages[256];
        glGetProgramInfoLog(prg_handle, sizeof(messages), 0, messages);
        std::cout << messages;
        exit(1);
    }
    return prg_handle;
}

GLuint RenderingEngine2::build_shader(const char *src, 
                                      GLenum shader_type) const {
    GLuint handle = glCreateShader(shader_type);
    glShaderSource(handle, 1, &src, 0);
    glCompileShader(handle);
    
    GLint res;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
        GLchar messages[256];
        glGetShaderInfoLog(handle, sizeof(messages), 0, messages);
        std::cout << messages;
        exit(1);
    }
    return handle;
}

void RenderingEngine2::apply_ortho(float max_x, float max_y) const {
    float a = 1. / max_x;
    float b = 1. / max_y;
    float ortho[16] = {
        a, 0,  0, 0,
        0, b,  0, 0,
        0, 0, -1, 0,
        0, 0,  0, 1
    };
    
    GLint proj_uniform = glGetUniformLocation(m_blap_program, "projection");
    glUniformMatrix4fv(proj_uniform, 1, 0, ortho);
}

void RenderingEngine2::apply_rotation(float degrees) const {
    float radians = degrees * 3.14159 / 180.;
    float s = std::sin(radians);
    float c = std::cos(radians);
    float z_rot[16] = {
        c, s, 0, 0,
       -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    GLint mv_uniform = glGetUniformLocation(m_blap_program, "modelview");
    glUniformMatrix4fv(mv_uniform, 1, 0, z_rot);
}

const vec2 square_strip[4] = {vec2(0, 0), vec2(0, 1), vec2(1, 0), vec2(1, 1)};

void RenderingEngine2::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(m_blap_slots.position);
    
    std::list<Sprite *>::iterator iter;
    for(iter = to_render->begin(); iter != to_render->end(); iter++) {
        (*iter)->render();
        glVertexAttribPointer(m_blap_slots.position, 2, GL_FLOAT, GL_FALSE,
                              sizeof(vec2), &square_strip[0].x);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 
                     sizeof(square_strip) / sizeof(vec2));
    }
    
    glDisableVertexAttribArray(m_blap_slots.position);
}

