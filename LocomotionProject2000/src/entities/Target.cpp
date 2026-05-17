/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Target.cpp
Description : Defines the Target Class Core Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/entities/Target.h"

Target::Target() {
	// Shape of the Target
	this->m_shape = std::make_unique<sf::CircleShape>(10);
	this->m_shape->setOrigin(this->m_shape->getGeometricCenter());
	this->m_shape->setFillColor(sf::Color::Green);

	// Default Behaviour
	this->m_currentBehaviour = BehaviourState::NONE;
}

Target::~Target() {
}

void Target::update(AgentUpdateContext ctx) {
	// Check if the Movement Behaviour State is set to Wander
	if (this->m_currentBehaviour == BehaviourState::WANDER) {
		// TODO: Implement TRUE Target Wander Logic
	}

	// Afterwards, Border Wrapping
	float screenWidth = static_cast<float>(Settings::getInstance().windowWidth);
	float screenHeight = static_cast<float>(Settings::getInstance().windowHeight);
	if (this->m_position.x < 0.0f) this->m_position.x = screenWidth; // Left to Right Wrapping
	if (this->m_position.x > screenWidth) this->m_position.x = 0.0f; // Right to Left Wrapping
	if (this->m_position.y < 0.0f) this->m_position.y = screenHeight; // Top to Bottom Wrapping
	if (this->m_position.y > screenHeight) this->m_position.y = 0.0f; // Bottom to Top Wrapping

	// Lastly, Update the Transform Properties of the Shape
	this->m_shape->setPosition(this->m_position);
}

BehaviourState Target::getMovementBehaviour() const {
	return this->m_currentBehaviour;
}

void Target::setMovementBehaviour(BehaviourState movementBehaviour) {
	this->m_currentBehaviour = movementBehaviour;
}