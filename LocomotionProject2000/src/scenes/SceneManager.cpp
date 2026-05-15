/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name   : SceneManager.cpp
Description : Defines the SceneManager Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/scenes/SceneManager.h"

SceneManager::SceneManager() {
	// Register Scenes
	this->m_sceneRegistry.emplace("MainScene", std::make_shared<SceneMainMenu>()); // Main Menu Scene
	this->m_sceneRegistry.emplace("GameplayScene", std::make_shared<SceneGameplay>()); // Gameplay Scene

	// Start with the Main Scene
	this->m_sceneStack.push(this->m_sceneRegistry.at("MainScene"));
}

void SceneManager::handleEvent(const sf::Event& event, const CommandContext& ctx) {
	// Send the Event to the current Active Scene for Scene-Related Processing.
	this->m_sceneStack.top()->handleEvent(event, ctx);
}

void SceneManager::update(float dt) {
	// Call the Update method of the current Active Scene for Scene-Related Updating.
	this->m_sceneStack.top()->update(dt);
}

void SceneManager::render(sf::RenderWindow& window) {
	// Call the Draw method of the current Active Scene for Scene-Related Rendering.
	this->m_sceneStack.top()->draw(window);
}

std::weak_ptr<Scene> SceneManager::getActiveScene() {
	return std::weak_ptr<Scene>(this->m_sceneStack.top());
}

void SceneManager::goToScene(const std::string& sceneName) {
	// Check if the requested scene exists in the registry
	if (this->m_sceneRegistry.find(sceneName) != this->m_sceneRegistry.end()) {
		// If there is a current Active Scene, call its onExit() method for cleanup
		if (!this->m_sceneStack.empty()) {
			this->m_sceneStack.top()->onExit();
			this->m_sceneStack.pop();
		}

		// Push the new scene onto the stack and call its onEnter() method for initialization
		this->m_sceneStack.push(this->m_sceneRegistry.at(sceneName));
		this->m_sceneStack.top()->onEnter();
	}
	else {
		// DEBUG
		std::cerr << "Scene '" << sceneName << "' not found in the scene registry!" << std::endl;
	}
}
