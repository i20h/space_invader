#include <game.h>

using namespace std;

int main(){
    game *Game = new game("Space Invader", nsGraphics::Vec2D(830, 590), 30);

    while (Game->windowIsOpen()){
        Game->playFrame();
    }

    delete Game;
    return 1;
}
