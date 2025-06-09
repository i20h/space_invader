#ifndef ENTITY_H
#define ENTITY_H

#include "mingl/gui/sprite.h"

class entity
{
protected:
    nsGui::Sprite sprite;

public:
    entity(nsGraphics::Vec2D coords, nsGui::Sprite sprite);
    void draw(MinGL& window);
    nsGraphics::Vec2D getPosition();
    void setPosition(nsGraphics::Vec2D position);
    nsGraphics::Vec2D computeSize();
};

#endif // ENTITY_H
