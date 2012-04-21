#import "vector.hpp"

struct ColorVertex {
    float position[2];
    float color[4];
};

class Sprite {
public:
    Sprite(float x, float y);
    void draw();
private:
    vec2 m_position, m_heading;
    float width, height;
    // Need textures, geometry, lots of fun stuff
    const struct ColorVertex *m_vertices;
};
