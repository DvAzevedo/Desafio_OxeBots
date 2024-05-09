#pragma once

constexpr int SCREEN_WIDTH = 900;
constexpr int SCREEN_HEIGHT = 450;
constexpr int MS_PER_FRAME = 16; // ~60 FPS

struct Vector2D
{
    double x;
    double y;

    // Construtor que aceita dois inteiros como argumentos
    Vector2D(double xCoord = 0.0, double yCoord = 0.0) : x(xCoord), y(yCoord) {}
};