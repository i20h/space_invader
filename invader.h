#ifndef INVADER_H
#define INVADER_H
#include "entity.h"
#include <cstdint>

class invader : public entity
{
private:
    //uint8_t health;

public:
    invader(const nsGraphics::Vec2D& pos, const nsGui::Sprite& sprite);
    nsGraphics::Vec2D getPosition() const;
    nsGraphics::Vec2D getPosition(int direction) const;
    bool isColliding(nsGraphics::Vec2D firstCorner, nsGraphics::Vec2D secondCorner);
    void move(const nsGraphics::Vec2D& delta);
};

#endif // INVADER_H
