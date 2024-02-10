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

	// Create the ball shape
	//sf::CircleShape ball(10);
	//ball.setFillColor(sf::Color::Red);
	//ball.setPointCount(10);
	//ball.setPosition(300, 400); // Start position of the ball

	//// set angle from 0 to 360 degrees
	//float deg = 45.0f;

	//// convert angle to radians
	//float angle = deg * PI / 180;

	//// set the speed of the ball
	//float speed = 10.0f;
	//
	//// set the velocity of the ball based on angle and speed
	//float velocityX = speed * cos(angle);
	//float velocityY = speed * sin(angle);

	//std::cout << "velocityX: " << velocityX;
	//std::cout << "velocityY: " << velocityY;

	// Create the walls
	//sf::RectangleShape leftWall(sf::Vector2f(10.f, 600.f));
	//leftWall.setPosition(0.f, 0.f);
	//leftWall.setFillColor(sf::Color::Green);

	//sf::RectangleShape rightWall(sf::Vector2f(10.f, 600.f));
	//rightWall.setPosition(790.f, 0.f);
	//rightWall.setFillColor(sf::Color::Green);

	Particle particle(0, 300, 400, 45, 10);
	sf::CircleShape ball(10);
	ball.setPosition(particle.getPosX(), particle.getPosY());
	ball.setPointCount(10);
	ball.setFillColor(sf::Color::Red);


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
		particle.updateParticlePosition();
		particle.checkCollision();
		ball.setPosition(particle.getPosX(), particle.getPosY());

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

		// Draw the ball
		window.draw(ball);

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
