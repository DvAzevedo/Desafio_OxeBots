

#include "../include/Interacoes.hpp"

bool itIsClose(double a, double b)
{
    double distancia = a - b;
    if ((distancia * distancia) <= 100)
    {
        return true;
    }
    return false;
}
bool robotCatchBall(Vector2D robotCoor, Vector2D ballCoor)
{
    if (itIsClose(robotCoor.x, ballCoor.x) && itIsClose(robotCoor.y, ballCoor.y))
    {
        return true;
    }
    return false;
}
void throwBall()
{
}
