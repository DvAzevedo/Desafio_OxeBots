#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include "GlobalVariables.hpp"

#ifndef ROBOT_HPP
#define ROBOT_HPP

struct RobotBody
{
    // 4 vertices of the robot box body
    SDL_Point points[4];
};

class Robot
{
public:
    Robot(SDL_Color color, int x, int y);
    void setMove(SDL_Event &e);
    void Move();
    void Draw(SDL_Renderer *renderer);

    void Forward();
    void Backward();
    void Stop();
    void accelerate();
    void turnRight();
    void turnLeft();

    void SetPosition(int x, int y);

    void userSetVelocity(double velocity);

    void setVelocity();

    void setAcceleration(double acceleration);

    void isChangingDirection(bool changingDirection);

    void changeDirection();

    void SetAngle(double angle);

    void set_if_it_is_moving(bool);

    double getAcceleration();
    double GetAngle();
    int getDirection();
    int GetX();
    int GetY();

private:
    int x, y;
    double velocity;
    double velocityMax;
    double acceleration;
    bool moving;
    double angle;
    SDL_Color color;
    int direction;
    bool changingDirection;

    RobotBody body;
    RobotBody rotatedBody;

    void Rotate(double angle);
    void SetBodyPosition(int x, int y);
};

#endif // ROBOT_HPP