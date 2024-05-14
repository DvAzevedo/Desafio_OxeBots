#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <SDL2/SDL.h>
#include <math.h>

SDL_Point RotatePoint(SDL_Point point, double angle, SDL_Point pivot);

double findDistance(SDL_Point point_a, SDL_Point point_b);

#endif  // FUNCTIONS_HPP
