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
	std::unique_ptr<sf::ConvexShape> convex = std::make_unique<sf::ConvexShape>(3);
	convex->setPoint(0, sf::Vector2f(20.0f, 0.0f)); // Tip
	convex->setPoint(1, sf::Vector2f(-10.0f, 10.0f)); // Back-Left
	convex->setPoint(2, sf::Vector2f(-10.0f, -10.0f)); // Back-Right
	convex->setOrigin(sf::Vector2f(0.0f, 0.0f));
	convex->setFillColor(sf::Color::White);
	this->m_shape = std::move(convex);

	// Set the initial position
	this->m_position = position;
	this->m_shape->setPosition(position);

	// Set the Movement Behaviour State
	this->m_currentBehaviour = movementBehaviour;
}

Boid::~Boid() {
}

void Boid::update(AgentUpdateContext ctx) {
	// Switch-Case for the Movement Behaviour
	switch (this->m_currentBehaviour) {
		case BehaviourState::SEEK: this->seek(ctx); break; // Seek Momvement Behaviour
		case BehaviourState::FLEE: this->flee(ctx); break; // Flee Momvement Behaviour
		case BehaviourState::PURSUE: this->pursue(ctx); break; // Pursue Momvement Behaviour
		case BehaviourState::EVADE: this->evade(ctx); break; // Evade Momvement Behaviour
		case BehaviourState::WANDER: this->wander(ctx); break; // Wander Momvement Behaviour
		case BehaviourState::ARRIVAL: this->arrival(ctx); break; // Arrival Momvement Behaviour
		case BehaviourState::FLOCK: this->flock(ctx); break; // Flock Momvement Behaviour
		case BehaviourState::LEADER_FOLLOW: this->leaderFollow(ctx); break; // Follow the Leader Momvement Behaviour
		default: break; // Default
	}

	// Apply Acceleration
	this->m_velocity += this->m_acceleration * ctx.dt;
	this->m_velocity = (this->m_velocity.lengthSquared() > this->m_maxSpeed * this->m_maxSpeed)
		? this->m_velocity.normalized() * this->m_maxSpeed : this->m_velocity;

	// Apply Velocity
	this->m_position += this->m_velocity * 1.5f /*Scalar*/ * ctx.dt;

	// Apply Border Wrapping Rules
	float screenWidth = static_cast<float>(Settings::getInstance().windowWidth);
	float screenHeight = static_cast<float>(Settings::getInstance().windowHeight);
	if (this->m_position.x < 0.0f) this->m_position.x += screenWidth; // Left to Right Wrapping
	if (this->m_position.x > screenWidth) this->m_position.x -= screenWidth; // Right to Left Wrapping
	if (this->m_position.y < 0.0f) this->m_position.y += screenHeight; // Top to Bottom Wrapping
	if (this->m_position.y > screenHeight) this->m_position.y -= screenHeight; // Bottom to Top Wrapping

	// Lastly, Update the Transform Properties of the Shape
	this->m_shape->setPosition(this->m_position);
	//this->m_acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Boid::setMovementBehaviour(BehaviourState movementBehaviour) {
	this->m_currentBehaviour = movementBehaviour;
}
