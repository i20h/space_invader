#include "game.h"

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
}

game::~game() {
    window.stopGraphic();
    delete FPS;
    delete Party;
    FPS = nullptr;
    Party = nullptr;
}

void game::initFunction(){
    stateFunctions[static_cast<int>(GameState::Menu)] = &game::mainMenu;
    stateFunctions[static_cast<int>(GameState::Playing)] = &game::playGame;
    //stateFunctions[static_cast<int>(GameState::Victory)] = &game::showEndScreen;
    stateFunctions[static_cast<int>(GameState::GameOver)]= &game::showEndScreen;
}

bool game::windowIsOpen(){
    return window.isOpen();
}

void game::finishFrame(){
    window.finishFrame();
}

void game::playFrame() {
    window.clearScreen();
    (this->*stateFunctions[static_cast<int>(state)])();

    FPS->wait();
    finishFrame();
}

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
}

void game::updateMenuButtonsHover(const nsGraphics::Vec2D& mousePos) {
    for (auto& btn : menuButtons) {
        btn.setHover(btn.isMouseOver(mousePos));
    }
}

void game::initMenuButtons() {
    menuButtons.clear();
    menuButtons.emplace_back(
        nsGraphics::Vec2D(375, 350), nsGraphics::Vec2D(90, 16), "Start Game",
        [this]() { 
            state = GameState::Playing; 
            menuButtons.clear();
            Party = new party(window, window.getWindowSize().getX());
            Party->createInvaders();
        },
        nsGui::GlutFont::GlutFonts::BITMAP_HELVETICA_18
        );
}

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
}

void game::mainMenu(){
    processEvents();
    nsGraphics::Vec2D mousePos = lastMousePosition;
    updateMenuButtonsHover(mousePos);

    window << gameMenu;
    for (const auto& btn : menuButtons)
        btn.draw(window);

    window << nsGui::Text(nsGraphics::Vec2D(10, 580), "Version: 1.0", nsGraphics::KWhite, nsGui::GlutFont::BITMAP_HELVETICA_12);
}

void game::playGame(){
    window << background;
    Party->play();
    if (Party->getLowestInvaderY() >= 490) {
        state = GameState::GameOver;
        delete Party;
        initReturnMenuButton();
    }
}

void game::showEndScreen() {
    processEvents();
    nsGraphics::Vec2D mousePos = lastMousePosition;
    updateMenuButtonsHover(mousePos);

    window << (state == GameState::Victory ? victoryScreen : gameOverScreen);
    for (const auto& btn : menuButtons)
        btn.draw(window);
}

