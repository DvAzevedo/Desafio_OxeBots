#ifndef COLISIONS_HPP
#define COLISIONS_HPP

#include <SDL2/SDL.h>
#include <math.h>

#include <vector>

#include "Ball.hpp"
#include "Functions.hpp"
#include "GlobalVariables.hpp"
#include "Robot.hpp"

class Colisions
{
   private:
    Ball & ball;
    std::vector<Robot *> robots;

   public:
    Colisions(Ball & ball, std::vector<Robot *> robots);
    void checkColisions();

   private:
    void checkBallColisions();
    void checkBallRobotColisions(Robot * robot);
};

#endif  // COLISIONS_HPP
