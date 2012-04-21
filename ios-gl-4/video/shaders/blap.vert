const char *blap_vert = STRINGIFY(
attribute vec4 pos;
attribute vec4 src_color;
varying vec4 dest_color;
uniform mat4 projection;
uniform mat4 modelview;

void main(void) {
    dest_color = src_color;
    gl_Position = projection * modelview * pos;
}
);