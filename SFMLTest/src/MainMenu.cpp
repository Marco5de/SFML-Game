/**
 * @file MainMenu.cpp
 * @defgroup MainMenu Main Menu
 * @ingroup MainMenu
 * @author Marco Deuscher
 * @date 05.11.2019
 * @brief Implementing Main Menu
 */


#include <iostream>
#include <cassert>
#include "MainMenu.h"
#include "Centering.h"

#define LOGGING_LEVEL_1

#include "logger.h"

#define VOLUME 90
//#define SOUND


#define FONTS_MAINMENU_PATH ("Fonts/arial.ttf")
#define FONTS_TITLE_PATH ("Fonts/orange juice 2.0.ttf")
#define BACKGROUNDIMAGE_MAINMENU_PATH ("images/MainMenu/background.jpg")
#define IMAGE_MAINMENU_MENU_PATH ("images/MainMenu/menu.png")


//Todo alle drawables in einen std::vector<drawable> packen (Problem ist das iterieren darüber!
//todo alles unabhängig von der Fenstergröße machen


/**
 * @brief Constructor
 *
 * @param window                Window in which the main menu is drawn
 * @param windowWidth           width of the given window
 * @param windowHeight          height of the given window
 */
MainMenu::MainMenu(sf::RenderWindow &window, GameProperties &gameProperties)
        : renderWindow(window),
          gameProperties(gameProperties),
          windowWidth(gameProperties.WINDOW_WIDTH),
          windowHeight(gameProperties.WINDOW_HEIGHT) {
    ;
}

/**
 * @brief       initializing MainMenu
 * @note        in this init function the font is loaded, the text initialized
 *
 * @return      MAINMENU_FONTLOADING_ERROR if loading the font failed, MAINMENU_SUCCESS if successfull
 */
int MainMenu::init() {
    if (!mainMenuFont.loadFromFile(FONTS_MAINMENU_PATH))
        return MAINMENU_FONTLOADING_ERROR;
    if (!titleFont.loadFromFile(FONTS_TITLE_PATH))
        return MAINMENU_FONTLOADING_ERROR;
    if (!backgroundImage.loadFromFile(BACKGROUNDIMAGE_MAINMENU_PATH))
        return MAINMENU_IMAGELOADING_ERROR;
    if (!menuTexture.loadFromFile(IMAGE_MAINMENU_MENU_PATH))
        return MAINMENU_IMAGELOADING_ERROR;

    assert(mainMenuFont.loadFromFile(FONTS_MAINMENU_PATH));
    assert(titleFont.loadFromFile(FONTS_TITLE_PATH));
    assert(backgroundImage.loadFromFile(BACKGROUNDIMAGE_MAINMENU_PATH));
    assert(menuTexture.loadFromFile(IMAGE_MAINMENU_MENU_PATH));
#ifdef SOUND
    assert(music.openFromFile("Sound/fade.wav"));

    music.setVolume(VOLUME);
    music.setLoop(true);
    music.setAttenuation(0);
    music.play();
    LOG("Laden der Musik erfolgreich");
#endif

    backgroundSprite.setTexture(backgroundImage);
    menuButton.setTexture(menuTexture);

    menuButton.setPosition(.01 * windowWidth, .01 * windowHeight);
    menuButton.scale(sf::Vector2f(.25, .25));

    backgroundRect.setPosition(.1 * windowWidth, .2 * windowHeight);
    backgroundRect.setFillColor(sf::Color::Black);
    backgroundRect.setOutlineColor(sf::Color::Magenta);
    backgroundRect.setOutlineThickness(10);
    sf::Vector2f size(.75 * windowWidth, .325 * windowHeight);
    backgroundRect.setSize(size);

    textStartGame.setFont(mainMenuFont);
    textStartGame.setString("Start Game");
    textStartGame.setCharacterSize(60);
    textStartGame.setPosition(.05 * windowWidth, .9 * windowHeight);

    textLeaveGame.setFont(mainMenuFont);
    textLeaveGame.setString("Leave Game");
    textLeaveGame.setCharacterSize(60);
    textLeaveGame.setPosition(.65 * windowWidth, .9 * windowHeight);

    textTitle.setFont(titleFont);
    textTitle.setString("Hexxagon");
    textTitle.setCharacterSize(200);
    textTitle.setPosition(.15 * windowWidth, .15 * windowHeight);
    textTitle.setFillColor(sf::Color::Magenta);
    textTitle.setOutlineColor(sf::Color::Black);

    subMenuBackground.setPosition(.075 * windowWidth, .15 * windowHeight);
    subMenuBackground.setSize(sf::Vector2f(.25 * windowWidth, .5 * windowHeight));
    subMenuBackground.setFillColor(sf::Color::Black);
    subMenuBackground.setOutlineColor(sf::Color::Yellow);
    subMenuBackground.setOutlineThickness(5);

    subMenuChangeName.setPosition(.085 * windowWidth, .175 * windowHeight);
    subMenuChangeName.setCharacterSize(30);
    subMenuChangeName.setFont(mainMenuFont);
    subMenuChangeName.setString("Change name");
    subMenuChangeName.setColor(sf::Color::Yellow);
    subMenuChangeName.setOutlineThickness(5);
    subMenuChangeName.setOutlineColor(sf::Color::Blue);

    nameBackground.setPosition(.25 * windowWidth, .6 * windowHeight);
    nameBackground.setSize(sf::Vector2f(.5 * windowWidth, .15 * windowHeight));
    nameBackground.setFillColor(sf::Color::Black);
    nameBackground.setOutlineColor(sf::Color::Magenta);
    nameBackground.setOutlineThickness(5);

    displayName.setFont(mainMenuFont);
    displayName.setCharacterSize(30);
    Centering::center(nameBackground, displayName);
    displayName.setColor(sf::Color::Magenta);

    gameProperties.playerName = getStringFromFile("nameConfig.txt");

    return MAINMENU_SUCCESS;
}

/**
 * @brief       this function is called from the main game loop
 *
 * @return      MAINMENU_SUCCESS if successfull
 */
int MainMenu::handleWindow() {
    handleMouseCursor();
    //sf::Event event;
    while (renderWindow.pollEvent(event)) {
        handleEvent();
    }

    //Todo sollte nicht jedes mal neu gemacht werden --> erstellen eines rename events!
    std::string name = std::string("Hey ").append(gameProperties.playerName);
    displayName.setString(name);
    Centering::center(nameBackground, displayName);

    renderWindow.clear();
    renderWindow.draw(backgroundSprite);
    renderWindow.draw(textStartGame);
    renderWindow.draw(textLeaveGame);
    renderWindow.draw(backgroundRect);
    renderWindow.draw(textTitle);
    renderWindow.draw(menuButton);
    renderWindow.draw(nameBackground);
    renderWindow.draw(displayName);
    if (menuOpen) {
        renderWindow.draw(subMenuBackground);
        renderWindow.draw(subMenuChangeName);
    }

    renderWindow.display();


    return MAINMENU_SUCCESS;
}

/**
 * @brief   handle everything MouseCursor related inside this function. Color of text is changed is hovering above
 *          Also checking for Mouse Button presses on the textfield, so they act es buttons!
 * @note Take care, that imageCoords have to be transformed to global coords
 */
void MainMenu::handleMouseCursor() {
    //get current mouse position relative to the window and convert from images coords to global coords
    currMousePos = sf::Mouse::getPosition(renderWindow);
    currWorldMousePos = renderWindow.mapPixelToCoords(currMousePos);
    if (textStartGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        textStartGame.setColor(sf::Color::Cyan);
    } else {
        textStartGame.setColor(sf::Color::White);
    }

    if (textLeaveGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        textLeaveGame.setColor(sf::Color::Red);
    } else {
        textLeaveGame.setColor(sf::Color::White);
    }
}


void MainMenu::handleEvent() {
    if (event.type == sf::Event::Closed)
        renderWindow.close();
    else if (event.type == sf::Event::MouseButtonPressed &&
             textStartGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
        gameProperties.currentGameState = gameState::LOBBY;
    else if (event.type == sf::Event::MouseButtonPressed &&
             textLeaveGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
        renderWindow.close();

    if (event.type == sf::Event::MouseButtonPressed &&
        menuButton.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
        menuOpen ? menuOpen = false : menuOpen = true;

    if (menuOpen) {
        if (event.type == sf::Event::MouseButtonPressed &&
            subMenuChangeName.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
            gameProperties.currentGameState = gameState::CHANGENAME;
            //todo verursacht flicker, weil frame nochmal gemalt wird, bevor screen gewechselt wird
            menuOpen = false;
            renderWindow.setKeyRepeatEnabled(true);
        }

    }

}