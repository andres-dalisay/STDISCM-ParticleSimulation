#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include<chrono>
#include <thread>
#include <mutex>

#include "Particle.cpp"
#include "FPS.cpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"


void drawInputWindow(sf::RenderWindow& window, sf::Font& font)
{
    
}



std::mutex mtx;

// make a function that will update a range of particle positions
void updateParticlePositions(std::vector<Particle>& particles,std::vector<sf::CircleShape>& particleShapes, int start, int end) {
	while (true) {
		for (int i = start; i <= end; i++) {
			particles.at(i).updateParticlePosition();
			particles.at(i).checkCollision();
			particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());

		}
	}
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

	//Particle particle(0, 300, 400, 45, 10);
	//sf::CircleShape ball(10);
	//ball.setPosition(particle.getPosX(), particle.getPosY());
	//ball.setPointCount(10);
	//ball.setFillColor(sf::Color::Red);

	std::vector<Particle> particles;
	std::vector<sf::CircleShape> particleShapes;
	std::vector<std::thread> threads;
	int threadCount = 2;

	for (int i = 0; i < 2; i++) {
		//push particles with random values
		particles.push_back(Particle(i, rand() % 1280, rand() % 720, rand() % 360, 2));
		particleShapes.push_back(sf::CircleShape(4, 10));
		particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
		particleShapes.at(i).setFillColor(sf::Color::Red);
	}

	int particlesPerThread = particles.size() / threadCount;
	int start = 0;
	int end = particlesPerThread - 1;

	for (int i = 0; i < 2; i++) {
		threads.push_back(std::thread(updateParticlePositions, std::ref(particles), std::ref(particleShapes), start, end));
		start += particlesPerThread;
		end += particlesPerThread;
	}

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



		// Draw the ball
		//window.draw(ball);
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

        for (int i = 0; i < particleShapes.size(); i++) {
            mainWindow.draw(particleShapes[i]);
        }
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

    ImGui::SFML::Shutdown();

    for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
        threads.at(i).join();
    }

    return 0;
}
