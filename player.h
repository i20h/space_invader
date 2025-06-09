#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class player : public entity
{
private:
    nsGraphics::Vec2D limit;
public:
    player(nsGraphics::Vec2D coords, nsGraphics::Vec2D limit = nsGraphics::Vec2D(0, 830));
    void setPosition(const nsGraphics::Vec2D& delta);
};

#endif // PLAYER_H
