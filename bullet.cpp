#include "bullet.h"

bullet::bullet(nsGraphics::Vec2D coords) : entity(coords, nsGui::Sprite("./sprite/missile.si2")) {}

/**
 * @brief Moves the bullet upwards by decreasing its Y position.
 *
 * This function retrieves the current position of the bullet,
 * subtracts 10 units from its Y coordinate to move it upwards,
 * and updates the bullet's position accordingly.
 */
void bullet::move() {
    nsGraphics::Vec2D position = getPosition();
    position.setY(position.getY() - 7.5);
    setPosition(position);
} // move()