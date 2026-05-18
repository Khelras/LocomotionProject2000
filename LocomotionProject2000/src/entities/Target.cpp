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


#include <cmath>
#include <random>

#include "locomotionproject2000/entities/Target.h"

Target::Target() {
	// Shape of the Target
	this->m_shape = std::make_unique<sf::CircleShape>(10);
	this->m_shape->setOrigin(this->m_shape->getGeometricCenter());
	this->m_shape->setFillColor(sf::Color::Green);

	// Default Behaviour
	this->m_currentBehaviour = BehaviourState::NONE;

	// Default Wander Angle of 0 
	this->m_wanderAngle = 0.0f;

	// Speed
	this->m_maxSpeed = 125.0f;
}

Target::~Target() {
}

void Target::update(AgentUpdateContext ctx) {
	// Check if the Movement Behaviour State is set to Wander
	if (this->m_currentBehaviour == BehaviourState::WANDER) {
		// TODO: Implement TRUE Target Wander Logic
		// Wander Circle Properties
		float wanderRadius = 50.0f; // The size of Wander Circle
		float wanderDistance = 60.0f; // How far is the Wander Circle from the Boid
		float wanderJitter = 0.3f; // How "Noisy" the Angle changes are

		// Get the Forward Vector
		sf::Vector2f forward = (this->m_velocity.lengthSquared() == 0.0f)
			? sf::Vector2f(1.0f, 0.0f) : this->m_velocity.normalized();

		// Calculate the Wander Circle Center
		sf::Vector2f wanderCircleCenter = this->m_position + forward * wanderDistance;

		// RNG for the Random Wander Angle
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // RNG from  -1.0f to 1.0f (Floating-Point Inclusive)
		this->m_wanderAngle += dis(gen) * wanderJitter; // Scale the RNG with the Wander Jitter for the new Wander Angle

		// Calculate the Displacement Vector
		sf::Vector2f displacement;
		displacement.x = cos(m_wanderAngle) * wanderRadius;
		displacement.y = sin(m_wanderAngle) * wanderRadius;

		// Cacluate the Wander Target Vector
		sf::Vector2f wanderTargetPos = wanderCircleCenter + displacement;

		// Calculate our Desired Velocity
		sf::Vector2f desiredVelocity = this->getShortestPathVector(this->m_position, wanderTargetPos).normalized() * this->m_maxSpeed;

		// Calculate the Steering Force
		sf::Vector2f steering = desiredVelocity - this->m_velocity;
		steering = (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
			? steering.normalized() * this->m_maxForce : steering;

		// Cacluate the Acceleration (F = ma >> a = F/m)
		this->m_acceleration += steering / this->m_mass;

		// Apply Acceleration
		this->m_velocity += this->m_acceleration * ctx.dt;
		this->m_velocity = (this->m_velocity.lengthSquared() > this->m_maxSpeed * this->m_maxSpeed)
			? this->m_velocity.normalized() * this->m_maxSpeed : this->m_velocity;

		// Apply Velocity
		this->m_position += this->m_velocity * 1.5f /*Scalar*/ * ctx.dt;
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
	this->m_acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Target::draw(sf::RenderWindow& window) {
	// Draw the Target
	window.draw(*this->m_shape.get());
}

BehaviourState Target::getMovementBehaviour() const {
	return this->m_currentBehaviour;
}

void Target::setMovementBehaviour(BehaviourState movementBehaviour) {
	this->m_currentBehaviour = movementBehaviour;
}