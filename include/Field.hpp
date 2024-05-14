#ifndef FIELD_H
#define FIELD_H

#include <SDL2/SDL.h>
#include <math.h>

#include "GlobalVariables.hpp"

class Field
{
   public:
    // Construtor para definir posição e dimensões
    Field(int width, int height);

    // Função para desenhar o campo no renderizador
    void draw(SDL_Renderer * renderer);

   private:
    int width;
    int height;
};

#endif  // FIELD_H
