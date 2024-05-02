#include "../include/Ball.hpp"

// Fator de decaimento da velocidade da bola, a cada iteração a velocidade é
// multiplicada por esse fator para simular a perda de energia
constexpr float DECAY_FACTOR = 0.9f;

// Construtor para definir posição e raio
Ball::Ball(int x, int y, int radius, SDL_Color color)
: _x(x), _y(y), _radius(radius), _color(color), _dx(0), _dy(0) {}

// Função para desenhar a bola no renderizador
void Ball::draw(SDL_Renderer * renderer) {
    // Definir a cor da bola
    SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);

    // Desenhar a bola
    for (int dy = -_radius; dy <= _radius; dy++) {
        for (int dx = -_radius; dx <= _radius; dx++) {
            if (dx * dx + dy * dy <= _radius * _radius) {
                SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b,
                                       _color.a);
                SDL_RenderDrawPoint(renderer, _x + dx, _y + dy);
            }
        }
    }
}

// Função para mover a bola
void Ball::move() {
    _x += static_cast<int>(_dx);
    _y += static_cast<int>(_dy);

    _dx = _dx * DECAY_FACTOR;
    _dy = _dy * DECAY_FACTOR;
}

// Função para definir a velocidade da bola
void Ball::setSpeed(int dx, int dy) {
    _dx = dx;
    _dy = dy;
}

// Função para definir a cor da bola
void Ball::setColor(SDL_Color color) { _color = color; }

// Função para obter a posição x da bola
int Ball::getX() { return _x; }

// Função para obter a posição y da bola
int Ball::getY() { return _y; }

// Função para obter o raio da bola
int Ball::getRadius() { return _radius; }

// Função para inverter a direção da bola
void Ball::invertX() { _dx = -_dx; }

void Ball::invertY() { _dy = -_dy; }