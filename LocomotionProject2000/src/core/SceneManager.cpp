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

#include "locomotionproject2000/core/SceneManager.h"

SceneManager::SceneManager() {
	// Register Scenes
	this->m_sceneRegistry.emplace("MainScene", std::make_shared<SceneMain>());

	// Start with the Main Scene
	this->m_sceneStack.push(this->m_sceneRegistry.at("MainScene"));
}

void SceneManager::handleEvent(const sf::Event& event, const CommandContext& ctx) {
	this->m_sceneStack.top()->handleEvent(event, ctx);
}

void SceneManager::update(float dt) {
	this->m_sceneStack.top()->update(dt);
}

void SceneManager::render(sf::RenderWindow& window) {
	this->m_sceneStack.top()->draw(window);
}
