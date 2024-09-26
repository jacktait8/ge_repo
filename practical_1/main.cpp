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

void Load(){
	//set size and origin of paddles 
	for ( auto &p : paddles) {
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}
	
	//set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius / 2.f , 2.f);
	
	Reset();
	
}

void Reset(){
	//reset paddle position 
	paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f , gameHeight /2.f));
	paddles[1].setPosition(Vector2f(gameWidth - (paddleOffsetWall + paddleSize.x / 2.f) , gameHeight /2.f));
	
	//reset paddle position 
	ball.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));
	
	//reset ball position 
	ballVelocity = { ( isPlayerServing ? initialVelocityX : -initialVelocityX), initialVelocityY };
}

void Update(RenderWindow &window) {
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
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(Vector2f(0.f, direction * paddleSpeed * dt));
	
	ball.move(ballVelocity * dt);
	
	// check ball collision
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	
	if(by > gameHeight ) {
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2(0.f, -10.f));
	} else if( by < 0) {
		ballVelocity.x *= velocityMultiplier;
		ballVelocity.y *= -velocityMultiplier;
		ball.move(Vector2(0.f, 10.f));	
	} else if (bx > gameWidth) {
		// right wall
		Reset();
	} else if (bx < 0) {
		// left wall
		Reset();
	}else if (
		//ball is inline or behind paddle AND
		bx < paddleSize.x + paddleOffsetWall && 
		//ball is below top edge of paddle AND
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)){
		// bounce off left paddle
		ballVelocity.x = -velocityMultiplier;
		ball.move(Vector2(0.f, 10.f));
		
	} else if (		
		//ball is inline or behind paddle AND
		bx < paddleSize.x + paddleOffsetWall && 
		//ball is below top edge of paddle AND
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5)){
		//bounces off right paddle
		ballVelocity.x = -velocityMultiplier;
		ball.move(Vector2(0.f, 10.f));

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