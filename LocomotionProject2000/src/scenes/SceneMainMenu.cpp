/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : SceneMainMenu.cpp
Description : Defines the SceneMainMenu Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include <string>

#include "locomotionproject2000/scenes/SceneMainMenu.h"
#include "locomotionproject2000/scenes/SceneManager.h"
#include "locomotionproject2000/core/Settings.h"

SceneMainMenu::SceneMainMenu() {
	// UI
	if (this->m_font.openFromFile("assets/fonts/arial.ttf") == false) {
		// DEBUG
		std::cerr << "Unable to open file from path: 'assets/fonts/arial.ttf'" << std::endl;
	}

	// -- Space Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the SpaceKey
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Space;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG	
			std::cout << "Space Key Pressed in context of Main Menu Scene!" << std::endl;

			// Go to the Gameplay Scene
			ctx.sceneManager->goToScene("GameplayScene");
		}
	});
	// -- //
}

SceneMainMenu::~SceneMainMenu() {
}

void SceneMainMenu::handleEvent(const sf::Event& event, const CommandContext& ctx) {
	// Loop through all Registered Commands and check if any of them match the given SFML Event
	for (auto& command : this->m_commands) {
		// Check if this Registered Command matches the given SFML Event
		if (command.match(event)) {
			// Execute the Registered Command's action using the provided context
			command(ctx);
		}
	}
}

void SceneMainMenu::update(float dt) {
}

void SceneMainMenu::draw(sf::RenderWindow& window) {
	// Screen Dimenions
	float screenWidth = static_cast<float>(Settings::getInstance().windowWidth);
	float screenHeight = static_cast<float>(Settings::getInstance().windowHeight);

	// -- Title Text -- //
	sf::Text title(this->m_font);
	title.setCharacterSize(45);
	title.setString("Welcome to Angelo's Epic Locomotion Simulator 2000!");
	title.setOrigin(title.getGlobalBounds().getCenter());
	title.setPosition(sf::Vector2f(screenWidth / 2.0f, title.getGlobalBounds().size.y * 2.0f));
	window.draw(title);
	// -- //

	// -- Behaviour Control Text -- //
	std::string controlBehaviourString = {
		"Boid Movement\nBehaviour Controls:\n"
		"    0: NONE\n"
		"    1: SEEK\n"
		"    2: FLEE\n"
		"    3: WANDER\n"
		"    4: ARRIVAL\n"
		"    5: FLOCKING\n"
		"    6: LEADER-FOLLOW"
	};

	sf::Text controlBehaviour(this->m_font);
	controlBehaviour.setCharacterSize(30);
	controlBehaviour.setString(controlBehaviourString);
	controlBehaviour.setOrigin(controlBehaviour.getGlobalBounds().getCenter());
	controlBehaviour.setPosition(sf::Vector2f(screenWidth / 4.0f, screenHeight / 2.0f));
	window.draw(controlBehaviour);
	// -- //

	// -- Other Control Text -- //
	std::string controlOtherString = {
		"Other Controls:\n"
		"    Left-Click: Spawn Boid\n"
		"    Right-Click: Spawn Obstacle\n"
		"    Middle-Click: Move Target\n"
		"\n"
		"    Space: Toggle Target State\n"
		"           (NONE <-> WANDER)\n"
		"\n"
		"    Backspace: Delete 5 Boids\n"
		"    S: Spawn 10 Boids\n"
		"    D: Display Debug Bounds\n"
		"    C: Clear all Obstacles\n"
	};

	sf::Text controlOther(this->m_font);
	controlOther.setCharacterSize(30);
	controlOther.setString(controlOtherString);
	controlOther.setOrigin(controlOther.getGlobalBounds().getCenter());
	controlOther.setPosition(sf::Vector2f(((screenWidth / 4.0f) * 3.0f) - 50.0f, screenHeight / 2.0f));
	window.draw(controlOther);
	// -- //

	// -- Footer Text -- //
	sf::Text footer(this->m_font);
	footer.setCharacterSize(45);
	footer.setString("Press 'Space' to go Next!");
	footer.setOrigin(footer.getGlobalBounds().getCenter());
	footer.setPosition(sf::Vector2f(screenWidth / 2.0f, screenHeight - (title.getGlobalBounds().size.y * 2.0f)));
	window.draw(footer);
	// -- //
}
