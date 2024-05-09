#pragma once
#include <SDL2/SDL.h>

struct Vector2D
{
    double x;
    double y;
    Vector2D(double xCoord = 0.0, double yCoord = 0.0) : x(xCoord), y(yCoord) {}
};

bool itIsClose(double a, double b)
{
    double distancia = a - b;
    if ((distancia * distancia) <= 25)
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
// class Interacoes
// {
// public:
//     Interacoes(Ball &ball, Robot &robot);
//     void setNewCoor();
//     // bool roboComBola();
//     void catchBall();
//     bool itIsClose(double a, double b);
//     void lancaBola();
//     void interationRobotBall();

// private:
//     Ball ball;
//     Robot robot;
//     // bool roboEstaComBola;
//     Vector2D ballCoor;
//     Vector2D robotCoor;
// };