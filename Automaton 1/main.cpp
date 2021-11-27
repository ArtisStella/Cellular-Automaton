#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include "Settings.h"
#include "RockPaperScissors.h"
#include "GameOfLife.h"


sf::RenderWindow *window;
sf::Event event;
Settings* settings;


int main() {

	settings = new Settings(sf::Vector2u(480, 360), 8);

	window = new sf::RenderWindow(sf::VideoMode(settings->windowSize.x, settings->windowSize.y), "Automaton 1", sf::Style::Close);
	window->setFramerateLimit(20);

	//RockPaperScissors rpcAutomata(*settings);
	GameOfLife golAutomata(*settings);


	while (window -> isOpen()) {
		while (window->pollEvent(event)) {
			
			switch (event.type) {

			case sf::Event::Closed:
				window->close();
			}
		}



		window->clear(settings->bgColour);

		//rpcAutomata.render(*window);
		golAutomata.render(*window);

		window->display();
		
		//rpcAutomata.update();
		golAutomata.update();
	}
	
	return 1;
}

