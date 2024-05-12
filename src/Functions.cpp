#include "../include/Functions.hpp"

SDL_Point RotatePoint(SDL_Point point, double angle, SDL_Point pivot)
{
    SDL_Point new_point;
    new_point.x = (point.x - pivot.x) * cos(angle) -
                  (point.y - pivot.y) * sin(angle) + pivot.x;
    new_point.y = (point.x - pivot.x) * sin(angle) +
                  (point.y - pivot.y) * cos(angle) + pivot.y;

    return new_point;
}

double findDistance(SDL_Point point_a, SDL_Point point_b)
{
    return sqrt(pow(point_a.x - point_b.x, 2) + pow(point_a.y - point_b.y, 2));
}
