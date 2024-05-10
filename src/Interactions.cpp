#include "../include/Interactions.hpp"

Interactions::Interactions(Ball &ball, std::vector<Robot *> const robots)
    : ball(ball), robots(robots)
{
}

void Interactions::robotsCatchBall()
{
    for (auto robot : robots)
        if (robotCatchBall(robot))
        {
            break;
        }
}

bool Interactions::itIsClose(double a, double b)
{
    double distancia = a - b;
    if ((distancia * distancia) <= 400)
    {
        return true;
    }
    return false;
}

bool Interactions::robotCatchBall(Robot *robot)
{
    if (itIsClose(robot->getX(), ball.getX()) && itIsClose(robot->getY(), ball.getY()))
    {

        if (!(robot->getJustThrowBall()))
        {
            ball.setPosition(robot->getX(), robot->getY());
            ball.setIsCatch(true);
            robot->setWithBall(true);
            return true;
        }
    }
    else
    {
        robot->setJustThrowBall(false);
    }
    return false;
}
