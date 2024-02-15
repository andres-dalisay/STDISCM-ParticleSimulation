#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Wall.cpp"
#include "cmath"

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

	bool isPointBetween(int x1, int y1, int x2, int y2, int x3, int y3) {
		bool xBetween = (x1 <= x2 && x2 <= x3) || (x3 <= x2 && x2 <= x1);
		bool yBetween = (y1 <= y2 && y2 <= y3) || (y3 <= y2 && y2 <= y1);

		return xBetween && yBetween;
	}

	double pointLineDistance(double x, double y, double x1, double y1, double x2, double y2) {
		double A = x - x1;
		double B = y - y1;
		double C = x2 - x1;
		double D = y2 - y1;

		double dot = A * C + B * D;
		double len_sq = C * C + D * D;
		double param = -1;
		if (len_sq != 0) 
			param = dot / len_sq;

		double xx, yy;

		if (param < 0) {
			xx = x1;
			yy = y1;
		}
		else if (param > 1) {
			xx = x2;
			yy = y2;
		}
		else {
			xx = x1 + param * C;
			yy = y1 + param * D;
		}

		double dx = x - xx;
		double dy = y - yy;
		return sqrt(dx * dx + dy * dy);
	}

	
	void checkCollision(std::vector<Wall> walls) {
		if (posX > 1280 || posX < 0)
			particleVector.at(0) = -particleVector.at(0);
		if (posY > 720 || posY < 0)
			particleVector.at(1) = -particleVector.at(1);
		
		for (int i = 0; i < walls.size(); ++i) {
			if (pointLineDistance(posX, posY, walls[i].getX1(), walls[i].getY1(), walls[i].getX2(), walls[i].getY2()) < 5) {
				//account for the particle angle when bouncing
				/*float angle = atan2(particleVector.at(1), particleVector.at(0));
				float wallAngle = atan2(walls[i].getY2() - walls[i].getY1(), walls[i].getX2() - walls[i].getX1());
				float newAngle = 2 * wallAngle - angle;
				particleVector.at(0) = cos(newAngle) * speed;
				particleVector.at(1) = sin(newAngle) * speed;*/


			
				// Calculate the angle of the wall
				float wallAngle = atan2(walls[i].getY2() - walls[i].getY1(), walls[i].getX2() - walls[i].getX1());

				// Calculate the angle of incidence
				float angleOfIncidence = atan2(particleVector[1], particleVector[0]);

				// Calculate the angle between the wall and the particle's velocity vector
				float angleDiff = angleOfIncidence - wallAngle;

				// Calculate the angle of reflection
				float angleOfReflection = angleOfIncidence - 2 * angleDiff;

				// Update the particle's angle and velocity based on the reflection
				particleVector[0] = cos(angleOfReflection) * speed;
				particleVector[1] = sin(angleOfReflection) * speed;

				//std::cout << "Collision with wall " << i << " Particle ID: " << id << std::endl;
			}
		}



		//for (size_t i = 0; i < walls.size(); ++i) {
		//	// Check for collision with each wall
		//	if (posX >= std::min(walls[i].getX1(), walls[i].getX2()) &&
		//		posX <= std::max(walls[i].getX1(), walls[i].getX2()) &&
		//		posY >= std::min(walls[i].getY1(), walls[i].getY2()) &&
		//		posY <= std::max(walls[i].getY1(), walls[i].getY2())) {
		//		particleVector.at(0) = -particleVector.at(0);
		//		particleVector.at(1) = -particleVector.at(1);

		//		std::cout << "Collision with wall " << i << " Particle ID: " << id << std::endl;

		//		break;
		//	}
		//}


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