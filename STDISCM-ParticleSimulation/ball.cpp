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

private:
	sf::CircleShape ball;
	std::vector<float> ballVector;
	float angle;
	float speed;

public:

	void updateBallVector(){
		float deg = 45.0f;
		angle = deg * PI / 180;
		speed = 10.0f;

		ballVector[0] = speed * cos(angle);
		ballVector[1] = speed * sin(angle);

	}

	void checkCollision(){
		if (ball.getPosition.x > 1080 || ballVector.at(0) < 0)
			ballVector.at(0) = -ballVector.at(0);
		if (ballVector.at(1) > 720 || ballVector.at(1) < 0)
			ballVector.at(1) = -ballVector.at(1);
	}
	
};