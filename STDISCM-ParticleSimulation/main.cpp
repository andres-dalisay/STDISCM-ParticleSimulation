#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

#include "FPS.cpp"

#include "imgui.h"
#include "imgui-SFML.h"


void drawInputWindow(sf::RenderWindow& window, sf::Font& font)
{
    
}



int main()
{
    // Create the main window
    sf::RenderWindow mainWindow(sf::VideoMode(1280, 720), "Particle Simulator");
    mainWindow.setFramerateLimit(60);
    ImGui::SFML::Init(mainWindow);

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

    sf::Clock deltaClock;
    // Main loop
    while (mainWindow.isOpen())
    {
        auto currentFPSTime = std::chrono::steady_clock::now();
        auto elapsedFPSTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentFPSTime - lastFPSDrawTime);

        // Process events
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            
        }
        ImGui::SFML::Update(mainWindow, deltaClock.restart());

        ImGui::Begin("Input Particle", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SeparatorText("Add Particles");

        //imgui input numbers only
        static int numberParticles = 0;
        ImGui::InputInt("Num Particles", &numberParticles);
        ImGui::Text("");
        ImGui::Text("");

        static int startX = 0;
        static int startY = 0;
        static int velocity = 0;
        static int angle = 0;

        ImGui::InputInt("Start X1", &startX);
        ImGui::InputInt("Start Y1", &startY);
        ImGui::InputInt("Velocity 1", &velocity);
        ImGui::InputInt("Angle 1", &angle);
        
        //imgui button input
        if (ImGui::Button("Add Case 1"))
        {
			std::cout << "CASE1: Adding " << numberParticles << " particles at " << startX << ", " << startY << " with velocity " << velocity << " and angle " << angle << std::endl;
		}

        ImGui::Text("");
        ImGui::Text("");

        static int startX2 = 0;
        static int startY2 = 0;
        static int velocity2 = 0;
        static int angleStart = 0;
        static int angleEnd = 0;

        ImGui::InputInt("Start X2", &startX2);
        ImGui::InputInt("Start Y2", &startY2);
        ImGui::InputInt("Velocity 2", &velocity2);
        ImGui::InputInt("Angle Start", &angleStart);
        ImGui::InputInt("Angle End", &angleEnd);

        //imgui button input
        if (ImGui::Button("Add Case 2"))
        {
            std::cout << "CASE2: Adding " << numberParticles << " particles at " << startX2 << ", " << startY2 << " with velocity " << velocity2 << " and angle " << angleStart << " to " << angleEnd << std::endl;
        }

        ImGui::Text("");
        ImGui::Text("");

        static int startX3 = 0;
        static int startY3 = 0;
        static int angle3 = 0;
        static int velocityStart = 0;
        static int velocityEnd = 0;

        ImGui::InputInt("Start X3", &startX3);
        ImGui::InputInt("Start Y3", &startY3);
        ImGui::InputInt("Angle 3", &angle3);
        ImGui::InputInt("Velocity Start", &velocityStart);
        ImGui::InputInt("Velocity End", &velocityEnd);

        //imgui button input
        if (ImGui::Button("Add Case 3"))
        {
			std::cout << "CASE3: Adding " << numberParticles << " particles at " << startX3 << ", " << startY3 << " with angle " << angle3 << " and velocity " << velocityStart << " to " << velocityEnd << std::endl;
		}

        ImGui::End();

        ImGui::Begin("Input Wall", NULL, ImGuiWindowFlags_AlwaysAutoResize);        
        ImGui::SeparatorText("Add Walls");

        static int wallStartX = 0;
        static int wallStartY = 0;
        static int wallEndX = 0;
        static int wallEndY = 0;

        ImGui::InputInt("Start X", &wallStartX);
        ImGui::InputInt("Start Y", &wallStartY);
        ImGui::InputInt("End X", &wallEndX);
        ImGui::InputInt("End Y", &wallEndY);

        //imgui button input
        if (ImGui::Button("Add Wall"))
        {
            std::cout << "Adding wall from " << wallStartX << ", " << wallStartY << " to " << wallEndX << ", " << wallEndY << std::endl;
        }


        ImGui::End();



        // Clear the main window
        mainWindow.clear(sf::Color::Black);

        //// Draw button
        //mainWindow.draw(button);
        //mainWindow.draw(buttonText);

        fps.update();

        if (elapsedFPSTime >= interval)
        {
            // Update last draw time
            lastFPSDrawTime = currentFPSTime;
            fpsText.setString(std::to_string(fps.getFPS()) + " FPS");
        }
        mainWindow.draw(fpsText);

        ImGui::SFML::Render(mainWindow);

        // Display the contents of the main window
        mainWindow.display();
    }

    return 0;
}
