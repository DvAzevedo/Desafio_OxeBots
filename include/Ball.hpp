#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <math.h>

#include <iostream>

#include "GlobalVariables.hpp"

class Ball
{
   public:
    // Construtor para definir posição, raio e cor
    Ball(int x, int y, int radius, SDL_Color color);

    // Função para desenhar a bola no renderizador
    void draw(SDL_Renderer * renderer);

    // Função para mover a bola
    void move();

    // Função para inverter a direção da bola
    void invertX();

    void invertY();

    // Função para obter a posição da bola
    int getX();
    int getY();
    double getDX();
    double getDY();

    // Função para obter o raio da bola
    int getRadius();

    // Função para definir a velocidade da bola
    void setSpeed(int dx, int dy);

    // Função para definir a cor da bola
    void setColor(SDL_Color color);

    // Função para definir a posição da bola
    void setPosition(int x, int y);

    void setIsCatch(bool wasCatch);
    bool getIsCatch();
    bool getJustBeenThrow();
    void setJustBeenThrow(bool justBeenThrow);
    void reset();

   private:
    int _x;
    int _y;
    int startX, startY;
    int const _radius;
    SDL_Color _color;
    bool isCatch;
    bool justBeenThrow;

    // velocidade da bola
    float _dx;
    float _dy;
};

#endif  // BALL_H
