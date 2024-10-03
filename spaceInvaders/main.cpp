#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

//Main.cpp
sf::Texture spritesheet;
sf::Sprite invader;

using namespace std;
using namespace sf;

void Load() {

	if (!spritesheet.loadFromFile("../../../../res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
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
}	
void Render(RenderWindow& window) {
	
	window.draw(invader);
}

int main() {
	RenderWindow window(VideoMode(500, 500), "PONG");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}
	
