#ifndef INTERACOES_HPP
#define INTERACOES_HPP

#include <SDL2/SDL.h>
#include "struct.hpp"
bool itIsClose(double a, double b);
bool robotCatchBall(Vector2D robotCoor, Vector2D ballCoor);
void throwBall();
#endif