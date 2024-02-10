#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include<chrono>

#include "Particle.cpp"
#include "FPS.cpp"

#define PI 3.14159265358979323846

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Particle Simulator");
	window.setFramerateLimit(60);

	auto lastFPSDrawTime = std::chrono::steady_clock::now();
	const std::chrono::milliseconds interval(500); // 0.5 seconds
	FPS fps;

	sf::Font font;
	if (!font.loadFromFile("OpenSans-VariableFont_wdth,wght.ttf"))
	{
		std::cout << "error";
	}

	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setCharacterSize(100);
	fpsText.setFillColor(sf::Color::Red);
	fpsText.setPosition(100, 100);
	fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);


	//Particle particle(0, 300, 400, 45, 10);
	//sf::CircleShape ball(10);
	//ball.setPosition(particle.getPosX(), particle.getPosY());
	//ball.setPointCount(10);
	//ball.setFillColor(sf::Color::Red);

	std::vector<Particle> particles;
	std::vector<sf::CircleShape> particleShapes;

	for (int i = 0; i < 15000; i++) {
		//push particles with random values
		particles.push_back(Particle(i, rand() % 1280, rand() % 720, rand() % 360, 10));
		particleShapes.push_back(sf::CircleShape(4, 10));
		particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
		particleShapes.at(i).setFillColor(sf::Color::Red);
	}

	// Main loop
	while (window.isOpen())
	{
		auto currentFPSTime = std::chrono::steady_clock::now();
		auto elapsedFPSTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFPSTime - lastFPSDrawTime);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		
		// Update ball position
		for (int i = 0; i < particles.size(); i++) {
			particles[i].updateParticlePosition();
			particles[i].checkCollision();
			//std::cout << particles[i].getPosX() << " " << particles[i].getPosY() << std::endl;
			particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
			//std::cout << particleShapes.at(i).getPosition().x << " " << particleShapes.at(i).getPosition().y << std::endl;
		}



		// Check for collisions with window boundaries
		//if (ball.getPosition().x > window.getSize().x || ball.getPosition().x < 0)
		//	velocityX = -velocityX;
		//if (ball.getPosition().y > window.getSize().y || ball.getPosition().y < 0)
		//	velocityY = -velocityY;

		//if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds()) ||
		//	ball.getGlobalBounds().intersects(rightWall.getGlobalBounds()))
		//	velocityX = -velocityX;

		// Clear the window
		window.clear();


		for (int i = 0; i < particleShapes.size(); i++) {
			window.draw(particleShapes[i]);
		}

		// Draw the ball
		//window.draw(ball);

		//window.draw(leftWall);
		//window.draw(rightWall);

		fps.update();

		if (elapsedFPSTime >= interval) {
			// Update last draw time
			lastFPSDrawTime = currentFPSTime;
			fpsText.setString(std::to_string(fps.getFPS()) + " FPS");
		}
		window.draw(fpsText);
		
		// Display the contents of the window
		window.display();
	}

	return 0;
}
