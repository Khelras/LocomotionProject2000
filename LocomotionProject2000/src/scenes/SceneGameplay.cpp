/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : SceneGameplay.cpp
Description : Defines the SceneGameplay Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/scenes/SceneGameplay.h"

SceneGameplay::SceneGameplay() {
	// Background Color
	this->m_backgroundColor = sf::Color::Black;

	// -- Left Mouse Button Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Mouse Button Press, then check if the Mouse Button was the Left Mouse Button
			if (const auto* key = event.getIf<sf::Event::MouseButtonPressed>()) {
				return key->button == sf::Mouse::Button::Left;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Left-Mouse-Button Pressed in context of Gameplay Scene!" << std::endl;
			sf::Vector2i mousePos = sf::Mouse::getPosition(ctx.window);
			std::cout << "Mouse Position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
		}
	});
	// -- //
}

SceneGameplay::~SceneGameplay() {
}

void SceneGameplay::handleEvent(const sf::Event& event, const CommandContext& ctx) {
	// Loop through all Registered Commands and check if any of them match the given SFML Event
	for (auto& command : this->m_commands) {
		// Check if this Registered Command matches the given SFML Event
		if (command.match(event)) {
			// Execute the Registered Command's action using the provided context
			command(ctx);
		}
	}
}

void SceneGameplay::update(float dt) {
}

void SceneGameplay::draw(sf::RenderWindow& window) {
}
