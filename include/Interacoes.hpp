#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include "Robot.hpp"
#include "Ball.hpp"
#include "GlobalVariables.hpp"

class Interacoes
{
public:
    Interacoes(Ball &ball, Robot &robot);
    void setNewCoor();
    // bool roboComBola();
    void catchBall();
    bool itIsClose(double a, double b);
    void lancaBola();
    void interationRobotBall();

private:
    Ball ball;
    Robot robot;
    // bool roboEstaComBola;
    Vector2D ballCoor;
    Vector2D robotCoor;
};