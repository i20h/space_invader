#include "game.h"

/**
 * @brief Constructs a new game object with the specified window name, size, and FPS limit.
 *
 * Initializes the main game window, background, menu screens, and sets the initial game state to Menu.
 * Also initializes the graphics context, FPS limiter, and sets up menu buttons and other necessary functions.
 *
 * @param name The title of the game window.
 * @param windowSize The size of the game window as a 2D vector.
 * @param limitFPS The maximum frames per second to limit the game loop.
 */
game::game(string name, nsGraphics::Vec2D windowSize, unsigned int limitFPS)
    : window(name, windowSize, nsGraphics::Vec2D(128, 128), nsGraphics::KBlack)
    , background("./sprite/background.si2", nsGraphics::Vec2D(0, 0))
    , gameMenu("./sprite/game-menu.si2", nsGraphics::Vec2D(0, 0))
    , victoryScreen("./sprite/game-win.si2", nsGraphics::Vec2D(0, 0))
    , gameOverScreen("./sprite/game-over.si2", nsGraphics::Vec2D(0, 0))
    , state(GameState::Menu)
{
    window.initGlut();
    window.initGraphic();
    FPS = new fpsLimiter(limitFPS);
    state = GameState::Menu;
    initFunction();
    initMenuButtons();
} // game::game(string name, nsGraphics::Vec2D windowSize, unsigned int limitFPS)

game::~game() {
    window.stopGraphic();
    delete FPS;
    delete Party;
    FPS = nullptr;
    Party = nullptr;
}

/**
 * @brief Initializes the mapping between game states and their corresponding handler functions.
 *
 * This function assigns member function pointers to the stateFunctions array,
 * associating each GameState enum value with the appropriate handler method.
 * - GameState::Menu    → game::mainMenu
 * - GameState::Playing → game::playGame
 * - GameState::Victory → game::showEndScreen
 * - GameState::GameOver→ game::showEndScreen
 *
 * This setup allows the game to call the correct function based on the current state.
 */
void game::initFunction(){
    stateFunctions[static_cast<int>(GameState::Menu)] = &game::mainMenu;
    stateFunctions[static_cast<int>(GameState::Playing)] = &game::playGame;
    stateFunctions[static_cast<int>(GameState::Victory)] = &game::showEndScreen;
    stateFunctions[static_cast<int>(GameState::GameOver)]= &game::showEndScreen;
} // initFunction()

/**
 * @brief Checks if the game window is currently open.
 *
 * This function returns true if the game window is open and false otherwise.
 * It is typically used to control the main game loop and determine when the
 * application should continue running or exit.
 *
 * @return true if the window is open, false otherwise.
 */
bool game::windowIsOpen(){
    return window.isOpen();
} // windowIsOpen()

/**
 * @brief Executes a single frame of the game loop.
 *
 * This function performs the following steps in order:
 * 1. Clears the game window for rendering a new frame.
 * 2. Invokes the current game state handler via a function pointer.
 * 3. Waits to maintain a consistent frame rate using the FPS controller.
 * 4. Finalizes and displays the rendered frame on the window.
 */
void game::playFrame() {
    window.clearScreen();
    (this->*stateFunctions[static_cast<int>(state)])();

    FPS->wait();
    window.finishFrame();
} // playFrame()

/**
 * @brief Processes all pending input events for the game window.
 *
 * This function retrieves and handles all events from the window's event manager.
 * It updates the last known mouse position on mouse movement or dragging events.
 * On mouse click events (specifically left mouse button release), it checks if any
 * menu button is under the mouse cursor and triggers its click handler if so.
 *
 * Event types handled:
 * - MouseMove / MouseDrag: Updates lastMousePosition.
 * - MouseClick (left button release): Checks for button clicks in menuButtons.
 */
void game::processEvents() {
    auto& eventManager = window.getEventManager();
    while (eventManager.hasEvent()) {
        nsEvent::Event_t evt = eventManager.pullEvent();
        if (evt.eventType == nsEvent::MouseMove || evt.eventType == nsEvent::MouseDrag) {
            lastMousePosition = nsGraphics::Vec2D(evt.eventData.moveData.x, evt.eventData.moveData.y);
        }
        if (evt.eventType == nsEvent::MouseClick) {
            if (evt.eventData.clickData.button == 0 && evt.eventData.clickData.state == 0) {
                nsGraphics::Vec2D mousePos(evt.eventData.clickData.x, evt.eventData.clickData.y);
                for (auto& btn : menuButtons) {
                    if (btn.isMouseOver(mousePos)) {
                        btn.tryClick(mousePos, true);
                    }
                }
            }
        }
    }
} // processEvents()

/**
 * @brief Updates the hover state of all menu buttons based on the mouse position.
 *
 * Iterates through each button in the menuButtons collection and sets its hover state
 * depending on whether the mouse position is over the button.
 *
 * @param mousePos The current position of the mouse cursor.
 */
void game::updateMenuButtonsHover(const nsGraphics::Vec2D& mousePos) {
    for (auto& btn : menuButtons) {
        btn.setHover(btn.isMouseOver(mousePos));
    }
} // updateMenuButtonsHover(const nsGraphics::Vec2D& mousePos)

/**
 * @brief Initializes the menu buttons for the game menu.
 *
 * This function clears any existing menu buttons and adds a "Start Game" button
 * to the menu. When the "Start Game" button is pressed, the game state is set to
 * Playing, the menu buttons are cleared, and a new Party object is created and
 * initialized with invaders.
 */
void game::initMenuButtons() {
    menuButtons.clear();
    menuButtons.emplace_back(
        nsGraphics::Vec2D(375, 350), nsGraphics::Vec2D(90, 16), "Start Game",
        [this]() { 
            state = GameState::Playing; 
            menuButtons.clear();
            Party = new party(window);
            Party->createInvaders();
        },
        nsGui::GlutFont::GlutFonts::BITMAP_HELVETICA_18
        );
}

/**
 * @brief Initializes the "Back to menu" button in the game's menu.
 *
 * This function clears any existing menu buttons and adds a new button labeled "Back to menu".
 * When the button is pressed, the game state is set to Menu and the menu buttons are re-initialized.
 * The button is positioned at (375, 400) with a size of (110, 16) and uses the BITMAP_HELVETICA_18 font.
 */
void game::initReturnMenuButton() {
    menuButtons.clear();
    menuButtons.emplace_back(
        nsGraphics::Vec2D(375, 400), nsGraphics::Vec2D(110, 16), "Back to menu",
        [this]() {
            state = GameState::Menu;
            initMenuButtons();
        },
        nsGui::GlutFont::GlutFonts::BITMAP_HELVETICA_18
    );
} // initReturnMenuButton()

/**
 * @brief Displays and manages the main menu of the game.
 *
 * This function processes user input events, updates the hover state of menu buttons
 * based on the current mouse position, and renders the main menu interface.
 * It draws all menu buttons and displays the game version information on the window.
 */
void game::mainMenu(){
    processEvents();
    nsGraphics::Vec2D mousePos = lastMousePosition;
    updateMenuButtonsHover(mousePos);

    window << gameMenu;
    for (const auto& btn : menuButtons)
        btn.draw(window);

    window << nsGui::Text(nsGraphics::Vec2D(10, 580), "Version: 1.0", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_12);
} // mainMenu()

/**
 * @brief Executes the main game loop logic for a single frame.
 *
 * This function handles rendering the background, updating the invader party,
 * and checking for game over or victory conditions. If all invaders are defeated,
 * the game state transitions to Victory. If any invader reaches the bottom threshold,
 * the game state transitions to GameOver. In both cases, the invader party is deleted
 * and the return-to-menu button is initialized.
 */
void game::playGame(){
    window << background;
    Party->play();
    if (Party->getLowestInvaderY() >= 490) {
        state = GameState::GameOver;
        delete Party;
        initReturnMenuButton();
    }

    if (Party->getInvadersCount() == 0) {
        state = GameState::Victory;
        delete Party;
        initReturnMenuButton();
    }
} // playGame()

/**
 * @brief Displays the end screen (victory or game over) and handles menu button interactions.
 *
 * This function processes user input events, updates the hover state of menu buttons
 * based on the current mouse position, and renders the appropriate end screen
 * (victory or game over) along with the menu buttons.
 *
 * The function assumes that `processEvents()`, `updateMenuButtonsHover()`, and
 * the rendering of screens and buttons are handled elsewhere in the class.
 */
void game::showEndScreen() {
    processEvents();
    nsGraphics::Vec2D mousePos = lastMousePosition;
    updateMenuButtonsHover(mousePos);

    window << (state == GameState::Victory ? victoryScreen : gameOverScreen);
    for (const auto& btn : menuButtons)
        btn.draw(window);
} // showEndScreen()


