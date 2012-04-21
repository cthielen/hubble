#ifndef dumbgl_game_hpp
#define dumbgl_game_hpp

#include <list>
#import "IRenderingEngine.hpp"

using namespace std;

class Game {
public:
    Game();
    void update(float dt);
    void init(IRenderingEngine *);

private:
    list<Sprite *> *m_ships;
    IRenderingEngine *m_rendering_engine;
};

extern Game *game;

#endif
