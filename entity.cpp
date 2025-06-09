#include "entity.h"

entity::entity(nsGraphics::Vec2D coords, nsGui::Sprite sprite)
    : sprite(sprite) {
         this->sprite.setPosition(coords);
    }

void entity::draw(MinGL& window) {
    window << sprite;
}

nsGraphics::Vec2D entity::getPosition() {
    return sprite.getPosition();
}

void entity::setPosition(nsGraphics::Vec2D position)
{
    sprite.setPosition(position);
}

nsGraphics::Vec2D entity::computeSize() {
    return sprite.computeSize();
}