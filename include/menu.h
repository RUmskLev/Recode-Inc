#ifndef MENU_H
#define MENU_H

#include "base.h"
#include <string>


/**
 * @brief Class for game main menu
 * 
 */
class Menu : public Scene
{
public:
    SDL_Texture *bgTexture; // Holds background image of menu
    TTF_Font *buttonsFont; // Holds font used in buttons
    TTF_Font *titleFont; // Holds font used in game title
    std::vector<Button> objects; // Holds all buttons, that menu contains
    bool* gamepause;

    Menu(SDL_Renderer* renderer, bool* gamePause);

    ~Menu();
    
    /**
     * @brief Draws backgroung and all buttons in menu objects vector iteration.
     * 
     * @param renderer Target renderer
     * @return int Doesn't provide any data, will be fixed later
     */
    int draw(SDL_Renderer *renderer);

    /**
     * @brief Code, that runs on mouse click.
     * 
     * @param mouseX x coordinate of mouse click
     * @param mouseY y coordinate of mouse click
     * @return int Result code, if 0 - continue, 1 - load level, -1 - error.
     */
    int onClick(int mouseX, int mouseY);

    /**
     * @brief Code, that runs on mouse over menu. Needed for animations and effects.
     * 
     * @param mouseX x coordinate of mouse click
     * @param mouseY y coordinate of mouse click
     */
    void onMouseOver(int mouseX, int mouseY);
};


#endif