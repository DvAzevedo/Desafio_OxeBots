#include "../include/Robot.hpp"

using namespace std;

constexpr float DECAY_FACTOR = 0.9f;
constexpr int MOVE_SPEED = 5;
constexpr int ROBOT_SIZE = 20;

Robot::Robot(SDL_Color color, int x, int y)
: velocity(1),
  velocityMax(5),
  acceleration(0.5),
  moving(false),
  angle(0),
  direction(1),
  changingDirection(false) {
    this->x = x;
    this->y = y;

    this->color = color;
    SetBodyPosition(x, y);

    this->rotatedBody = body;
}

void Robot::Move() {
    setVelocity();

    int x_v = static_cast<int>(velocity * cos(angle)) * direction;

    int y_v = static_cast<int>(velocity * sin(angle)) * direction;

    for (int i = 0; i < 4; i++) {
        if (body.points[i].x + x_v <= 5) x_v = 0;
        if (body.points[i].x + x_v >= SCREEN_WIDTH - 5) x_v = 0;
        if (body.points[i].y + y_v <= 5) y_v = 0;
        if (body.points[i].y + y_v >= SCREEN_HEIGHT - 5) y_v = 0;
    }

    x += x_v;
    y += y_v;

    for (int i = 0; i < 4; i++) {
        body.points[i].x += x_v;
        body.points[i].y += y_v;
    }

    Rotate(angle);
}

void Robot::Draw(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_Point points_to_draw[5];

    for (int i = 0; i < 4; i++) {
        points_to_draw[i] = rotatedBody.points[i];
    }
    points_to_draw[4] = rotatedBody.points[0];

    SDL_RenderDrawLines(renderer, points_to_draw, 5);
    // TODO Draw the robot's face, and infill the rectangle
}

void Robot::setMove(SDL_Event & e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_SPACE:
                if (moving)
                    Stop();
                else
                    accelerate();
                break;
            case SDLK_UP:
                Forward();
                break;
            case SDLK_DOWN:
                Backward();
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
void Robot::Forward() {
    if (getDirection() == -1) {
        isChangingDirection(true);
    }
}
void Robot::Backward() {
    if (getDirection() == 1) {
        isChangingDirection(true);
    }
}
void Robot::accelerate() { set_if_it_is_moving(true); }
void Robot::Stop() { set_if_it_is_moving(false); }
void Robot::turnRight() { angle += 0.1f; }
void Robot::turnLeft() { angle -= 0.1f; }

void Robot::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;

    SetBodyPosition(x, y);
}
void Robot::userSetVelocity(double velocity) { this->velocity = velocity; }

void Robot::setVelocity() {
    if (changingDirection) {
        changeDirection();
    } else if (moving) {
        if (velocity * velocity < velocityMax * velocityMax) {
            velocity = (velocity + acceleration);
        }
    } else {  // freiando
        if (velocity > 0) {
            velocity -= 1;
        }
    }
}

void Robot::set_if_it_is_moving(bool moving) { this->moving = moving; }

void Robot::setAcceleration(double acceleration) {
    this->acceleration = acceleration;
}

void Robot::isChangingDirection(bool changingDirection) {
    this->changingDirection = changingDirection;
}

void Robot::changeDirection() {
    velocity -= acceleration;
    if (velocity <= 0) {
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

SDL_Point RotatePoint(SDL_Point point, double angle, SDL_Point pivot) {
    SDL_Point new_point;
    new_point.x = (point.x - pivot.x) * cos(angle) -
                  (point.y - pivot.y) * sin(angle) + pivot.x;
    new_point.y = (point.x - pivot.x) * sin(angle) +
                  (point.y - pivot.y) * cos(angle) + pivot.y;

    return new_point;
}

void Robot::Rotate(double angle) {
    for (int i = 0; i < 4; i++) {
        rotatedBody.points[i] = RotatePoint(body.points[i], angle, {x, y});
    }
}

void Robot::SetBodyPosition(int x, int y) {
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
