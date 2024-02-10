#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "FPS.cpp"


void drawInputWindow(sf::RenderWindow& window, sf::Font& font)
{
   
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

    //CASE 1

    sf::RectangleShape inputBoxParticleStart(sf::Vector2f(50, 20));
    inputBoxParticleStart.setFillColor(sf::Color::White);
    inputBoxParticleStart.setOutlineThickness(2);
    inputBoxParticleStart.setOutlineColor(sf::Color::Black);
    inputBoxParticleStart.setPosition(150, 100);

    sf::Text textParticleStart;
    textParticleStart.setFont(font);
    textParticleStart.setCharacterSize(15);
    textParticleStart.setFillColor(sf::Color::Black);
    textParticleStart.setString("Start X Point");
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
    textParticleEnd.setString("End X Point");
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
    button1.setPosition(10, 200);

    sf::Text button1Text;
    button1Text.setFont(font);
    button1Text.setCharacterSize(20);
    button1Text.setFillColor(sf::Color::Black);
    button1Text.setString("Insert Case 1");

    sf::FloatRect textBounds = button1Text.getLocalBounds();
    button1Text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    button1Text.setPosition(button1.getPosition().x + button1.getSize().x / 2.0f, button1.getPosition().y + button1.getSize().y / 2.0f);

    //CASE 2

    sf::RectangleShape inputBoxParticleStart2x(sf::Vector2f(25, 20));
    inputBoxParticleStart2x.setFillColor(sf::Color::White);
    inputBoxParticleStart2x.setOutlineThickness(2);
    inputBoxParticleStart2x.setOutlineColor(sf::Color::Black);
    inputBoxParticleStart2x.setPosition(150, 250);

    sf::RectangleShape inputBoxParticleStart2y(sf::Vector2f(25, 20));
    inputBoxParticleStart2y.setFillColor(sf::Color::White);
    inputBoxParticleStart2y.setOutlineThickness(2);
    inputBoxParticleStart2y.setOutlineColor(sf::Color::Black);
    inputBoxParticleStart2y.setPosition(175, 250);

    sf::Text textParticleStart2;
    textParticleStart2.setFont(font);
    textParticleStart2.setCharacterSize(15);
    textParticleStart2.setFillColor(sf::Color::Black);
    textParticleStart2.setString("Start Point");
    textParticleStart2.setPosition(10, 250);

    sf::RectangleShape inputBoxParticleVelocity2(sf::Vector2f(50, 20));
    inputBoxParticleVelocity2.setFillColor(sf::Color::White);
    inputBoxParticleVelocity2.setOutlineThickness(2);
    inputBoxParticleVelocity2.setOutlineColor(sf::Color::Black);
    inputBoxParticleVelocity2.setPosition(150, 270);

    sf::Text textParticleVelocity2;
    textParticleVelocity2.setFont(font);
    textParticleVelocity2.setCharacterSize(15);
    textParticleVelocity2.setFillColor(sf::Color::Black);
    textParticleVelocity2.setString("Velocity");
    textParticleVelocity2.setPosition(10, 270);

    sf::RectangleShape inputBoxParticleAngleStart(sf::Vector2f(50, 20));
    inputBoxParticleAngleStart.setFillColor(sf::Color::White);
    inputBoxParticleAngleStart.setOutlineThickness(2);
    inputBoxParticleAngleStart.setOutlineColor(sf::Color::Black);
    inputBoxParticleAngleStart.setPosition(150, 290);

    sf::Text textParticleAngleStart;
    textParticleAngleStart.setFont(font);
    textParticleAngleStart.setCharacterSize(15);
    textParticleAngleStart.setFillColor(sf::Color::Black);
    textParticleAngleStart.setString("Angle Start");
    textParticleAngleStart.setPosition(10, 290);

    sf::RectangleShape inputBoxParticleAngleEnd(sf::Vector2f(50, 20));
    inputBoxParticleAngleEnd.setFillColor(sf::Color::White);
    inputBoxParticleAngleEnd.setOutlineThickness(2);
    inputBoxParticleAngleEnd.setOutlineColor(sf::Color::Black);
    inputBoxParticleAngleEnd.setPosition(150, 310);

    sf::Text textParticleAngleEnd;
    textParticleAngleEnd.setFont(font);
    textParticleAngleEnd.setCharacterSize(15);
    textParticleAngleEnd.setFillColor(sf::Color::Black);
    textParticleAngleEnd.setString("Angle End");
    textParticleAngleEnd.setPosition(10, 310);

    sf::RectangleShape button2(sf::Vector2f(190, 25));
    button2.setFillColor(sf::Color::White);
    button2.setOutlineThickness(2);
    button2.setOutlineColor(sf::Color::Black);
    button2.setPosition(10, 350);

    sf::Text button2Text;
    button2Text.setFont(font);
    button2Text.setCharacterSize(20);
    button2Text.setFillColor(sf::Color::Black);
    button2Text.setString("Insert Case 2");

    textBounds = button2Text.getLocalBounds();
    button2Text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    button2Text.setPosition(button2.getPosition().x + button2.getSize().x / 2.0f, button2.getPosition().y + button2.getSize().y / 2.0f);

    //CASE 3

    sf::RectangleShape inputBoxParticleStart3x(sf::Vector2f(25, 20));
    inputBoxParticleStart3x.setFillColor(sf::Color::White);
    inputBoxParticleStart3x.setOutlineThickness(2);
    inputBoxParticleStart3x.setOutlineColor(sf::Color::Black);
    inputBoxParticleStart3x.setPosition(150, 400);

    sf::RectangleShape inputBoxParticleStart3y(sf::Vector2f(25, 20));
    inputBoxParticleStart3y.setFillColor(sf::Color::White);
    inputBoxParticleStart3y.setOutlineThickness(2);
    inputBoxParticleStart3y.setOutlineColor(sf::Color::Black);
    inputBoxParticleStart3y.setPosition(175, 400);

    sf::Text textParticleStart3;
    textParticleStart3.setFont(font);
    textParticleStart3.setCharacterSize(15);
    textParticleStart3.setFillColor(sf::Color::Black);
    textParticleStart3.setString("Start Point");
    textParticleStart3.setPosition(10, 400);

    sf::RectangleShape inputBoxParticleAngle2(sf::Vector2f(50, 20));
    inputBoxParticleAngle2.setFillColor(sf::Color::White);
    inputBoxParticleAngle2.setOutlineThickness(2);
    inputBoxParticleAngle2.setOutlineColor(sf::Color::Black);
    inputBoxParticleAngle2.setPosition(150, 420);

    sf::Text textParticleAngle2;
    textParticleAngle2.setFont(font);
    textParticleAngle2.setCharacterSize(15);
    textParticleAngle2.setFillColor(sf::Color::Black);
    textParticleAngle2.setString("Angle");
    textParticleAngle2.setPosition(10, 420);

    sf::RectangleShape inputBoxParticleVelocityStart(sf::Vector2f(50, 20));
    inputBoxParticleVelocityStart.setFillColor(sf::Color::White);
    inputBoxParticleVelocityStart.setOutlineThickness(2);
    inputBoxParticleVelocityStart.setOutlineColor(sf::Color::Black);
    inputBoxParticleVelocityStart.setPosition(150, 440);

    sf::Text textParticleVelocityStart;
    textParticleVelocityStart.setFont(font);
    textParticleVelocityStart.setCharacterSize(15);
    textParticleVelocityStart.setFillColor(sf::Color::Black);
    textParticleVelocityStart.setString("Velocity Start");
    textParticleVelocityStart.setPosition(10, 440);

    sf::RectangleShape inputBoxParticleVelocityEnd(sf::Vector2f(50, 20));
    inputBoxParticleVelocityEnd.setFillColor(sf::Color::White);
    inputBoxParticleVelocityEnd.setOutlineThickness(2);
    inputBoxParticleVelocityEnd.setOutlineColor(sf::Color::Black);
    inputBoxParticleVelocityEnd.setPosition(150, 460);

    sf::Text textParticleVelocityEnd;
    textParticleVelocityEnd.setFont(font);
    textParticleVelocityEnd.setCharacterSize(15);
    textParticleVelocityEnd.setFillColor(sf::Color::Black);
    textParticleVelocityEnd.setString("Velocity End");
    textParticleVelocityEnd.setPosition(10, 460);

    sf::RectangleShape button3(sf::Vector2f(190, 25));
    button3.setFillColor(sf::Color::White);
    button3.setOutlineThickness(2);
    button3.setOutlineColor(sf::Color::Black);
    button3.setPosition(10, 500);

    sf::Text button3Text;
    button3Text.setFont(font);
    button3Text.setCharacterSize(20);
    button3Text.setFillColor(sf::Color::Black);
    button3Text.setString("Insert Case 3");

    textBounds = button3Text.getLocalBounds();
    button3Text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    button3Text.setPosition(button3.getPosition().x + button3.getSize().x / 2.0f, button3.getPosition().y + button3.getSize().y / 2.0f);


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

        window.draw(inputBoxParticleStart2x);
        window.draw(inputBoxParticleStart2y);
        window.draw(textParticleStart2);
		window.draw(inputBoxParticleVelocity2);
		window.draw(textParticleVelocity2);
		window.draw(inputBoxParticleAngleStart);
		window.draw(textParticleAngleStart);
		window.draw(inputBoxParticleAngleEnd);
		window.draw(textParticleAngleEnd);
		window.draw(button2);
		window.draw(button2Text);

        window.draw(inputBoxParticleStart3x);
        window.draw(inputBoxParticleStart3y);
        window.draw(textParticleStart3);
        window.draw(inputBoxParticleAngle2);
        window.draw(textParticleAngle2);
        window.draw(inputBoxParticleVelocityStart);
        window.draw(textParticleVelocityStart);
        window.draw(inputBoxParticleVelocityEnd);
        window.draw(textParticleVelocityEnd);
        window.draw(button3);
        window.draw(button3Text);




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
