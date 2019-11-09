/**
 * @file MainMenu.cpp
 * @defgroup MainMenu Main Menu
 * @ingroup MainMenu
 * @author Marco Deuscher
 * @date 05.11.2019
 * @brief Implementing Main Menu
 */


#include <iostream>
#include "MainMenu.h"

#define FONTS_MAINMENU_PATH ("Fonts/arial.ttf")
#define FONTS_TITLE_PATH ("Fonts/orange juice 2.0.ttf")
#define BACKGROUNDIMAGE_MAINMENU_PATH ("images/MainMenu/background.jpg")


//Todo alle drawables in einen std::vector<drawable> packen (Problem ist das iterieren darüber!
//todo alles unabhängig von der Fenstergröße machen


/**
 * @brief Constructor
 *
 * @param window                Window in which the main menu is drawn
 * @param windowWidth           width of the given window
 * @param windowHeight          height of the given window
 */
MainMenu::MainMenu(sf::RenderWindow *window, const int windowWidth, const int windowHeight, gameState *gs) : windowWidth(windowWidth),
                                                                                  windowHeight(windowHeight) {
    mainMenuWindow = window;
    currentGameState = gs;
}

/**
 * @brief       initializing MainMenu
 * @note        in this init function the font is loaded, the text initialized
 *
 * @return      MAINMENU_FONTLOADING_ERROR if loading the font failed, MAINMENU_SUCCESS if successfull
 */
int MainMenu::initMainMenu() {
    if (!mainMenuFont.loadFromFile(FONTS_MAINMENU_PATH))
        return MAINMENU_FONTLOADING_ERROR;
    if(!titleFont.loadFromFile(FONTS_TITLE_PATH))
        return MAINMENU_FONTLOADING_ERROR;
    if(!backgroundImage.loadFromFile(BACKGROUNDIMAGE_MAINMENU_PATH))
        return MAINMENU_IMAGELOADING_ERROR;


    backgroundSprite.setTexture(backgroundImage);

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


    return MAINMENU_SUCCESS;
}

/**
 * @brief       this function is called from the main game loop
 *
 * @return      MAINMENU_SUCCESS if successfull
 */
int MainMenu::handleMainMenu() {
    //sf::Event event;
    while (mainMenuWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mainMenuWindow->close();
    }

    handleMouseCursor();

    mainMenuWindow->clear();
    mainMenuWindow->draw(backgroundSprite);
    mainMenuWindow->draw(textStartGame);
    mainMenuWindow->draw(textLeaveGame);
    mainMenuWindow->draw(textTitle);

    mainMenuWindow->display();


    return MAINMENU_SUCCESS;
}

/**
 * @brief   handle everything MouseCursor related inside this function. Color of text is changed is hovering above
 *          Also checking for Mouse Button presses on the textfield, so they act es buttons!
 * @note Take care, that imageCoords have to be transformed to global coords
 */
void MainMenu::handleMouseCursor() {
    //get current mouse position relative to the window and convert from images coords to global coords
    currMousePos = sf::Mouse::getPosition(*mainMenuWindow);
    currWorldMousePos = mainMenuWindow->mapPixelToCoords(currMousePos);
    if (textStartGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        textStartGame.setColor(sf::Color::Cyan);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            //Todo handle button press und nur einzelnen click handeln, sonst über mehrere frames mehrfach!
            std::cout << "Button is pressed" << std::endl;
            *currentGameState = gameState::INGAME;
        }
    } else {
        textStartGame.setColor(sf::Color::White);
    }

    if (textLeaveGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        textLeaveGame.setColor(sf::Color::Red);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            //Todo sauberes abbrechen des Spiels!
            mainMenuWindow->close();
            std::exit(0);
        }
    } else {
        textLeaveGame.setColor(sf::Color::White);
    }
}