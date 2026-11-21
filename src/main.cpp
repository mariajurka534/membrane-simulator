
#include <SFML/Graphics.hpp>
#include "Membrane.hpp"
#include "WaveSolver.hpp"
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <algorithm>

int main()
{

    float offsetX = 50.0f;
    float offsetY = 50.0f;

    sf::RenderWindow window(
        sf::VideoMode(1400, 900),
        "Membrane simulator"
    );

    window.setFramerateLimit(60);

    Membrane membrane(1.0, 1.0, 1.0, 1.0, 102, 102);

        float cellWidth = 800.0f / membrane.getGridWidth();
        float cellHeight = 800.0f / membrane.getGridLength();

    // membrane.setDisplacement(50, 50, 0.05);

    WaveSolver solver(membrane, 0.005, 0.4, 0.05, 10, 50, 50);

    sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
    
    while (window.isOpen())
    {
        sf::Event event;

        solver.update();

        

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        for(int i = 0; i < membrane.getGridLength(); i++){
            for(int j = 0; j < membrane.getGridWidth(); j++){

            cell.setPosition(
                offsetX + j * cellWidth,
                offsetY + i * cellHeight
            );

            double value = membrane.getDisplacement(i, j);

            double maxDisplacement = 0.02;
            double normalized = value / maxDisplacement;

            normalized = std::max(-1.0, std::min(1.0, normalized));

            sf::Color color;

            if (normalized < -0.7) {
                color = sf::Color(0, 0, 255);       // Blue
            }
            else if (normalized < -0.4) {
                color = sf::Color(0, 100, 255);    // Light blue
            }
            else if (normalized < -0.1) {
                color = sf::Color(0, 255, 255);   // Cyan
            }
            else if (normalized < 0.1) {
                color = sf::Color(0, 255, 0);     // Green
            }
            else if (normalized < 0.4) {
                color = sf::Color(255, 255, 0);   // Yellow
            }
            else if (normalized < 0.7) {
                color = sf::Color(255, 128, 0);   // Orange
            }
            else {
                color = sf::Color(255, 0, 0);     // Red
            }

            cell.setFillColor(color);

            window.draw(cell);
    }   
    }
        window.display();
    }

    return 0;
}



