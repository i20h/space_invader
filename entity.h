#ifndef ENTITY_H
#define ENTITY_H

#include "mingl/gui/sprite.h"

class entity
{
protected:
    nsGui::Sprite sprite;

public:
    entity(nsGraphics::Vec2D coords, nsGui::Sprite sprite);
    virtual void draw(MinGL& window);
    nsGraphics::Vec2D getPosition() const;
    void setPosition(nsGraphics::Vec2D position);
    nsGraphics::Vec2D computeSize();
    bool isColliding(const nsGui::Sprite& other) const;
    nsGui::Sprite& getSprite();
};

#endif // ENTITY_H
