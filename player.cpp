#include "player.h"

player::player(nsGraphics::Vec2D coords, nsGraphics::Vec2D limit) :
    entity (coords, nsGui::Sprite("./sprite/missile.si2")) {}

void player::setPosition(const nsGraphics::Vec2D& delta, int direction = 1) {
    nsGraphics::Vec2D position = entity::getPosition();
    int size = (direction == 1) ? sprite.computeSize().getX() : 0;

    nsGraphics::Vec2D newPosition = position + size + delta;

    if (newPosition.getX() < limit.getX() || newPosition.getX() + entity::computeSize().getX() > limit.getY()) {
        return;
    }

    entity::setPosition(newPosition);
}