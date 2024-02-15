#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <mutex>


#include "Particle.cpp"
#include "FPS.cpp"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

std::mutex mtx;
std::condition_variable cv;
bool readyToRender = false;
int threadDoneCount = 0;
const int numThreads = 4;


void updateParticles(std::vector<Particle>& particles, std::vector<sf::CircleShape>& particleShapes, std::vector<Wall>& walls, int startIndex, int endIndex) {
    while (true){
        {
			std::unique_lock lk(mtx);
			for (int i = startIndex; i < endIndex; i++) {
				particles.at(i).checkCollision(walls);
				particles.at(i).updateParticlePosition();
				particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
			}
			readyToRender = true;
			cv.notify_one();
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
    const std::chrono::milliseconds timeInterval(500); // 0.5 seconds
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

	std::vector<Particle> particles;
	std::vector<sf::CircleShape> particleShapes;
    int particleCount = 0;

    std::vector<Wall> walls;
    std::vector<sf::VertexArray> wallShapes;

    // SAMPLE WALLS
    sf::VertexArray wallLine(sf::Lines, 2);
    wallLine[0].position = sf::Vector2f(300, 100);
    wallLine[1].position = sf::Vector2f(300, 300);
    wallLine[0].color = sf::Color::White;
    wallLine[1].color = sf::Color::White;

    walls.push_back(Wall(300, 100, 300, 300));
    wallShapes.push_back(wallLine);

    sf::VertexArray wallLine2(sf::Lines,2);
    wallLine2[0].position = sf::Vector2f(650, 650);
    wallLine2[1].position = sf::Vector2f(350, 650);
    wallLine2[0].color = sf::Color::White;
    wallLine2[1].color = sf::Color::White;


    walls.push_back(Wall(650, 650, 350, 650));
    wallShapes.push_back(wallLine2);

	sf::VertexArray wallLine3(sf::Lines, 2);
	wallLine3[0].position = sf::Vector2f(350, 150);
	wallLine3[1].position = sf::Vector2f(550, 450);
	wallLine3[0].color = sf::Color::White;
	wallLine3[1].color = sf::Color::White;

	walls.push_back(Wall(350, 150, 550, 450));
	wallShapes.push_back(wallLine3);
    for (int i = 0; i < 4; i++) {
		particles.push_back(Particle(i, 100, 100, 0, 1));
		particleShapes.push_back(sf::CircleShape(4, 10));
		particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
		particleShapes.at(i).setFillColor(sf::Color::Red);
		particleCount++;
	}

    //std::thread::hardware_concurrency();
	const int particlesPerThread = particleCount / numThreads;
	std::vector<std::thread> threads;

	for (int i = 0; i < numThreads; ++i) {
		int startIndex = i * particlesPerThread;
		int endIndex = (i == numThreads - 1) ? particleCount : (i + 1) * particlesPerThread;
		threads.emplace_back(updateParticles, std::ref(particles), std::ref(particleShapes), std::ref(walls), startIndex, endIndex);
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

		ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("Input Particle", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::SeparatorText("Add Particles");

        //imgui input numbers only
        static int numberParticles = 0;
        ImGui::InputInt("Num Particles", &numberParticles);
        ImGui::Text("");
        ImGui::Text("");

        static int startX = 0;
        static int startY = 0;
        static int endX = 0;
        static int endY = 0;
        static float velocity = 0;
        static float angle = 0;

        ImGui::InputInt("Start X1", &startX);
        ImGui::InputInt("Start Y1", &startY);
        ImGui::InputInt("End X1", &endX);
		ImGui::InputInt("End Y1", &endY);
        ImGui::InputFloat("Velocity 1", &velocity);
        ImGui::InputFloat("Angle 1", &angle);
        
        //imgui button input
        if (ImGui::Button("Add Case 1"))
        {
			std::cout << "CASE1: Adding " << numberParticles << " particles at " << startX << ", " << startY << " with velocity " << velocity << " and angle " << angle << std::endl;
            float distance = sqrt(pow(endX - startX, 2) + pow(endY - startY, 2));
            float interval = 0;
            if (numberParticles == 1) interval = 0;
            else interval = distance / (numberParticles - 1);
            
            for(int i = 0; i < numberParticles; i++){
				particles.push_back(Particle(i, startX + interval * i, startY + interval*i, angle, velocity));
				particleShapes.push_back(sf::CircleShape(4, 10));
				particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
				particleShapes.at(i).setFillColor(sf::Color::Red);
                particleCount++;
            }

        }

        ImGui::Text("");
        ImGui::Text("");

        static int startX2 = 0;
        static int startY2 = 0;
        static float velocity2 = 0;
        static float angleStart = 0;
        static float angleEnd = 0;

        ImGui::InputInt("Start X2", &startX2);
        ImGui::InputInt("Start Y2", &startY2);
        ImGui::InputFloat("Velocity 2", &velocity2);
        ImGui::InputFloat("Angle Start", &angleStart);
        ImGui::InputFloat("Angle End", &angleEnd);

        //imgui button input
        if (ImGui::Button("Add Case 2"))
        {
            std::cout << "CASE2: Adding " << numberParticles << " particles at " << startX2 << ", " << startY2 << " with velocity " << velocity2 << " and angle " << angleStart << " to " << angleEnd << std::endl;
            float interval = 0;
            if (numberParticles >1) interval = (angleEnd - angleStart) / (numberParticles - 1);
                
            std::cout << interval;

			for (int i = 0; i < numberParticles; i++) {
				particles.push_back(Particle(i, startX2, startY2, angleStart+(interval*i), velocity2));
				particleShapes.push_back(sf::CircleShape(4, 10));
				particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
				particleShapes.at(i).setFillColor(sf::Color::Red);
				particleCount++;
			}
        
        }

        ImGui::Text("");
        ImGui::Text("");

        static int startX3 = 0;
        static int startY3 = 0;
        static float angle3 = 0;
        static float velocityStart = 0;
        static float velocityEnd = 0;

        ImGui::InputInt("Start X3", &startX3);
        ImGui::InputInt("Start Y3", &startY3);
        ImGui::InputFloat("Angle 3", &angle3);
        ImGui::InputFloat("Velocity Start", &velocityStart);
        ImGui::InputFloat("Velocity End", &velocityEnd);

        //imgui button input
        if (ImGui::Button("Add Case 3"))
        {
			std::cout << "CASE3: Adding " << numberParticles << " particles at " << startX3 << ", " << startY3 << " with angle " << angle3 << " and velocity " << velocityStart << " to " << velocityEnd << std::endl;
		    
			float interval = 0;
            if (numberParticles > 1) {
                interval = (velocityEnd - velocityStart) / (numberParticles - 1);
            }
                

			std::cout << interval;

			for (int i = 0; i < numberParticles; i++) {
                //std::cout << "Velocity: " << velocityStart + (interval * i) << " | Angle: " << angle3 << std::endl;
                std::cout << "velocityStart: " << velocityStart << " | interval: " << interval << " | i: " << i << " | velocity: " << velocityStart + (interval * i) << std::endl;  
				particles.push_back(Particle(i, startX3, startY3, angle3, velocityStart + (interval * i)));
				particleShapes.push_back(sf::CircleShape(4, 10));
				particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
				particleShapes.at(i).setFillColor(sf::Color::Red);
				particleCount++;
			}
        }

        if (ImGui::Button("Clear Balls"))
        {
            particleCount = 0;
            //clear array of balls
        }

        ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(1000, 0));

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
            walls.push_back(Wall(wallStartX, wallStartY, wallEndX, wallEndY));
            sf::VertexArray wall(sf::Lines, 2);
            wall[0].position = sf::Vector2f(wallStartX, wallStartY);
            wall[1].position = sf::Vector2f(wallEndX, wallEndY);
            wallShapes.push_back(wall);
        }
        ImGui::End();



        // Clear the main window
        mainWindow.clear(sf::Color::Black);    

        for (auto& wall : wallShapes) {
            mainWindow.draw(wall);
        }

        /*for (int i = 0; i < particleCount; i++) {
            particles.at(i).checkCollision(walls);

            particles.at(i).updateParticlePosition();
            particleShapes.at(i).setPosition(particles.at(i).getPosX(), particles.at(i).getPosY());
        }*/

        std::unique_lock lock(mtx);
        cv.wait(lock, [] { return readyToRender; });
        for (int i = 0; i < particleShapes.size(); i++) {
            mainWindow.draw(particleShapes[i]);
        }
        readyToRender = false;
        lock.unlock();

        fps.update();

        if (elapsedFPSTime >= timeInterval)
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

	for (auto& thread : threads) {
		thread.join();
	}

    ImGui::SFML::Shutdown();

    return 0;
}
