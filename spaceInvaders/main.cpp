#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "ship.h"
#include "game.h"

//Main.cpp
std::vector<Ship*> ships;
sf::Texture spritesheet;
sf::Sprite invader;

using namespace std;
using namespace sf;

Player1 player;

void Load() {

	if (!spritesheet.loadFromFile("../../../../res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
	player.setTexture(spritesheet);
	player.setTextureRect(IntRect(Vector2i(160, 30), Vector2i(32, 32)));
	Invader::speed = 30.f;
	Invader::direction = true;
	Bullet::Init();

	int invaders_rows = 5;
	int invaders_columns = 12;
	float xposition = 50;
	float yposition = 25;
		

	for (int r = 0; r < invaders_rows; ++r) {
		auto rect = IntRect(Vector2(0, 0), Vector2(32, 32));
		for (int c = 0; c < invaders_columns; ++c) {
			Vector2f position = { xposition, yposition };
			auto inv = new Invader(rect, position);
			xposition = xposition + 50;
			ships.push_back(inv);
			
		}
		yposition = yposition + 50;
		xposition = 50;
	}
	//Invader* inv = new Invader(sf::IntRect(Vector2(30, 0), Vector2(32, 32)), { 100,100 });
	//ships.push_back(inv);
}

void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	// check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	//update ships
	for (auto& s : ships) {
		s->Update(dt);
	};

	player.Update(dt);
	float playerPosition = player.getPosition().x;
	if (playerPosition + (32 * 0.5) > gameWidth) {
		player.move(Vector2f(-10.f, 0.f));
	}
	else if (playerPosition + (32 * 0.5) < 0) {
		player.move(Vector2f(10.f, 0.f));
	}
	// Update bullets
	Bullet::Update(dt);


}	
void Render(RenderWindow& window) {
	for (const auto s : ships) {
		window.draw(*s);
	}
	window.draw(player);
	Bullet::Render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "SPACE INVADERS");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
	
