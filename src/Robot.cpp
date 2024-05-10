#include "../include/Robot.hpp"

using namespace std;

Robot::Robot(SDL_Color color, int x, int y)
    : changingDirection(false),
      moving(false),
      acceleration(0.5),
      angle(0),
      velocity(1),
      velocityMax(5),
      direction(1)
{
    this->x = x;
    this->y = y;

    this->color = color;
    setBodyPosition(x, y);

    this->rotatedBody = body;
}

void Robot::move()
{
    setVelocity();

    int x_v = static_cast<int>(velocity * cos(angle)) * direction * !stopX;

    int y_v = static_cast<int>(velocity * sin(angle)) * direction * !stopY;

    for (int i = 0; i < 4; i++)
    {
        if (body.points[i].x + x_v <= 5)
            x_v = 0;
        if (body.points[i].x + x_v >= SCREEN_WIDTH - 5)
            x_v = 0;
        if (body.points[i].y + y_v <= 5)
            y_v = 0;
        if (body.points[i].y + y_v >= SCREEN_HEIGHT - 5)
            y_v = 0;
    }

    x += x_v;
    y += y_v;

    for (int i = 0; i < 4; i++)
    {
        body.points[i].x += x_v;
        body.points[i].y += y_v;
    }

    rotate(angle);
    stopX = false;
    stopY = false;
}

void Robot::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Color orange = {255, 165, 0, 255};

    SDL_Point points_to_draw[5];

    for (int i = 0; i < 4; i++)
        points_to_draw[i] = rotatedBody.points[i];

    points_to_draw[4] = rotatedBody.points[0];

    SDL_RenderDrawLines(renderer, points_to_draw, 5);

    SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);
    SDL_Point head[2] = {points_to_draw[1], points_to_draw[2]};
    SDL_RenderDrawLines(renderer, head, 2);
}

void Robot::setMove(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            if (moving)
                stop();
            else
                accelerate();
            break;
        case SDLK_UP:
            forward();
            break;
        case SDLK_DOWN:
            backward();
            break;
        case SDLK_LEFT:
            turnLeft();
            break;
        case SDLK_RIGHT:
            turnRight();
            break;
        }
    }
}
void Robot::forward()
{
    if (getDirection() == -1)
    {
        isChangingDirection(true);
    }
}
void Robot::backward()
{
    if (getDirection() == 1)
    {
        isChangingDirection(true);
    }
}
void Robot::accelerate() { set_if_it_is_moving(true); }
void Robot::stop() { set_if_it_is_moving(false); }
void Robot::stopXf() { stopX = true; }
void Robot::stopYf() { stopY = true; }
void Robot::turnRight() { angle += 0.1f; }
void Robot::turnLeft() { angle -= 0.1f; }

void Robot::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;

    setBodyPosition(x, y);
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
    else
    { // freiando
        if (velocity > 0)
        {
            velocity -= 1;
        }
    }
}

void Robot::set_if_it_is_moving(bool moving) { this->moving = moving; }

void Robot::setAcceleration(double acceleration)
{
    this->acceleration = acceleration;
}

void Robot::isChangingDirection(bool changingDirection)
{
    this->changingDirection = changingDirection;
}

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

void Robot::setAngle(double angle) { this->angle = angle; }

double Robot::getAngle() { return angle; }

double Robot::getAcceleration() { return acceleration; }

int Robot::getDirection() { return direction; }

int Robot::getX() { return x; }

int Robot::getY() { return y; }

double Robot::getVelocityX() { return velocity * cos(angle); }

double Robot::getVelocityY() { return velocity * sin(angle); }

RobotBody Robot::getBody() { return rotatedBody; }

void Robot::rotate(double angle)
{
    for (int i = 0; i < 4; i++)
    {
        rotatedBody.points[i] = RotatePoint(body.points[i], angle, {x, y});
    }
}

void Robot::setBodyPosition(int x, int y)
{
    body.points[0] = {x - ROBOT_SIZE, y - ROBOT_SIZE};
    body.points[1] = {x + ROBOT_SIZE, y - ROBOT_SIZE};
    body.points[2] = {x + ROBOT_SIZE, y + ROBOT_SIZE};
    body.points[3] = {x - ROBOT_SIZE, y + ROBOT_SIZE};
}

// move{
//  velocity *= DECAY_FACTOR;

// Clamp angle to -90 to 90 degrees, so the robot can only move forward and
// backward

// if (angle > M_PI / 2)
// {
//     angle = M_PI / 2;
// }
// else if (angle < -M_PI / 2)
// {
//     angle = -M_PI / 2;
// }

// if (velocity < 0.5)
// {
//     velocity = 0;
// }
//}
