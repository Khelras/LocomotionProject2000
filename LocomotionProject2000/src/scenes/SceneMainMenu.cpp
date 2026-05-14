/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name   : SceneMainMenu.cpp
Description : Defines the SceneMainMenu Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/scenes/SceneMainMenu.h"
#include "locomotionproject2000/scenes/SceneManager.h"

SceneMainMenu::SceneMainMenu() {
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
}
