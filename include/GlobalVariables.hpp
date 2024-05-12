#ifndef GlobalVariables_HPP
#define GlobalVariables_HPP

// Fator de decaimento da velocidade da bola, a cada iteração a velocidade é
// multiplicada por esse fator para simular a perda de energia
constexpr float DECAY_FACTOR = 0.98f;
constexpr int MOVE_SPEED = 5;
constexpr int MS_PER_FRAME = 16;  // ~60 FPS
constexpr int ROBOT_SIZE = 20;
constexpr int DISTANCE_TO_CATCH = ROBOT_SIZE * ROBOT_SIZE;
constexpr int SCREEN_HEIGHT = 500;
constexpr int SCREEN_WIDTH = 960;
constexpr int FIELD_HEIGHT = 450;
constexpr int FIELD_WIDTH = 900;
constexpr int TOP_MARGIN = SCREEN_HEIGHT - FIELD_HEIGHT;
constexpr int SIDE_MARGIN = (SCREEN_WIDTH - FIELD_WIDTH) / 2;
constexpr int BALL_SPEED = ROBOT_SIZE / 2;

#endif  // GlobalVariables_HPP
