#include "../include/Ball.hpp"
// Fator de decaimento da velocidade da bola, a cada iteração a velocidade é
// multiplicada por esse fator para simular a perda de energia
constexpr float DECAY_FACTOR = 0.99f;

// Construtor para definir posição e raio
Ball::Ball(int x, int y, int radius, SDL_Color color)
: _x(x), _y(y), _radius(radius), _color(color), _dx(0), _dy(0) {}

// Função para desenhar a bola no renderizador
void Ball::draw(SDL_Renderer * renderer) {
    // Definir a cor da bola
    SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);

    // Desenhar a bola
    int offsetx, offsety, d;
    offsetx = 0;
    offsety = _radius;
    d = _radius - 1;

    while (offsety >= offsetx) {
        SDL_RenderDrawLine(renderer, _x - offsety, _y + offsetx, _x + offsety,
                           _y + offsetx);
        SDL_RenderDrawLine(renderer, _x - offsetx, _y + offsety, _x + offsetx,
                           _y + offsety);
        SDL_RenderDrawLine(renderer, _x - offsetx, _y - offsety, _x + offsetx,
                           _y - offsety);
        SDL_RenderDrawLine(renderer, _x - offsety, _y - offsetx, _x + offsety,
                           _y - offsetx);

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (_radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

// Função para mover a bola
void Ball::move() {
    if (_y > (SCREEN_HEIGHT - _radius) || _y < (0 + _radius)) _dy *= -1;
    if (_x > (SCREEN_WIDTH - _radius) || _x < (0 + _radius)) _dx *= -1;

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
