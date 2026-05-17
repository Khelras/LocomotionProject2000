/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : BoidMovement.cpp
Description : Defines the Boid Class Movement Behaviour Functions
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include <iostream>
#include <cmath>

#include "locomotionproject2000/entities/Boid.h"
#include "locomotionproject2000/entities/Target.h"

void Boid::seek(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Seek' Movement Behavior." << std::endl;

	// Calculate our Desired Velocity
	sf::Vector2f targetPos = ctx.target.getPosition();
	sf::Vector2f desiredVelocity = this->getShortestPathVector(this->m_position, targetPos).normalized() * this->m_maxSpeed;

	// Calculate the Steering Force
	sf::Vector2f steering = desiredVelocity - this->m_velocity;
	steering = (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
		? steering.normalized() * this->m_maxForce : steering;
	
	// Cacluate the Acceleration (F = ma >> a = F/m)
	this->m_acceleration += steering / this->m_mass;
}

void Boid::flee(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Flee' Movement Behavior." << std::endl;

	// Calculate our Desired Velocity
	sf::Vector2f targetPos = ctx.target.getPosition();
	sf::Vector2f desiredVelocity = this->getShortestPathVector(targetPos, this->m_position).normalized() * this->m_maxSpeed;

	// Calculate the Steering Force
	sf::Vector2f steering = desiredVelocity - this->m_velocity;
	steering = (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
		? steering.normalized() * this->m_maxForce : steering;

	// Cacluate the Acceleration (F = ma >> a = F/m)
	this->m_acceleration += steering / this->m_mass;
}

void Boid::pursue(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Pursue' Movement Behavior." << std::endl;
}

void Boid::evade(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Evade' Movement Behavior." << std::endl;
}

void Boid::wander(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Wander' Movement Behavior." << std::endl;
}

void Boid::arrival(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Arrival' Movement Behavior." << std::endl;

	// Calculate our Desired Velocity
	sf::Vector2f targetPos = ctx.target.getPosition();
	sf::Vector2f desiredVelocity = this->getShortestPathVector(this->m_position, targetPos);

	// Slowing Down Radius (Kinematics Approximation)
	float slowingRadius = (this->m_mass * (this->m_maxSpeed * this->m_maxSpeed)) / (2.0f * this->m_maxForce);
	
	// Check the Distance between the Boid and the Target
	float distance = desiredVelocity.length();
	if (distance < slowingRadius) {
		// Check if it is VERY Close (Prevents Normalisation Errors on Zero-Vectors)
		if (distance < 0.01f) {
			this->m_velocity = sf::Vector2f(0.f, 0.f);
			this->m_acceleration = sf::Vector2f(0.f, 0.f);
			return;
		}

		// Slow Down
		desiredVelocity = desiredVelocity.normalized() * this->m_maxSpeed * (distance / slowingRadius);
	}
	else {
		// Max Desired Velocity
		desiredVelocity = desiredVelocity.normalized() * this->m_maxSpeed;
	}

	// Calculate the Steering Force
	sf::Vector2f steering = desiredVelocity - this->m_velocity;
	steering = (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
		? steering.normalized() * this->m_maxForce : steering;

	// Cacluate the Acceleration (F = ma >> a = F/m)
	this->m_acceleration += steering / this->m_mass;
}

void Boid::flock(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Flock' Movement Behavior." << std::endl;
}

void Boid::leaderFollow(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Leader-Follow' Movement Behavior." << std::endl;
}
