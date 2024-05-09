#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "GlobalVariables.hpp"

class Ball
{
public:
    // Construtor para definir posição, raio e cor
    Ball(int x, int y, int radius, SDL_Color color);

    // Função para desenhar a bola no renderizador
    void draw(SDL_Renderer *renderer);

    // Função para mover a bola
    void move();

    // Função para inverter a direção da bola
    void invertX();
    void invertY();

    // Função para obter a posição da bola
    int getX();
    int getY();
    Vector2D getCoordinates() const;
    void setCoordinates(const Vector2D &newCoordinates);

    // Função para obter o raio da bola
    int getRadius();

    // Função para definir a velocidade da bola
    void setSpeed(int dx, int dy);

    // Função para definir a cor da bola
    void setColor(SDL_Color color);

private:
    int _x;
    int _y;
    int _radius;
    SDL_Color _color;

    // velocidade da bola
    float _dx;
    float _dy;
};

#endif // BALL_H
