#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "FPS.cpp"


void drawInputWindow(sf::RenderWindow& window, sf::Font& font)
{
    
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
