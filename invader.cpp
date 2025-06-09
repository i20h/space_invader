#include "invader.h"

invader::invader(const nsGraphics::Vec2D& coords, const nsGui::Sprite& sprite)
    : entity(coords, sprite) {}

nsGraphics::Vec2D invader::getPosition() const
{
    return sprite.getPosition();
}

nsGraphics::Vec2D invader::getPosition(int direction) const
{
    int size = (direction == 1) ? sprite.computeSize().getX() : 0;
    return sprite.getPosition() + nsGraphics::Vec2D(size, 0);
}

bool invader::isColliding(nsGraphics::Vec2D firstCorner, nsGraphics::Vec2D secondCorner)
{
    return sprite.getPosition().isColliding(firstCorner, secondCorner);
}

void invader::move(const nsGraphics::Vec2D& delta) {
    sprite.setPosition(sprite.getPosition() + delta);
}