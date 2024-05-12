#ifndef INTERACTIONS_HPP
#define INTERACTIONS_HPP

#include <SDL2/SDL.h>
#include <math.h>

#include <vector>

#include "Ball.hpp"
#include "Functions.hpp"
#include "GlobalVariables.hpp"
#include "Robot.hpp"

class Interactions
{
   private:
    Ball & ball;
    std::vector<Robot *> robots;

   public:
    Interactions(Ball & ball, std::vector<Robot *> robots);
    void robotsCatchBall();
    void robotsThrowBall();

   private:
    bool itIsClose(double a, double b);
    void robotCatchBall(Robot * robot);
    void robotThrowBall(Robot * robot);
};

#endif
