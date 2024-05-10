#include <SDL2/SDL.h>
#include <math.h>

#include <algorithm>
#include <iostream>

#include "Functions.hpp"
#include "GlobalVariables.hpp"

#ifndef ROBOT_HPP
#define ROBOT_HPP

struct RobotBody {
    // 4 vertices of the robot box body
    SDL_Point points[4];
};

class Robot {
   public:
    Robot(SDL_Color color, int x, int y);
    void setMove(SDL_Event & e);
    void Move();
    void Draw(SDL_Renderer * renderer);

    void Forward();
    void Backward();
    void Stop();
    void accelerate();
    void turnRight();
    void turnLeft();
    void StopX();
    void StopY();

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
    double getVelocityX();
    double getVelocityY();
    RobotBody getBody();

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

    void Rotate(double angle);
    void SetBodyPosition(int x, int y);
};

#endif  // ROBOT_HPP
