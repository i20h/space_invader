#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class bullet : public entity
{
public:
    bullet(nsGraphics::Vec2D coords);
    virtual ~bullet() = default;
    void move();
};

#endif // BULLET_H
