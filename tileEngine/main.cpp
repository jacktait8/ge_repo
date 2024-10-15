#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <memory> 
#include "entity.h"
#include "player.h"

using namespace std;
using namespace sf;
std::unique_ptr<Player> player = std::make_unique<Player>();


void Update(RenderWindow& window) {
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();

	player->Update(dt);

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

	player->Render(window);
	
}

int main() {
	RenderWindow window(VideoMode(500,500), "THE MAZE");
	//Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}