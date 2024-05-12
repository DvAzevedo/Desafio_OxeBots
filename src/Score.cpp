#include "../include/Score.hpp"
using namespace std;

Score::Score(Ball & ball, std::vector<Robot *> const robots)
: ball(ball), robots(robots), scoreRobot1(0), scoreRobot2(0)
{
}

void Score::reset()
{
    for (auto robot : robots) robot->reset();
    ball.reset();
};

void Score::updateScore()
{
    if (ball.getX() > (2 * SIDE_MARGIN + FIELD_WIDTH - 2 * ball.getRadius()))
        if ((ball.getY() > TOP_MARGIN + 3 * FIELD_HEIGHT / 8) &&
            (ball.getY() < TOP_MARGIN + 5 * FIELD_HEIGHT / 8))
        {
            cout << "Gol Robo 1\n";
            scoreRobot1++;
            cout << scoreRobot1 << " x " << scoreRobot2 << endl;
            reset();
        }
    if (ball.getX() < (2 * ball.getRadius()))
        if ((ball.getY() > TOP_MARGIN + 3 * FIELD_HEIGHT / 8) &&
            (ball.getY() < TOP_MARGIN + 5 * FIELD_HEIGHT / 8))
        {
            cout << "Gol Robo 2\n";
            scoreRobot2++;
            cout << scoreRobot1 << " x " << scoreRobot2 << endl;
            reset();
        }
};

int Score::getScoreRobot1() { return scoreRobot1; }
int Score::getScoreRobot2() { return scoreRobot2; }
