#include <SDL2/SDL.h>
#include <algorithm>

#ifndef ROBOT_HPP
#define ROBOT_HPP

struct RobotBody {
    // 4 vertices of the robot box body
    SDL_Point v1;
    SDL_Point v2;
    SDL_Point v3;
    SDL_Point v4;
};

class Robot {
   public:
    Robot(SDL_Color color, int x, int y);
    void Move();
    void Draw(SDL_Renderer * renderer);

    void Forward();
    void Backward();
    void Stop();

    void SetPosition(int x, int y);

    void SetVelocity(double velocity);

    void SetAngle(double angle);

    double GetAngle();
    int GetX();
    int GetY();

   private:
    int x, y;
    double velocity;
    double angle;
    SDL_Color color;
    int direction;

    RobotBody body;
    RobotBody rotatedBody;

    void Rotate(double angle);
};

#endif  // ROBOT_HPP
