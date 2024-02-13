#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Wall.cpp"

#define PI 3.14159265358979323846

class Particle {
public:
	Particle(int id, float posX, float posY, float  angleDeg, float speed) {
		// convert to radians
		this->particleVector = { 0, 0 };
		this->id = id;
		this->angle = angleDeg * PI / 180;
		this->speed = speed;
		this->posX = posX;
		this->posY = posY;
		//std::cout << "ID: " << this->id << " | speed: " << this->speed << std::endl;

		setParticleVector();
	}

private:
	std::vector<float> particleVector;
	float angle;
	float speed;
	float posX;
	float posY;
	int id;

public:

	void setParticleVector() {
		particleVector[0] = this->speed * cos(this->angle);
		particleVector[1] = this->speed * sin(this->angle);
	}

	void updateParticlePosition() {
		posX += particleVector[0];
		posY += particleVector[1];
	}

	
	void checkCollision(std::vector<Wall>& walls) {
		if (posX > 1280 || posX < 0)
			particleVector.at(0) = -particleVector.at(0);
		if (posY > 720 || posY < 0)
			particleVector.at(1) = -particleVector.at(1);
		
		// check if particle is colliding with any walls
		for (int i = 0; i < walls.size(); i++) {
			// TODO: fix this
		}

		//if (posX > walls.at(i).getX2() && posX < walls.at(i).getX1() &&
		//	posY > walls.at(i).getY2() && posY < walls.at(i).getY1()) {
		//	// if particle is colliding with wall, reverse the velocity
		//	particleVector.at(0) = -particleVector.at(0);
		//	particleVector.at(1) = -particleVector.at(1);
		//}


		//if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds()) ||
		//	ball.getGlobalBounds().intersects(rightWall.getGlobalBounds()))
		//	velocityX = -velocityX;
		
	}

	float getPosX() {
		return posX;
	}

	float getPosY() {
		return posY;
	}
};