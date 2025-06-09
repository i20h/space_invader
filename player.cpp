#include "player.h"

player::player(nsGraphics::Vec2D coords, nsGraphics::Vec2D limit) :
    entity (coords, nsGui::Sprite("./sprite/vessel.si2")), limit(limit) {}

/**
 * @brief Sets the player's position based on a delta vector and movement direction.
 *
 * This function calculates the new position of the player by adding the specified delta
 * and an optional size offset (depending on the direction) to the current position.
 * It ensures that the new position does not exceed the defined horizontal limits.
 * If the new position is within bounds, the player's position is updated.
 *
 * @param delta The vector by which to move the player.
 * @param direction The movement direction (1 for right, -1 for left). Defaults to 1.
 */
void player::setPosition(const nsGraphics::Vec2D& delta) {
    nsGraphics::Vec2D position = entity::getPosition();
    nsGraphics::Vec2D newPosition = position + delta;

    if (newPosition.getX() < limit.getX() || (newPosition.getX() + entity::computeSize().getX()) > limit.getY()) {
        return;
    }

    entity::setPosition(newPosition);
} // setPosition(const nsGraphics::Vec2D& delta, int direction)
