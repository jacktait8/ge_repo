//bullet.cpp
#include "bullet.h"
#include "game.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Bullet Bullet::bullets[256];
unsigned char Bullet::bulletPointer = 0;

void Bullet::Update(const float& dt)
{
	for (unsigned char i = 0; i < bulletPointer; i++) {
		bullets[i]._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow& window)
{
	for (unsigned char i = 0; i < bulletPointer; i++) {
		window.draw(bullets[i]);
	}
}
void Bullet::Fire(const sf::Vector2f& pos, const bool mode)
{
	Bullet& bullet = bullets[bulletPointer];

	bullet.setPosition(pos);
	bullet._mode = mode;
	bulletPointer = (bulletPointer + 1) % 256; // Move to the next bullet
}

void Bullet::Init()
{
	spritesheet.loadFromFile("../../../../res/img/invaders_sheet.png");
	for (auto& bullet : bullets) {
		bullet.setTexture(spritesheet);
		bullet.setPosition(-100,-100);
		bullet.setTextureRect(IntRect(Vector2i(64, 32), Vector2i(32, 32)));
	}
}
Bullet::Bullet()
	: _mode(false) // Default to false for player bullets
{
	setPosition(Vector2f(0, 0)); // Set default position to (0, 0)
}
void Bullet::_Update(const float& dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//off screen - do nothing
		return;
	}
	else {
		move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
		const FloatRect boundingBox = getGlobalBounds();
	}
}
