#include "../include/Interactions.hpp"

using namespace std;

Interactions::Interactions(Ball & ball, std::vector<Robot *> const robots)
: ball(ball), robots(robots)
{
}

void Interactions::robotsCatchBall()
{
    for (size_t i = 0; i < robots.size(); ++i)
    {
        int j = (i + 1) % robots.size();
        if (!(robots[j]->getWithBall())) robotCatchBall(robots[i]);
    }
}

void Interactions::robotCatchBall(Robot * robot)
{
    if (itIsClose(robot->getX(), ball.getX()) &&
        itIsClose(robot->getY(), ball.getY()))
    {
        if (!(robot->getJustThrowBall()))
        {
            ball.setPosition(robot->getX(), robot->getY());
            ball.setIsCatch(true);
            robot->setWithBall(true);
        }
    }
    else
    {
        robot->setJustThrowBall(false);
    }
}

bool Interactions::itIsClose(double a, double b)
{
    double distancia = a - b;
    if ((distancia * distancia) <= DISTANCE_TO_CATCH)
    {
        return true;
    }
    return false;
}

void Interactions::robotsThrowBall()
{
    for (auto robot : robots) robotThrowBall(robot);
}
void Interactions::robotThrowBall(Robot * robot)
{
    if (robot->getWithBall() && robot->getThrowBall())
    {
        robot->setThrowBall(false);
        robot->setWithBall(false);
        robot->setJustThrowBall(true);
        ball.setIsCatch(false);
        ball.setSpeed(robot->getXThrowSpeed(), robot->getYThrowSpeed());
    }
}
