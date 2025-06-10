#include "party.h"

/**
 * @brief Constructs a party object with the specified window and window size.
 */
party::party(MinGL &window) : window(window)
{
    windowLenght = window.getWindowSize().getX();
    Player = new player(nsGraphics::Vec2D(0, 0), nsGraphics::Vec2D(0, windowLenght));
    int playerX = (window.getWindowSize().getX() - Player->computeSize().getX() / 2) / 2;
    int playerY = window.getWindowSize().getY() - Player->computeSize().getY();
    Player->entity::setPosition(nsGraphics::Vec2D(playerX, playerY));
} // party(MinGL &window, int windowSize)

/**
 * @brief Initializes and populates the invaders grid for the party.
 *
 * This function clears any existing invaders and creates a 3-row formation of invaders,
 * each row using a different sprite. Each row contains 6 invaders, positioned with
 * specific x and y coordinates. The invaders are spaced horizontally by 80 units,
 * and vertically by 60 units between rows. The sprites for each row are loaded from
 * predefined file paths.
 *
 * The invaders are stored in the 'invaders' member variable, which is a vector of vectors.
 */
void party::createInvaders()
{
    invaders.clear();
    invaders.resize(3);
    const char *sprites[3] = {
        "./sprite/invader-1.si2",
        "./sprite/invader-2.si2",
        "./sprite/invader-3.si2"};

    int x = 10;
    int y = 10;
    for (size_t i = 0; i < invaders.size(); ++i)
    {
        invaders[i].clear();
        for (size_t j = 0; j < 6; ++j)
        {
            invaders[i].emplace_back(nsGraphics::Vec2D(x, y), nsGui::Sprite(sprites[i]));
            x += 80;
            if (x > 410)
                x = 10;
        }
        x = 10;
        y += 60;
    }
} // createInvaders()

/**
 * @brief Executes a single iteration of the game loop for the party.
 *
 * This function performs the following actions in order:
 * 1. Handles the logic for eliminating invaders.
 * 2. Draws the current state of all invaders on the screen.
 * 3. Updates the movement of all invaders.
 * 4. Updates the movement of the player.
 */
void party::play()
{
    killInvader();
    drawInvaders();
    updateInvadersMovement();
    updatePlayerMovement();
} // play()

/**
 * @brief Draws all invaders and the player onto the game window.
 *
 * Iterates through all invader objects in the 'invaders' collection and calls their draw method,
 * rendering them to the specified window. After drawing all invaders, the player's draw method is
 * also called to render the player onto the same window.
 */
void party::drawInvaders()
{
    for (auto &row : invaders)
    {
        for (auto &inv : row)
        {
            inv.draw(window);
        }
    }
    Player->draw(window);
} // drawInvaders()

/**
 * @brief Calculates the minimum and maximum X coordinates of all invaders.
 *
 * Iterates through all invaders in the party and determines the smallest and largest
 * X positions based on their current positions and the given direction.
 *
 * @return A std::pair<int, int> where the first element is the minimum X coordinate
 *         and the second element is the maximum X coordinate among all invaders.
 */
std::pair<int, int> party::getInvadersBounds() const
{
    int minX = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    for (const auto &row : invaders)
    {
        for (const auto &inv : row)
        {
            int x = inv.getPosition(direction).getX();
            if (x < minX)
                minX = x;
            if (x > maxX)
                maxX = x;
        }
    }
    return {minX, maxX};
} // getInvadersBounds()

/**
 * @brief Returns the lowest Y-coordinate among all invaders in the party.
 *
 * Iterates through all invaders and finds the maximum Y value,
 * which corresponds to the invader positioned lowest on the screen.
 *
 * @return The largest Y-coordinate value of any invader.
 */
int party::getLowestInvaderY() const
{
    int maxY = std::numeric_limits<int>::min();
    for (const auto &row : invaders)
    {
        for (const auto &inv : row)
        {
            int y = inv.getPosition().getY();
            if (y > maxY)
                maxY = y;
        }
    }
    return maxY;
} // getLowestInvaderY()

/**
 * @brief Updates the movement of the invaders based on their current direction and position.
 *
 * This function checks the current bounds of the invaders and determines if they have reached
 * the edge of the window. If so, it moves all invaders down by a step and reverses their direction.
 * Otherwise, it moves the invaders horizontally in the current direction.
 *
 * Preconditions:
 * - The invaders' positions and movement parameters (direction, stepX, stepY, windowLenght) are properly initialized.
 *
 * Postconditions:
 * - Invaders are moved either horizontally or vertically, and direction may be reversed if an edge is reached.
 */
void party::updateInvadersMovement()
{
    auto [minX, maxX] = getInvadersBounds();
    if ((direction == 1 && maxX + stepX > windowLenght) ||
        (direction == -1 && minX - stepX < 0))
    {
        moveInvaders(nsGraphics::Vec2D(0, stepY));
        direction *= -1;
    }
    else
        moveInvaders(nsGraphics::Vec2D(stepX * direction, 0));

} // updateInvadersMovement()

/**
 * @brief Moves all invaders in the party by a specified delta.
 *
 * Iterates through each invader in the 2D invaders collection and applies
 * the given movement vector to update their positions.
 *
 * @param delta The vector by which to move each invader.
 */
void party::moveInvaders(nsGraphics::Vec2D delta)
{
    for (auto &row : invaders)
    {
        for (auto &inv : row)
        {
            inv.move(delta);
        }
    }
} // moveInvaders(nsGraphics::Vec2D delta)

/**
 * @brief Sets the player's position based on the given delta and direction.
 *
 * This function updates the player's position by applying the specified delta vector
 * and direction. It delegates the actual position update to the Player object's setPosition method.
 *
 * @param delta The change in position as a 2D vector.
 * @param direction The direction in which to move the player.
 */
void party::setPlayerPosition(const nsGraphics::Vec2D &delta)
{
    Player->setPosition(delta);
} // setPlayerPosition(const nsGraphics::Vec2D &delta, int direction)

/**
 * @brief Updates the player's movement based on the currently pressed key.
 *
 * This function checks which key is pressed and performs the corresponding action:
 * - If '0' is pressed, the function returns immediately.
 * - If the "up" key (KUp) is pressed, the player shoots (currently only returns).
 * - If the pressed key corresponds to a movement direction (found in keyToDirection),
 *   the player's position is updated accordingly.
 */
void party::updatePlayerMovement()
{
    char key = getPressedKey();

    if (key == '0')
        return;

    if (Player->canShoot() && key == KUp)
    {
        Player->shoot();
        return;
    }

    auto it = keyToDirection.find(key);
    if (it != keyToDirection.end())
    {
        setPlayerPosition(it->second);
    }
} // updatePlayerMovement()

/**
 * @brief Returns the key currently pressed by the user, or 0 if none.
 *
 * Iterates through the keys of interest and returns the first one found pressed.
 *
 * @return The code of the pressed key, or 0 if none.
 */
char party::getPressedKey() const
{
    if (window.isPressed({KLeft, false}))
        return KLeft;
    if (window.isPressed({KRight, false}))
        return KRight;
    if (window.isPressed({KUp, false}))
        return KUp;
    return '0';
} // getPressedKey() const

/**
 * @brief Removes invaders that have been hit by the player.
 *
 * Iterates through all rows of invaders and checks each invader to determine
 * if it has been hit by the player. If an invader is hit, it is removed from
 * its respective row. This function modifies the invaders container in place.
 */
void party::killInvader()
{
    for (auto &row : invaders)
    {
        auto it = row.begin();
        while (it != row.end())
        {
            if (Player->isInvaderHit(it->getSprite()))
            {
                it = row.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
} // killInvader() const

/**
 * @brief Returns the total number of invaders in the party.
 *
 * Iterates through all rows of invaders and sums up the number of invaders in each row.
 *
 * @return The total count of invaders.
 */
int party::getInvadersCount() const
{
    int count = 0;
    for (const auto &row : invaders)
    {
        count += row.size();
    }
    return count;
} // getInvadersCount() const