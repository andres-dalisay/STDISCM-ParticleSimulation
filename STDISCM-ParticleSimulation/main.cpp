#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include<chrono>

#include "ball.cpp"

#define PI 3.14159265358979323846

class FPS
{
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {}

	/// @brief Update the frame count.
	/// 


	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if (mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}
};

int main()
{

	// Create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Particle Simulator");
	window.setFramerateLimit(60);

	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;


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

	//// Create the ball shape
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

	// Create the ball shape
	Ball ball(50,50,180,10);


	// Create the walls
	sf::RectangleShape leftWall(sf::Vector2f(10.f, 600.f));
	leftWall.setPosition(0.f, 0.f);
	leftWall.setFillColor(sf::Color::Green);

	sf::RectangleShape rightWall(sf::Vector2f(10.f, 600.f));
	rightWall.setPosition(790.f, 0.f);
	rightWall.setFillColor(sf::Color::Green);


	// Main loop
	while (window.isOpen())
	{
		auto currentFPSTime = std::chrono::steady_clock::now();
		auto elapsedFPSTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFPSTime - lastFPSDrawTime);

	
	// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// window.draw, etc.
		

		
		// Update ball position
		ball.moveBall();
		ball.checkCollision(window);

		// Check for collisions with window boundaries
		/*if (ball.getPosition().x > window.getSize().x || ball.getPosition().x < 0)
			velocityX = -velocityX;
		if (ball.getPosition().y > window.getSize().y || ball.getPosition().y < 0)
			velocityY = -velocityY;*/

		/*if (ball.getGlobalBounds().intersects(leftWall.getGlobalBounds()) ||
			ball.getGlobalBounds().intersects(rightWall.getGlobalBounds()))
			velocityX = -velocityX;*/

		// Clear the window
		window.clear();

		// Draw the ball
		//window.draw(ball);
		ball.drawBall(window);

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
