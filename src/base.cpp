#include "base.h"
#include <algorithm>


Scene::~Scene()
{
    SDL_DestroyTexture(bgTexture);
}


void SDL_RenderFillRoundedRect(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color color, int colorOffset)
{

    int less_side = std::min(width, height);

    // SDL_SetRenderDrawColor(renderer, color.r - colorOffset, color.g - colorOffset, color.b - colorOffset, SDL_ALPHA_OPAQUE);

    SDL_Rect crossRectVertical = {x + less_side / 4, y, width - less_side / 2, height};
    SDL_Rect crossRectHorizontal = {x, y + less_side / 4, width, height - less_side / 2};
    SDL_RenderFillRect(renderer, &crossRectVertical);
    SDL_RenderFillRect(renderer, &crossRectHorizontal);

    SDL_RenderFillCircle(renderer, x + less_side / 4, y + less_side / 4, (less_side / 4) - 1);
    SDL_RenderFillCircle(renderer, x + width - less_side / 4, y + less_side / 4, (less_side / 4) - 1);
    SDL_RenderFillCircle(renderer, x + width - less_side / 4, y + height - less_side / 4, (less_side / 4) - 1);
    SDL_RenderFillCircle(renderer, x + less_side / 4, y + height - less_side / 4, (less_side / 4) - 1);

    #ifdef _DEBUGG
    
    SDL_Rect outline{x, y, width, height};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawRect(renderer, &outline);

    #endif
}


int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


Button::~Button()
{

}


Button::Button(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, SDL_Color color, TTF_Font *font, SDL_Color textColor) : text(text), x(x), y(y), w(w), h(h), font(font), buttonColor(color), buttonTextColor(textColor)
{
    
}


void Button::draw(SDL_Renderer *renderer)
{
    // SDL_Rect rect = {x, y, w, h};
    textSurface = TTF_RenderText_Shaded(font, text.c_str(), buttonTextColor, {buttonColor.r, buttonColor.g, buttonColor.b});
    SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, buttonColor.r, buttonColor.g, buttonColor.b));
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {x + (w - textSurface->w) / 2, y + (h - textSurface->h) / 2, textSurface->w, textSurface->h};
    if(buttonColor.a){
        SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_RenderFillRoundedRect(renderer, x, y, w, h, buttonColor, 0);
    }
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
}


bool Button::isMouseOver(int mouseX, int mouseY)
{
    return mouseX >= x && mouseX <= x + w && mouseY >= y && mouseY <= y + h;
}


void Button::onMouseOver()
{
    colorOffset = 0;
}


int Button::onClick()
{
    if (text == "Quit")
    {
        return -1;
    } else if (text == "Play") {
        return 1;
    }
    return 0;
}

Label::Label(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, TTF_Font *labelFont) : x(x), y(y), w(w), h(h), font(labelFont), labelRenderer(renderer), text(text)
{
    SDL_Surface* textSurface = TTF_RenderText_Shaded(labelFont, text.c_str(), SDL_Color{0, 0, 255, 255}, SDL_Color{0, 0, 0, 255});
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
}

Label::~Label()
{
}

void Label::draw(SDL_Renderer *renderer)
{
    // if (text == "")
    // {
    //     text = "ERROR";
    // }
    // textSurface = TTF_RenderText_Shaded(font, text.c_str(), SDL_Color{0, 0, 255, 255}, SDL_Color{0, 0, 0, 255});
    // texture = SDL_CreateTextureFromSurface(labelRenderer, textSurface);
    // SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, 0, 0, 0));
    // textRect = {x + (w - textSurface->w) / 2, y + (h - textSurface->h) / 2, textSurface->w, textSurface->h};

    // SDL_RenderCopy(renderer, texture, &textRect, nullptr);

    // SDL_FreeSurface(textSurface);
    // SDL_DestroyTexture(texture);

    textSurface = TTF_RenderText_Shaded(font, text.c_str(), textColor, {bgColor.r, bgColor.g, bgColor.b});
    SDL_SetColorKey(textSurface, SDL_TRUE, SDL_MapRGB(textSurface->format, bgColor.r, bgColor.g, bgColor.b));
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = {x + (w - textSurface->w) / 2, y + (h - textSurface->h) / 2, textSurface->w, textSurface->h};
    // if(bgColor.a){
    //     SDL_RenderFillRoundedRect(renderer, x, y, w, h, bgColor, colorOffset);
    // }
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
}

void Label::change_text(std::string newText)
{
    text = newText; 
}
