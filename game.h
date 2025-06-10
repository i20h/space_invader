#ifndef GAME_H
#define GAME_H

#include <string>
#include "party.h"
#include "button.h"
#include "fpslimiter.h"
#include "mingl/mingl.h"
#include "mingl/gui/text.h"
#include "mingl/gui/sprite.h"
#include "mingl/event/event_manager.h"

#include <vector>

using namespace std;

class game
{
private:
    enum class GameState {
        Menu,
        Playing,
        Victory,
        GameOver,
        Count
    };

    MinGL window;
    party *Party;
    fpsLimiter *FPS = nullptr;
    nsGui::Sprite background;
    nsGui::Sprite gameMenu;
    nsGui::Sprite victoryScreen;
    nsGui::Sprite gameOverScreen;
    GameState state;
    vector<Button> menuButtons;


    void (game::*stateFunctions[static_cast<int>(GameState::Count)])();
    void windowClear();
    nsGraphics::Vec2D lastMousePosition = nsGraphics::Vec2D(0, 0);

    void initFunction();

public:
    game(string name, nsGraphics::Vec2D windowSize, unsigned int limitFPS);
    ~game();

    bool windowIsOpen();
    void mainMenu();
    void playGame();
    void showEndScreen();
    void playFrame();
    void updateMenuButtonsHover(const nsGraphics::Vec2D& mousePos);
    void initMenuButtons();
    void initReturnMenuButton();
    void processEvents();
};

#endif // GAME_H
