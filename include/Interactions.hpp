#ifndef INTERACTIONS_HPP
#define INTERACTIONS_HPP

#include <SDL2/SDL.h>
#include <math.h>

#include <vector>

#include "Ball.hpp"
#include "GlobalVariables.hpp"
#include "Robot.hpp"
#include "Functions.hpp"

class Interactions
{
private:
    Ball &ball;
    std::vector<Robot *> robots;

public:
    Interactions(Ball &ball, std::vector<Robot *> robots);
    void robotsCatchBall();

private:
    bool itIsClose(double a, double b);
    bool robotCatchBall(Robot *robot);
};
//     if (robot1.getWithBall() && robot1.getThrowBall())
//     {
//         cout << "Aqui\n";
//         robot1.setThrowBall(false);
//         robot1.setWithBall(false);
//         ball.setIsCatch(false);
//         ball.setJustBeenThrow(true);
//         // cout << robot1.getXSpeed();
//         // cout << robot1.getYSpeed();
//         ball.setSpeed(robot1.getXSpeed(), robot1.getYSpeed());
//     }

//    if (robotCatchBall(robot1.getCoordinates(), ball.getCoordinates()))
//     {
//         if (!(ball.getJustBeenThrow()))
//         {
//             ball.setCoordinates(robot1.getCoordinates());
//             ball.setIsCatch(true);
//             robot1.setWithBall(true);
//         }
//     }
//     else
//     {
//         ball.setJustBeenThrow(false);
//     }

#endif