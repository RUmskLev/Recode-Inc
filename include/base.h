#ifndef BASE_H
#define BASE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "definitions.h"


/**
 * @brief Basic class for any object, that could be drawn in scenes.
 * 
 */
class Drawable
{
public:
    bool is_selected; // Contains special condition of being active by any mean. See DrawCountry code for more info.
    int colorOffset;

    Drawable() {}
    
    virtual ~Drawable() {}

    /**
     * @brief Basic function, that will check if object contains given coordinates.
     * 
     * @param mouseX x coordinate of mouse
     * @param mouseY y coordinate of mouse
     * @return true If given coordinates are inside object.
     * @return false Returned otherwise.
     */
    virtual bool isMouseOver(int mouseX, int mouseY)
    {
        return false;
    }

    /**
     * @brief Basic function, that will be called on mouse over the object.
     * 
     */
    virtual void onMouseOver() {}

    /**
     * @brief Basic function, that will be called on mouse click on the object. Should be overriden.
     * 
     * @return int result code of action, every drawable provides its own codes.
     */
    virtual int onClick() = 0;

    /**
     * @brief Basic function, that will be called every game cycle to provide object to be drawn for renderer. Should be overriden.
     * 
     * @param renderer Target renderer
     */
    virtual void draw(SDL_Renderer* renderer) = 0;
};


/**
 * @brief Base class for scenes, that could be presented in game
 * 
 */
class Scene
{
public:
    SDL_Texture* bgTexture = nullptr; // Holds background texture
    std::vector<Drawable> objects; // Should hold all objects to draw, but depricated, every child class may define its own container for drawables.

    Scene() {}

    Scene(SDL_Texture* texture) : bgTexture(texture) {}

    virtual ~Scene();

    /**
     * @brief Basic function, that will be called every game cycle to provide needed objects to be drawn for renderer. Should be overriden.
     * 
     * @param renderer Target renderer
     */
    virtual int draw(SDL_Renderer* renderer) = 0;

    /**
     * @brief Basic function, that will be called on mouse click in the scene. Should be overriden.
     * 
     * @return int result code of action.
     */
    virtual int onClick(int mouseX, int mouseY) = 0;

    /**
     * @brief Basic function, that will be called on mouse over the scene.
     * 
     */
    virtual void onMouseOver(int mouseX, int mouseY) {}
};


/**
 * @brief Class for button
 * 
 */
class Button : public Drawable
{
public:
    std::string name;
    std::string text; // Text, that written in button
    int x, y, w, h; // X of left upper corner, y of left upper corner, width and height of button
    SDL_Color buttonColor; // color, used to draw button
    SDL_Color buttonTextColor; // color, used to draw text on button
    SDL_Texture* texture; // texture of button
    SDL_Surface* textSurface; // Surface for text in button
    SDL_Rect textRect; // Source rect for text in button
    TTF_Font* font; // Font of text in button
    int colorOffset; // Defines color changes, when mouse is over the button

    Button(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, SDL_Color textColor = SDL_Color{0, 0, 0, 255});

    ~Button();

    void draw(SDL_Renderer *renderer) override;

    bool isMouseOver(int mouseX, int mouseY) override;

    void onMouseOver() override;

    int onClick() override;
};


class Label : public Drawable
{
public:
    SDL_Renderer* labelRenderer;
    SDL_Texture* texture;
    std::string text;
    SDL_Rect textRect;
    SDL_Surface* textSurface;
    SDL_Color bgColor;
    SDL_Color textColor;
    int x;
    int y;
    int w;
    int h;
    TTF_Font* font;

    Label (SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, TTF_Font* labelFont);
    ~Label ();


    void draw(SDL_Renderer* renderer);

    void change_text(std::string newText);

    int onClick() override {return 0;}
};



/**
 * @brief Renders filled rectangle with smooth angles, for now only circles as angles, later may have a to b sides scalar. Similar to SDL's SDL_RenderFill_ functions.
 * 
 * @param renderer Target renderer
 * @param x X coordinate of rectangle's left corner
 * @param y Y coordinate of rectangle's left corner
 * @param width Width of rectangle
 * @param height Height of rectangle
 * @param color_r Red part of rectangle's color (0 - 255)
 * @param color_g Green part of rectangle's color (0 - 255)
 * @param color_b Blue part of rectangle's color (0 - 255)
 */
void SDL_RenderFillRoundedRect(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color color, int colorOffset = 0);


/**
 * @brief Renders circle outline. Similar to SDL's SDL_RenderDraw_ functions.
 * 
 * @param renderer Target renderer
 * @param x X coordinate of circle's left corner
 * @param y Y coordinate of circle's left corner
 * @param radius radius of circle
 * @return int Returns -1 on error
 */
int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);


/**
 * @brief Renders filled circle. Similar to SDL's SDL_RenderFill_ functions.
 * 
 * @param renderer Target renderer
 * @param x X coordinate of circle's left corner
 * @param y Y coordinate of circle's left corner
 * @param radius radius of circle
 * @return int Returns -1 on error
 */
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

#endif