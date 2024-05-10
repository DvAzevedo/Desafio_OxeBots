#include "../include/Colisions.hpp"

Colisions::Colisions(Ball & ball, std::vector<Robot *> const robots)
: ball(ball), robots(robots)
{
}

void Colisions::checkColisions() { checkBallColisions(); }

void Colisions::checkBallColisions()
{
    for (auto robot : robots) checkBallRobotColisions(robot);
}

enum class ColideBy
{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};

void Colisions::checkBallRobotColisions(Robot * robot)
{
    SDL_Point unRotatedBall =
      RotatePoint({ball.getX(), ball.getY()}, -robot->GetAngle(),
                  {robot->GetX(), robot->GetY()});

    ColideBy collision;
    bool collided = false;

    SDL_Point closestPoint;

    if (unRotatedBall.x < robot->GetX() - ROBOT_SIZE)
    {
        closestPoint.x = robot->GetX() - ROBOT_SIZE;
        collision = ColideBy::LEFT;
    }
    else if (unRotatedBall.x > robot->GetX() + ROBOT_SIZE)
    {
        closestPoint.x = robot->GetX() + ROBOT_SIZE;
        collision = ColideBy::RIGHT;
    }
    else
        closestPoint.x = unRotatedBall.x;

    if (unRotatedBall.y < robot->GetY() - ROBOT_SIZE)
    {
        closestPoint.y = robot->GetY() - ROBOT_SIZE;
        collision = ColideBy::TOP;
    }
    else if (unRotatedBall.y > robot->GetY() + ROBOT_SIZE)
    {
        closestPoint.y = robot->GetY() + ROBOT_SIZE;
        collision = ColideBy::BOTTOM;
    }
    else
        closestPoint.y = unRotatedBall.y;

    double distance = findDistance(unRotatedBall, closestPoint);

    if (distance < ball.getRadius()) collided = true;

    if (collided) switch (collision)
        {
            case ColideBy::LEFT:
                ball.setSpeed(-BALL_SPEED, ball.getDY());
                ball.invertY();
                break;
            case ColideBy::RIGHT:
                ball.setSpeed(BALL_SPEED, ball.getDY());
                ball.invertY();
                break;
            case ColideBy::TOP:
                ball.setSpeed(ball.getDX(), -BALL_SPEED);
                ball.invertX();
                break;
            case ColideBy::BOTTOM:
                ball.setSpeed(ball.getDX(), BALL_SPEED);
                ball.invertX();
                break;
            default:
                break;
        }
}
