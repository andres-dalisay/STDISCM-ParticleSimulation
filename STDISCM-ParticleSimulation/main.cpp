#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "FPS.cpp"


void drawInputWindow(sf::RenderWindow& window, sf::Font& font)
{
    // Create input boxes in the new window
	sf::RectangleShape inputBoxParticles(sf::Vector2f(50, 20));
    inputBoxParticles.setFillColor(sf::Color::White);
    inputBoxParticles.setOutlineThickness(2);
    inputBoxParticles.setOutlineColor(sf::Color::Black);
    inputBoxParticles.setPosition(150, 50);

	sf::Text textNoOfParticles;
	textNoOfParticles.setFont(font);
	textNoOfParticles.setCharacterSize(15);
	textNoOfParticles.setFillColor(sf::Color::Black);
	textNoOfParticles.setString("No. of Particles");
	textNoOfParticles.setPosition(10, 50);

    sf::RectangleShape inputBoxParticleStart(sf::Vector2f(50, 20));
    inputBoxParticleStart.setFillColor(sf::Color::White);
    inputBoxParticleStart.setOutlineThickness(2);
    inputBoxParticleStart.setOutlineColor(sf::Color::Black);
    inputBoxParticleStart.setPosition(150, 100);

    sf::Text textParticleStart;
    textParticleStart.setFont(font);
    textParticleStart.setCharacterSize(15);
    textParticleStart.setFillColor(sf::Color::Black);
    textParticleStart.setString("Start Point");
    textParticleStart.setPosition(10, 100);

    sf::RectangleShape inputBoxParticleEnd(sf::Vector2f(50, 20));
    inputBoxParticleEnd.setFillColor(sf::Color::White);
    inputBoxParticleEnd.setOutlineThickness(2);
    inputBoxParticleEnd.setOutlineColor(sf::Color::Black);
    inputBoxParticleEnd.setPosition(150, 120);

    sf::Text textParticleEnd;
    textParticleEnd.setFont(font);
    textParticleEnd.setCharacterSize(15);
    textParticleEnd.setFillColor(sf::Color::Black);
    textParticleEnd.setString("End Point");
    textParticleEnd.setPosition(10, 120);

    sf::RectangleShape inputBoxParticleVelocity(sf::Vector2f(50, 20));
    inputBoxParticleVelocity.setFillColor(sf::Color::White);
    inputBoxParticleVelocity.setOutlineThickness(2);
    inputBoxParticleVelocity.setOutlineColor(sf::Color::Black);
    inputBoxParticleVelocity.setPosition(150, 140);

    sf::Text textParticleVelocity;
    textParticleVelocity.setFont(font);
    textParticleVelocity.setCharacterSize(15);
    textParticleVelocity.setFillColor(sf::Color::Black);
    textParticleVelocity.setString("Velocity");
    textParticleVelocity.setPosition(10, 140);

    sf::RectangleShape inputBoxParticleAngle(sf::Vector2f(50, 20));
    inputBoxParticleAngle.setFillColor(sf::Color::White);
    inputBoxParticleAngle.setOutlineThickness(2);
    inputBoxParticleAngle.setOutlineColor(sf::Color::Black);
    inputBoxParticleAngle.setPosition(150, 160);

    sf::Text textParticleAngle;
    textParticleAngle.setFont(font);
    textParticleAngle.setCharacterSize(15);
    textParticleAngle.setFillColor(sf::Color::Black);
    textParticleAngle.setString("Angle");
    textParticleAngle.setPosition(10, 160);

    sf::RectangleShape button1(sf::Vector2f(190, 25));
    button1.setFillColor(sf::Color::White);
    button1.setOutlineThickness(2);
    button1.setOutlineColor(sf::Color::Black);
    button1.setPosition(10, 210);

    sf::Text button1Text;
    button1Text.setFont(font);
    button1Text.setCharacterSize(20);
    button1Text.setFillColor(sf::Color::Black);
    button1Text.setString("Insert Case 1");

    // Center the position of text within the button
    sf::FloatRect textBounds = button1Text.getLocalBounds();
    button1Text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    button1Text.setPosition(button1.getPosition().x + button1.getSize().x / 2.0f, button1.getPosition().y + button1.getSize().y / 2.0f);


    while (window.isOpen())
    {
		sf::Event inputEvent;
        while (window.pollEvent(inputEvent))
        {
			if (inputEvent.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		// Draw input boxes here
		window.draw(inputBoxParticles);
		window.draw(textNoOfParticles);
        window.draw(inputBoxParticleStart);
        window.draw(textParticleStart);
        window.draw(inputBoxParticleEnd);
        window.draw(textParticleEnd);
        window.draw(inputBoxParticleVelocity);
        window.draw(textParticleVelocity);
        window.draw(inputBoxParticleAngle);
        window.draw(textParticleAngle);
        window.draw(button1);
        window.draw(button1Text);



		window.display();
	}


}

int main()
{
    // Create the main window
    sf::RenderWindow mainWindow(sf::VideoMode(1280, 720), "Particle Simulator");
    mainWindow.setFramerateLimit(60);

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
    fpsText.setCharacterSize(30);
    fpsText.setFillColor(sf::Color::Red);
    fpsText.setPosition(1150, 680);
    fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Create button for input window
    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setFillColor(sf::Color::Green);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::White);
    button.setPosition(10, 10);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setString("Balls");

    // Center the position of text within the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(button.getPosition().x + button.getSize().x / 2.0f, button.getPosition().y + button.getSize().y / 2.0f);


    // Main loop
    while (mainWindow.isOpen())
    {
        auto currentFPSTime = std::chrono::steady_clock::now();
        auto elapsedFPSTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFPSTime - lastFPSDrawTime);

        // Process events
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();

            // Check for button click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(mainWindow);
                    if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
                    {
                        // Open new window with input boxes
                        sf::RenderWindow inputWindow(sf::VideoMode(300, 700), "Input Window", sf::Style::Titlebar | sf::Style::Close);
                        inputWindow.setFramerateLimit(60);

                        drawInputWindow(inputWindow, font);
                    }
                }
            }
        }

        // Clear the main window
        mainWindow.clear(sf::Color::Black);

        // Draw button
        mainWindow.draw(button);
        mainWindow.draw(buttonText);

        fps.update();

        if (elapsedFPSTime >= interval)
        {
            // Update last draw time
            lastFPSDrawTime = currentFPSTime;
            fpsText.setString(std::to_string(fps.getFPS()) + " FPS");
        }
        mainWindow.draw(fpsText);

        // Display the contents of the main window
        mainWindow.display();
    }

    return 0;
}
