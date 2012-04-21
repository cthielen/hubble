#import "../game/sprite.hpp"

const ColorVertex dumbarrow[] = {
    {{-0.5, -0.8}, {1, 0, 0, 1}},
    {{0.5, -0.8},  {1, 0, 0.5, 1}},
    {{0, 1},       {1, 0, 1, 1}},
    {{0.5, -0.8},  {0.5, 1, 0, 1}},
    {{-0.5, -0.8}, {0, 1, 0, 1}},
    {{0, -0.3},    {1, 1, 0, 1}}
};

Sprite::Sprite(float x, float y) {
    m_position = vec2(x, y);
    m_heading = vec2(0, 0);
    m_vertices = dumbarrow;
}

void Sprite::draw() {
}
