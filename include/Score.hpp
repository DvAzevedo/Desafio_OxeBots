#ifndef SCORE_HPP
#define SCORE_HPP

#include <SDL2/SDL.h>
#include <math.h>

#include <iostream>
#include <vector>

#include "Ball.hpp"
#include "Functions.hpp"
#include "GlobalVariables.hpp"
#include "Robot.hpp"

class Score
{
   private:
    Ball & ball;
    std::vector<Robot *> robots;
    int scoreRobot1, scoreRobot2;

   public:
    Score(Ball & ball, std::vector<Robot *> robots);
    void updateScore();
    int getScoreRobot1();
    int getScoreRobot2();
    void reset();
};

#endif
