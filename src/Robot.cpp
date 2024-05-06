#include "../include/Robot.hpp"

using namespace std;

constexpr float DECAY_FACTOR = 0.9f;
constexpr int MOVE_SPEED = 5;
constexpr int ROBOT_SIZE = 20;

Robot::Robot(SDL_Color color, int x, int y)
    : velocity(1), angle(0), direction(1), changingDirection(false), velocityMax(6), moving(false), acceleration(0.5)
{
    this->x = x;
    this->y = y;

    this->color = color;
    this->body.v1 = {x - ROBOT_SIZE, y - ROBOT_SIZE};
    this->body.v2 = {x + ROBOT_SIZE, y - ROBOT_SIZE};
    this->body.v3 = {x + ROBOT_SIZE, y + ROBOT_SIZE};
    this->body.v4 = {x - ROBOT_SIZE, y + ROBOT_SIZE};
    this->rotatedBody = body;
}

void Robot::Move()
{

    setVelocity();

    int x_v = std::min(static_cast<int>(velocity * cos(angle)), int(velocity)) * direction;

    int y_v = std::min(static_cast<int>(velocity * sin(angle)), int(velocity)) * direction;

    x += x_v;
    y += y_v;

    body.v1.x += x_v;
    body.v1.y += y_v;

    body.v2.x += x_v;
    body.v2.y += y_v;

    body.v3.x += x_v;
    body.v3.y += y_v;

    body.v4.x += x_v;
    body.v4.y += y_v;

    // velocity *= DECAY_FACTOR;

    // Clamp angle to -90 to 90 degrees, so the robot can only move forward and
    // backward
    if (angle > M_PI / 2)
    {
        angle = M_PI / 2;
    }
    else if (angle < -M_PI / 2)
    {
        angle = -M_PI / 2;
    }

    if (velocity < 0.5)
    {
        velocity = 0;
    }

    Rotate(angle);
}

void Robot::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point points[] = {rotatedBody.v1, rotatedBody.v2, rotatedBody.v3,
                          rotatedBody.v4, rotatedBody.v1};
    // Draw the rotated rectangle outline
    SDL_RenderDrawLines(renderer, points, 5);

    // TODO Draw the robot's face, and infill the rectangle
}
void Robot::setMove(SDL_Event &e)
{
    if (e.key.keysym.sym == SDLK_SPACE)
    {
        if (moving)
        {
            Stop();
        }
        else
        {
            accelerate();
        }
    }
    if (e.key.keysym.sym == SDLK_UP)
    {
        Forward();
    }
    if (e.key.keysym.sym == SDLK_DOWN)
    {
        Backward();
    }
}
void Robot::Forward()
{
    if (getDirection() == -1)
    {
        isChangingDirection(true);
    }
}
void Robot::Backward()
{
    if (getDirection() == 1)
    {
        isChangingDirection(true);
    }
}
void Robot::accelerate()
{
    set_if_it_is_moving(true);
}
void Robot::Stop()
{
    set_if_it_is_moving(false);
}

void Robot::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;

    body.v1 = {x - ROBOT_SIZE, y - ROBOT_SIZE};
    body.v2 = {x + ROBOT_SIZE, y - ROBOT_SIZE};
    body.v3 = {x + ROBOT_SIZE, y + ROBOT_SIZE};
    body.v4 = {x - ROBOT_SIZE, y + ROBOT_SIZE};
}
void Robot::userSetVelocity(double velocity) { this->velocity = velocity; }

void Robot::setVelocity()
{
    if (changingDirection)
    {
        changeDirection();
    }
    else if (moving)
    {
        if (velocity * velocity < velocityMax * velocityMax)
        {
            velocity = (velocity + acceleration);
        }
    }
    else // Freiando
    {
        if (velocity > 0)
        {
            velocity -= 1;
        }
    }
}

void Robot::set_if_it_is_moving(bool moving) { this->moving = moving; }

void Robot::setAcceleration(double acceleration) { this->acceleration = acceleration; }

void Robot::isChangingDirection(bool changingDirection) { this->changingDirection = changingDirection; }

void Robot::changeDirection()
{
    velocity -= acceleration;
    if (velocity <= 0)
    {
        velocity = 0;
        direction = direction * (-1);
        changingDirection = false;
    }
}

void Robot::SetAngle(double angle) { this->angle = angle; }

double Robot::GetAngle() { return angle; }

double Robot::getAcceleration() { return acceleration; }

int Robot::getDirection() { return direction; }

int Robot::GetX() { return x; }

int Robot::GetY() { return y; }

SDL_Point RotatePoint(SDL_Point point, double angle, SDL_Point pivot)
{
    SDL_Point new_point;
    new_point.x = (point.x - pivot.x) * cos(angle) -
                  (point.y - pivot.y) * sin(angle) + pivot.x;
    new_point.y = (point.x - pivot.x) * sin(angle) +
                  (point.y - pivot.y) * cos(angle) + pivot.y;

    return new_point;
}

void Robot::Rotate(double angle)
{
    rotatedBody.v1 = RotatePoint(body.v1, angle, {x, y});
    rotatedBody.v2 = RotatePoint(body.v2, angle, {x, y});
    rotatedBody.v3 = RotatePoint(body.v3, angle, {x, y});
    rotatedBody.v4 = RotatePoint(body.v4, angle, {x, y});
}