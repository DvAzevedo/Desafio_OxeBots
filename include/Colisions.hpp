#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include "Robot.hpp"
#include "Ball.hpp"
#include "GlobalVariables.hpp"

class RobotBallCollision
{
public:
    Colisions(Ball, Robot);
    bool checkColision();
    void getNewCordinates();
    void changeBallDirection();
}