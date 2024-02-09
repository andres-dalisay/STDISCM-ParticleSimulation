//#include <SFML/Graphics.hpp>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(1280, 720), "Particle Simulator");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}


#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include<chrono>

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


	auto lastDrawTime = std::chrono::steady_clock::now();
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
	sf::CircleShape ball(10);
	ball.setFillColor(sf::Color::Red);
	ball.setPointCount(10);
	ball.setPosition(300, 400); // Start position of the ball

	// set angle from 0 to 360 degrees
	float deg = 45.0f;

	// convert angle to radians
	float angle = deg * PI / 180;

	// set the speed of the ball
	float speed = 1.0f;
	
	// set the velocity of the ball based on angle and speed
	float velocityX = speed * cos(angle);
	float velocityY = speed * sin(angle);

	std::cout << "velocityX: " << velocityX;
	std::cout << "velocityY: " << velocityY;

	// Main loop
	while (window.isOpen())
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastDrawTime);

	
	// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// window.draw, etc.
		

		
		// Update ball position
		ball.move(velocityX, velocityY);

		// Check for collisions with window boundaries
		if (ball.getPosition().x > window.getSize().x || ball.getPosition().x < 0)
			velocityX = -velocityX;
		if (ball.getPosition().y > window.getSize().y || ball.getPosition().y < 0)
			velocityY = -velocityY;

		// Clear the window
		window.clear();

		// Draw the ball
		window.draw(ball);



		fps.update();
		/*fpsText = std::to_string(fps.getFPS());*/

		

		if (elapsedTime >= interval) {
			// Update last draw time
			lastDrawTime = currentTime;
			fpsText.setString(std::to_string(fps.getFPS()));
		}
		window.draw(fpsText);
		
		// Display the contents of the window
		window.display();
	}

	return 0;
}
