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

#define PI 3.14159265358979323846

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Particle Simulator");

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
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

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

		// Display the contents of the window
		window.display();
	}

	return 0;
}
