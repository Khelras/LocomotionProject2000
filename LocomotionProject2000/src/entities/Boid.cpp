/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Boid.cpp
Description : Defines the Boid Class Core Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/entities/Boid.h"
#include "locomotionproject2000/core/Settings.h"

Boid::Boid() {
	// Default Behaviour
	this->m_currentBehaviour = BehaviourState::NONE;
}

Boid::Boid(sf::Vector2f position, BehaviourState movementBehaviour) : Boid() {
	// Shape of the Boid
	this->m_shape.setPointCount(3);
	this->m_shape.setPoint(0, sf::Vector2f(20.0f, 0.0f)); // Tip
	this->m_shape.setPoint(1, sf::Vector2f(-10.0f, 10.0f)); // Back-Left
	this->m_shape.setPoint(2, sf::Vector2f(-10.0f, -10.0f)); // Back-Right
	this->m_shape.setOrigin(sf::Vector2f(0.0f, 0.0f));
	this->m_shape.setFillColor(sf::Color::White);

	// Set the initial position
	this->m_position = position;
	this->m_shape.setPosition(position);

	// Set the Movement Behaviour State
	this->m_currentBehaviour = movementBehaviour;
}

Boid::~Boid() {
}

void Boid::update(AgentUpdateContext ctx) {
	// Switch-Case for the Movement Behaviour
	switch (this->m_currentBehaviour) {
		case BehaviourState::NONE: this->none(ctx); break; // Simple Forward Movement
		case BehaviourState::SEEK: this->seek(ctx); break; // Seek Momvement Behaviour
		case BehaviourState::FLEE: this->flee(ctx); break; // Flee Momvement Behaviour
		case BehaviourState::PURSUE: this->pursue(ctx); break; // Pursue Momvement Behaviour
		case BehaviourState::EVADE: this->evade(ctx); break; // Evade Momvement Behaviour
		case BehaviourState::WANDER: this->wander(ctx); break; // Wander Momvement Behaviour
		case BehaviourState::ARRIVAL: this->arrival(ctx); break; // Arrival Momvement Behaviour
		case BehaviourState::FLOCK: this->flock(ctx); break; // Flock Momvement Behaviour
		case BehaviourState::LEADER_FOLLOW: this->leaderFollow(ctx); break; // Follow the Leader Momvement Behaviour
		default: this->none(ctx); break; // Default to Simple Forward Movement
	}

	// Afterwards, Border Wrapping
	float screenWidth = static_cast<float>(Settings::getInstance().windowWidth);
	float screenHeight = static_cast<float>(Settings::getInstance().windowHeight);
	if (this->m_position.x < 0.0f) this->m_position.x = screenWidth; // Left to Right Wrapping
	if (this->m_position.x > screenWidth) this->m_position.x = 0.0f; // Right to Left Wrapping
	if (this->m_position.y < 0.0f) this->m_position.y = screenHeight; // Top to Bottom Wrapping
	if (this->m_position.y > screenHeight) this->m_position.y = 0.0f; // Bottom to Top Wrapping

	// Lastly, Update the Transform Properties of the Shape
	this->m_shape.setPosition(this->m_position);
	this->m_shape.setRotation(this->m_rotation);
}

void Boid::setMovementBehaviour(BehaviourState movementBehaviour) {
	this->m_currentBehaviour = movementBehaviour;
}
