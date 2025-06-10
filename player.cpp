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

    if (newPosition.getX() < limit.getX() || (newPosition.getX() + entity::computeSize().getX()) > limit.getY())
        return;

    entity::setPosition(newPosition);
} // setPosition(const nsGraphics::Vec2D& delta, int direction)

/**
 * @brief Determines if the player is allowed to shoot a new bullet.
 *
 * This function checks two conditions:
 * 1. At least 0.5 seconds have passed since the last bullet was shot.
 * 2. The current number of bullets is less than or equal to the maximum allowed bullets.
 *
 * @return true if the player can shoot a new bullet, false otherwise.
 */
bool player::canShoot() const {
    return (difftime(time(nullptr), lastBulletShot) >= 0.5 && (const int)bullets.size() <= maxBullets) ? true : false;
} // canShoot()

void player::shoot() {
    if (!canShoot()) return;

    lastBulletShot = time(nullptr);
    bullets.emplace_back(getPosition() + nsGraphics::Vec2D(0, -10));
} // shoot()

void player::draw(MinGL& window) {
    entity::draw(window);
    removeOffscreenBullets();
    for (auto& bullet : bullets) {
        bullet.draw(window);
        bullet.move();
    }    
} // draw(MinGL& window)

bool player::isInvaderHit(const nsGui::Sprite& invaderSprite) {
    for (auto it = bullets.begin(); it != bullets.end(); ++it) {
        if (it->isColliding(invaderSprite)) {
            bullets.erase(it);
            return true;
        }
    }
    return false;
} // isInvaderHit(const nsGui::Sprite& invaderSprite) const

void player::removeOffscreenBullets() {
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
        [](const bullet& b) { return b.getPosition().getY() < 0; }), bullets.end());
} // removeOffscreenBullets()