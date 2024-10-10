#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A, //player1 up
	Keyboard::Z, //player 1 down 
	Keyboard::Up,
	Keyboard::Down
};
Vector2f ballVelocity;
bool isPlayerServing = false;
const float velocityMultiplier = 1.1f;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;

CircleShape ball;
RectangleShape paddles[2];

void Reset(int num) {
	//reset paddle position 
	paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
	paddles[1].setPosition(Vector2f(gameWidth - (paddleOffsetWall + paddleSize.x / 2.f), gameHeight / 2.f));

	//reset paddle position 
	ball.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));

	//reset ball position 
	if (num == gameWidth) {
		ballVelocity = { (isPlayerServing ? -initialVelocityX : initialVelocityX), initialVelocityY };
	} else if (num == 0) {
		ballVelocity = { (isPlayerServing ? initialVelocityX : -initialVelocityX), initialVelocityY };

	}
}

void Load() {
	//set size and origin of paddles 
	for (auto& p : paddles) {
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}

	//set size and origin of ball
	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius / 2.f, 2.f);

	Reset(gameWidth);
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

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	// handle paddle movement
	float player1Direction = 0.0f;
	float player2Direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		player1Direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) {
		player1Direction++;
	}
	//if (Keyboard::isKeyPressed(controls[2])) {
	//	player2Direction--;
	//}
	//if (Keyboard::isKeyPressed(controls[3])) {
	//	player2Direction++;
	//}
	paddles[0].move(Vector2f(0.f, player1Direction * paddleSpeed * dt));
	//paddles[1].move(Vector2f(0.f, player2Direction * paddleSpeed * dt));

	

	ball.move(ballVelocity * dt);
	//check player collision 
	const float paddle0y = paddles[0].getPosition().y;
	const float paddle1y = paddles[1].getPosition().y;
	const float ballY = ball.getPosition().y;

	if (paddle1y > ballY + paddleSize.y / 4.f) {
		paddles[1].move(Vector2f(0.f, -150 * dt));
	}
	if (paddle1y < ballY - paddleSize.y / 4.f) {
		paddles[1].move(Vector2f(0.f, 150 * dt));
	}
	

	//prevent baddles from going out of bounds
	if (paddle0y + (paddleSize.y * 0.5) > gameHeight) {
		paddles[0].move(Vector2f(0.f, -10.f));
	}
	else if (paddle0y - (paddleSize.y * 0.5) < 0) {
		paddles[0].move(Vector2f(0.f, 10.f));
	}

	if (paddle1y + (paddleSize.y * 0.5) > gameHeight) {
		paddles[1].move(Vector2f(0.f, -10.f));
	}
	else if (paddle1y - (paddleSize.y * 0.5) < 0) {
		paddles[1].move(Vector2f(0.f, 10.f));
	}

	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;

	
	if(by > gameHeight ) {
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2f(0.f, -10.f));
	} else if( by < 0) {
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2f(0.f, 10.f));	

	} else if (bx > gameWidth) {
		// right wall
		Reset(gameWidth);
	} else if (bx < 0) {
		// left wall
		Reset(0);
	}else if (

		//ball is inline or behind paddle AND
		bx < paddleSize.x + paddleOffsetWall && 
		//ball is below top edge of paddle AND
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
		// bounce off LEFT paddle
		ballVelocity.x = -ballVelocity.x;
		ballVelocity.x *= velocityMultiplier;
		ball.move(Vector2f(0.f, 10.f));
		
	} else if (		
		//ball is inline or behind paddle AND
		bx > gameWidth - (paddleSize.x + paddleOffsetWall) &&
		//ball is below top edge of paddle AND
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
	{
		//bounces off RIGHT paddle
		ballVelocity.x = -ballVelocity.x;
		ballVelocity.x *= velocityMultiplier;
		ball.move(Vector2f(0.f, 10.f));

	}
}


void Render(RenderWindow &window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}