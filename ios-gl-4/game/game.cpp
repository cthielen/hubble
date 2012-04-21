#import "game.hpp"
#include <list>
using namespace std;

Game *game = new Game();

Game::Game() {
    m_ships = new list<Sprite *>();
}

void Game::init(IRenderingEngine *engine) {
    m_rendering_engine = engine;
    for(int i=0; i < 10; i++) {
        float x = (-100. + rand() % 200) / 200.;
        float y = (-100. + rand() % 200) / 200.;

        m_ships->push_back(new Sprite(x, y));
    }
}

void Game::update(float dt) {
    m_rendering_engine->to_render->clear();
    list<Sprite *>::iterator iter;
    for(iter=m_ships->begin(); iter != m_ships->end(); iter++) {
        // Lets just pretend they are all on screen.
        m_rendering_engine->to_render->push_back(*iter);
    }
}

