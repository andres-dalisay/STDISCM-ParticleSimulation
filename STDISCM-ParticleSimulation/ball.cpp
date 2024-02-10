#include <vector>
#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846

class Ball {
public:
	Ball() {
		ball = sf::CircleShape(10);
		ballVector = { 0, 0 };
		angle = 0;
		speed = 0;
	}

	Ball(float x, float y, float angle, float speed) {
		ball = sf::CircleShape(10);
		ball.setPosition(x, y);

		updateBallVector(angle, speed);

		angle = angle;
		speed = speed;
	}

private:
	sf::CircleShape ball;
	std::vector<float> ballVector;
	float angle;
	float speed;

public:

	void drawBall(sf::RenderWindow& window) {
		window.draw(ball);
	}

	void updateBallVector(float deg, float speed){
		float angleNew = deg * PI / 180;
		speed = speed;

		ballVector = { speed * cos(angleNew) , speed * sin(angleNew) };

		//ballVector.at(0) = (speed * cos(angleNew));
		//ballVector.at(1) = (speed * sin(angleNew));

	}

	void moveBall() {
		ball.move(ballVector.at(0), ballVector.at(1));
	}

	void checkCollision(sf::RenderWindow& window){
		if (ball.getPosition().x > window.getSize().x || ball.getPosition().x < 0)
			ballVector.at(0) = -ballVector.at(0);
		if (ball.getPosition().y > window.getSize().y || ball.getPosition().y < 0)
			ballVector.at(1) = -ballVector.at(1);
	}
	
};