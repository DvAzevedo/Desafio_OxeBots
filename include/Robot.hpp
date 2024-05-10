#include <SDL2/SDL.h>
#include <math.h>

#include <algorithm>
#include <iostream>

#include "Functions.hpp"
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
    void move();
    void draw(SDL_Renderer *renderer);

    void forward();
    void backward();
    void stop();
    void accelerate();
    void turnRight();
    void turnLeft();
    void stopXf();
    void stopYf();

    void setPosition(int x, int y);

    void userSetVelocity(double velocity);

    void setVelocity();

    void setAcceleration(double acceleration);

    void isChangingDirection(bool changingDirection);

    void changeDirection();

    void setAngle(double angle);

    void set_if_it_is_moving(bool);

    double getAcceleration();
    double getAngle();
    int getDirection();
    int getX();
    int getY();
    double getVelocityX();
    double getVelocityY();
    RobotBody getBody();
    double getXThrowSpeed();
    double getYThrowSpeed();
    void setWithBall(bool caughtBall);
    void setThrowBall(bool throwBall);
    void setJustThrowBall(bool justThrowBall);
    bool getWithBall();
    bool getThrowBall();
    bool getJustThrowBall();

private:
    bool changingDirection;
    bool moving;
    bool stopX, stopY;
    double acceleration;
    double angle;
    double velocity;
    double velocityMax;
    int direction;
    int x, y;
    RobotBody body;
    RobotBody rotatedBody;
    SDL_Color color;
    double xThrowSpeed, yThrowSpeed;
    bool withBall;
    bool throwBall;
    bool justThrowBall;

    void rotate(double angle);
    void setBodyPosition(int x, int y);
};

#endif // ROBOT_HPP
