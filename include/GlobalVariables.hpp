#pragma once

// Fator de decaimento da velocidade da bola, a cada iteração a velocidade é
// multiplicada por esse fator para simular a perda de energia
constexpr float DECAY_FACTOR = 0.9f;
constexpr int MOVE_SPEED = 5;
constexpr int MS_PER_FRAME = 16; // ~60 FPS
constexpr int ROBOT_SIZE = 20;
constexpr int DISTANCE_TO_CATCH = ROBOT_SIZE * ROBOT_SIZE / 2;
constexpr int SCREEN_HEIGHT = 450;
constexpr int SCREEN_WIDTH = 900;
constexpr int BALL_SPEED = ROBOT_SIZE / 2;
