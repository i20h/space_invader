#include "entity.h"

/**
 * @brief Constructs an entity with the specified coordinates and sprite.
 *
 * Initializes the entity's sprite and sets its position to the given coordinates.
 *
 * @param coords The initial position of the entity as a 2D vector.
 * @param sprite The sprite to be associated with the entity.
 */
entity::entity(nsGraphics::Vec2D coords, nsGui::Sprite sprite)
    : sprite(sprite) {
         this->sprite.setPosition(coords);
    } // entity(nsGraphics::Vec2D coords, nsGui::Sprite sprite)

/**
 * @brief Draws the entity's sprite onto the given MinGL window.
 *
 * This function renders the entity's sprite by sending it to the specified MinGL window.
 *
 * @param window Reference to the MinGL window where the sprite will be drawn.
 */
void entity::draw(MinGL& window) {
    window << sprite;
} // draw(MinGL& window)

/**
 * @brief Retrieves the current position of the entity.
 *
 * @return nsGraphics::Vec2D The position of the entity as a 2D vector.
 */
nsGraphics::Vec2D entity::getPosition() const {
    return sprite.getPosition();
} // getPosition() const

/**
 * @brief Sets the position of the entity's sprite to the specified coordinates.
 *
 * @param position The new position for the entity as a 2D vector.
 */
void entity::setPosition(nsGraphics::Vec2D position)
{
    sprite.setPosition(position);
} // setPosition(nsGraphics::Vec2D position)

/**
 * @brief Computes the size of the entity's sprite.
 *
 * This function calculates the size of the sprite associated with the entity.
 *
 * @return nsGraphics::Vec2D The computed size of the sprite as a 2D vector.
 */
nsGraphics::Vec2D entity::computeSize() {
    return sprite.computeSize();
} // computeSize()

/**
 * @brief Checks if the entity's sprite is colliding with another sprite.
 *
 * This function determines if the bounding boxes of the two sprites overlap,
 * indicating a collision.
 *
 * @param other The other sprite to check for collision against.
 * @return true if the sprites are colliding, false otherwise.
 */
bool entity::isColliding(const nsGui::Sprite& other) const
{
    nsGraphics::Vec2D posA = sprite.getPosition();
    nsGraphics::Vec2D sizeA = sprite.computeSize();
    nsGraphics::Vec2D posB = other.getPosition();
    nsGraphics::Vec2D sizeB = other.computeSize();

    int leftA = posA.getX();
    int rightA = posA.getX() + sizeA.getX();
    int topA = posA.getY();
    int bottomA = posA.getY() + sizeA.getY();

    int leftB = posB.getX();
    int rightB = posB.getX() + sizeB.getX();
    int topB = posB.getY();
    int bottomB = posB.getY() + sizeB.getY();

    return !(rightA < leftB || leftA > rightB || bottomA < topB || topA > bottomB);
} // isColliding(const nsGui::Sprite& other) const

/**
 * @brief Returns a reference to the sprite associated with this entity.
 *
 * This function provides access to the underlying nsGui::Sprite object
 * representing the visual appearance of the entity. Modifying the returned
 * sprite will directly affect how the entity is rendered.
 *
 * @return Reference to the entity's nsGui::Sprite.
 */
nsGui::Sprite& entity::getSprite() {
    return sprite;
} // getSprite()
