#ifndef PARTY_H
#define PARTY_H

#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "invader.h"
#include "player.h"
#include "mingl/mingl.h"

using namespace std;

class party
{
private:
    MinGL &window;
    std::vector<std::vector<invader>> invaders;
    player *Player;
    int direction = 1;
    int windowLenght;
    const int stepX = 10;
    const int stepY = 20;
    const char KUp = 'z';
    const char KLeft = 'q';
    const char KRight = 'd';

    std::unordered_map<char, nsGraphics::Vec2D> keyToDirection = {
        {KLeft, nsGraphics::Vec2D(-5, 0)},
        {KRight, nsGraphics::Vec2D(5, 0)},
    };
public:

    party(MinGL &window);

    void createInvaders();
    void drawInvaders();
    void moveInvaders(nsGraphics::Vec2D delta);
    void updateInvadersMovement();
    void killInvader();
    std::pair<int, int> getInvadersBounds() const;
    int getLowestInvaderY() const;
    char getPressedKey() const;
    int getInvadersCount() const;

    void updatePlayerMovement();
    void setPlayerPosition(const nsGraphics::Vec2D& delta);

    void play();
};
#endif // PARTY_H
