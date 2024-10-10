//ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[3] = {
    Keyboard::A, //left
    Keyboard::D, //right
    Keyboard::W // shoot
};
const float paddleSpeed = 200.f;


Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

//ship.cpp
Invader::Invader() : Ship() {}
bool Invader::direction;
float Invader::speed;


Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(Vector2f(16.f, 16.f));;
    setPosition(pos);
}

void Invader::Update(const float& dt) {
    Ship::Update(dt);

    move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (int i = 0; i < ships.size(); ++i) {
            ships[i]->move(Vector2f(0.0f, 24.0f));
        }
    }
    std::cout << "New Position: " << getPosition().x << std::endl;
}

Player::Player() : Ship(IntRect(Vector2(160, 32), Vector2(32, 32))) {
    setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt){
    Ship::Update(dt);

    float player1Direction = 0.0f;

    if (Keyboard::isKeyPressed(controls[0])) {
        player1Direction--;
        Vector2f right(player1Direction * paddleSpeed * dt, 0.f);
        move(right);
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        player1Direction++;
        Vector2f left(player1Direction * paddleSpeed * dt, 0.f);
        move(left);
    }
    //fire bullet
    if (Keyboard::isKeyPressed(controls[2])) {
        Bullet::Fire(getPosition(), false);
    }
    

    if (Keyboard::isKeyPressed(controls[2])) {
        Bullet::Update(dt);
    }
    for (const auto s : bullets) {
        s->Update(dt);
    }
}