#include "../include/Robot.hpp"

constexpr float DECAY_FACTOR = 0.9f;
constexpr int MOVE_SPEED = 5;
constexpr int ROBOT_SIZE = 20;

Robot::Robot(SDL_Color color, int x, int y)
: velocity(0), angle(0), direction(1) {
    this->x = x;
    this->y = y;

    this->color = color;
    this->body.v1 = {x - ROBOT_SIZE, y - ROBOT_SIZE};
    this->body.v2 = {x + ROBOT_SIZE, y - ROBOT_SIZE};
    this->body.v3 = {x + ROBOT_SIZE, y + ROBOT_SIZE};
    this->body.v4 = {x - ROBOT_SIZE, y + ROBOT_SIZE};
    this->rotatedBody = body;
}

void Robot::Move() {
    int x_v = std::min(static_cast<int>(velocity * cos(angle)), MOVE_SPEED) *
              direction;
    int y_v = std::min(static_cast<int>(velocity * sin(angle)), MOVE_SPEED) *
              direction;

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

    velocity *= DECAY_FACTOR;

    // Clamp angle to -90 to 90 degrees, so the robot can only move forward and
    // backward
    if (angle > M_PI / 2) {
        angle = M_PI / 2;
    } else if (angle < -M_PI / 2) {
        angle = -M_PI / 2;
    }

    if (velocity < 0.5) {
        velocity = 0;
    }

    Rotate(angle);
}

void Robot::Draw(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point points[] = {rotatedBody.v1, rotatedBody.v2, rotatedBody.v3,
                          rotatedBody.v4, rotatedBody.v1};
    // Draw the rotated rectangle outline
    SDL_RenderDrawLines(renderer, points, 5);

    // TODO Draw the robot's face, and infill the rectangle
}

void Robot::Forward() { direction = 1; }

void Robot::Backward() { direction = -1; }

void Robot::Stop() { direction = 0; }

void Robot::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;

    body.v1 = {x - ROBOT_SIZE, y - ROBOT_SIZE};
    body.v2 = {x + ROBOT_SIZE, y - ROBOT_SIZE};
    body.v3 = {x + ROBOT_SIZE, y + ROBOT_SIZE};
    body.v4 = {x - ROBOT_SIZE, y + ROBOT_SIZE};
}

void Robot::SetVelocity(double velocity) { this->velocity = velocity; }

void Robot::SetAngle(double angle) { this->angle = angle; }

double Robot::GetAngle() { return angle; }

int Robot::GetX() { return x; }

int Robot::GetY() { return y; }

SDL_Point RotatePoint(SDL_Point point, double angle, SDL_Point pivot) {
    SDL_Point new_point;
    new_point.x = (point.x - pivot.x) * cos(angle) -
                  (point.y - pivot.y) * sin(angle) + pivot.x;
    new_point.y = (point.x - pivot.x) * sin(angle) +
                  (point.y - pivot.y) * cos(angle) + pivot.y;

    return new_point;
}

void Robot::Rotate(double angle) {
    rotatedBody.v1 = RotatePoint(body.v1, angle, {x, y});
    rotatedBody.v2 = RotatePoint(body.v2, angle, {x, y});
    rotatedBody.v3 = RotatePoint(body.v3, angle, {x, y});
    rotatedBody.v4 = RotatePoint(body.v4, angle, {x, y});
}
