/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name   : Window.cpp
Description : Defines the Window Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/core/Window.h"

Window::Window() {
	// Default Window Properties
	sf::VideoMode defaultMode({ 1200, 800 });
	sf::String defaultName = "Locomotion Project 2000!";

	// Create an SFML RenderWindow
	this->create(defaultMode, defaultName, sf::Style::Close);
	this->m_resolution = defaultMode.size;
	this->setFramerateLimit(30);
}

Window::Window(sf::VideoMode mode, const std::string& name) {
	// Create an SFML RenderWindow
	this->create(mode, name, sf::Style::Close);
	this->m_resolution = mode.size;
	this->setFramerateLimit(30);
}

Window::~Window() {
}

void Window::process() {
	// Create a CommandContext to pass to the SceneManager when processing Events and Commands
	CommandContext ctx{ *this };

	// Clock
	sf::Clock clock;

	// -- Main Process Loop -- //
	while (this->isOpen() == true) {
		// Delta Time
		float dt = clock.restart().asSeconds();

		// Process all raw SFML Events
		while (const auto event = this->pollEvent()) {
			// -- 1. Global Raw SFML Event Handling -- //
			// Window Close Event
			if (event->is<sf::Event::Closed>()) {
				this->close();
				break;
			}
			// -- //

			// -- 2. Otherwise, Send to Scene Manager for Scene-Specific Command Handling -- // 
			this->m_sceneManager.handleEvent(*event, ctx);
			// -- //
		}

		// -- Update Loops -- //
		this->m_sceneManager.update(dt);
		// -- //

		// -- Rendering -- //
		// Step 1: Clear the back buffer
		this->clear();

		// Step 2: Draw and render objects to the back buffer
		this->draw();

		// Step 3: Swap buffers and display the back buffer
		this->display();
		// -- //
	}
	// -- //
}

void Window::clear() {
	sf::RenderWindow::clear(sf::Color(6, 64, 43)); // Dark Green Background :D
}

void Window::draw() {
	this->m_sceneManager.render(*this);
}

void Window::display() {
	sf::RenderWindow::display();
}
