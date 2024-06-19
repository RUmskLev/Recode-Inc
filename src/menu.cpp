#include "menu.h"


Menu::Menu(SDL_Renderer* renderer, bool* gamePause)
{
    gamepause = gamePause;
    *gamepause = true;

    bgTexture = IMG_LoadTexture(renderer, "assets/Menu_background.jpg");
    if(!bgTexture) {
        logger.error(101, "Image for menu background not found!\n");
    }

    buttonsFont = TTF_OpenFont("assets/fonts/Elounda-Regular.otf", 36);
    if(!buttonsFont) {
        logger.error(101, "Font for buttons texts in menu was not found!\n");
    }

    titleFont = TTF_OpenFont("assets/fonts/Elounda-Regular.otf", 54);
    if(!titleFont) {
        logger.error(101, "Font for title text in menu was not found!\n");
    }

    Button gameTitleButton{renderer, "Recode Inc", 50, 100, 700, 150, COLOR_TRANSPARENT, titleFont, MENU_BUTTONS_TEXT_COLOR};
    Button menuPlayButton{renderer, "Play", 300, 300, 200, 70, MENU_BUTTONS_COLOR, buttonsFont, MENU_BUTTONS_TEXT_COLOR};
    Button menuExitButton{renderer, "Quit", 300, 400, 200, 70, MENU_BUTTONS_COLOR, buttonsFont, MENU_BUTTONS_TEXT_COLOR};

    objects.push_back(gameTitleButton);
    objects.push_back(menuPlayButton);
    objects.push_back(menuExitButton);
}


Menu::~Menu()
{
    SDL_DestroyTexture(bgTexture);
    TTF_CloseFont(buttonsFont);
    TTF_CloseFont(titleFont);
}


int Menu::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);

    for(auto &button : objects)
    {
        button.draw(renderer);
    }
    return 0;
}


int Menu::onClick(int mouseX, int mouseY)
{
    for (auto &button : objects)
    {
        if (button.isMouseOver(mouseX, mouseY))
        {
            return button.onClick();
        }
    }
    return 0;
}


void Menu::onMouseOver(int mouseX, int mouseY)
{
    for (auto &button : objects)
    {
        if (button.isMouseOver(mouseX, mouseY))
        {
            button.onMouseOver();
        } else {
            button.colorOffset = 0;
        }
    }
}
