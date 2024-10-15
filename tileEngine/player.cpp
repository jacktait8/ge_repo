//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::W, //move up
	Keyboard::A, //move left
	Keyboard::S, //move down 
	Keyboard::D //move right
};

void Player::Update(double dt) {
	Vector2f playerMovement(0.f, 0.f);

if (Keyboard::isKeyPressed(controls[0])) {
        // Move up
        playerMovement.y -= _speed * dt;
    }
    if (Keyboard::isKeyPressed(controls[2])) {
        // Move down
        playerMovement.y += _speed * dt;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        // Move left
        playerMovement.x -= _speed * dt;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        // Move right
        playerMovement.x += _speed * dt;
    }

    // Apply the movement to the player's position
    _shape->move(playerMovement);
}

Player::Player()
	: _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Magenta);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
	window.draw(*_shape);
}
