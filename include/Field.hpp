#ifndef FIELD_H
#define FIELD_H

#include <SDL2/SDL.h>
#include <math.h>

class Field
{
public:
    Field(int width, int height);

    void draw(SDL_Renderer *renderer);

private:
    int width;
    int height;
};

#endif
