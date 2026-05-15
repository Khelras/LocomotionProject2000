/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Boid.h
Description : Declares the Boid Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include <cmath>

#include "locomotionproject2000/entities/Boid.h"
#include "locomotionproject2000/core/Settings.h"

Boid::Boid() {
	// Default Behaviour
	this->m_currentBehavior = BehaviorState::SEEK;
}

Boid::Boid(sf::Vector2f position) : Boid() {
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
}

Boid::~Boid() {
}

void Boid::update(AgentUpdateContext ctx) {
	// -- Simple Straight-Line Flight for Initial Testing -- //
	// Forward Direction Vector from the Rotation
	float radians = this->m_rotation.asRadians();
	sf::Vector2f forward(std::cosf(radians), std::sinf(radians));

	// Velocity Vector
	this->m_velocity = forward * this->m_maxSpeed;

	// Apply the Velocity Vector and Perform Movement
	this->m_position += this->m_velocity * ctx.dt;

	// Border Wrapping
	float screenWidth = static_cast<float>(Settings::getInstance().windowWidth);
	float screenHeight = static_cast<float>(Settings::getInstance().windowHeight);
	if (this->m_position.x < 0.0f) this->m_position.x = screenWidth; // Left to Right Wrapping
	if (this->m_position.x > screenWidth) this->m_position.x = 0.0f; // Right to Left Wrapping
	if (this->m_position.y < 0.0f) this->m_position.y = screenHeight; // Top to Bottom Wrapping
	if (this->m_position.y > screenHeight) this->m_position.y = 0.0f; // Bottom to Top Wrapping

	// Update the Transform Properties of the Shape
	this->m_shape.setPosition(this->m_position);
	this->m_shape.setRotation(this->m_rotation);
	// -- //
}
