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

void Boid::seek(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Seek' Movement Behavior." << std::endl;

	// -- Simple Straight-Line Movement -- //
	// Forward Direction Vector from the Rotation
	float radians = this->m_rotation.asRadians();
	sf::Vector2f forward(std::cosf(radians), std::sinf(radians));

	// Velocity Vector
	this->m_velocity = forward * this->m_maxSpeed;

	// Apply the Velocity Vector and Perform Movement
	this->m_position += this->m_velocity * ctx.dt;
	// -- //
}

void Boid::flee(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Flee' Movement Behavior." << std::endl;
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
}

void Boid::flock(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Flock' Movement Behavior." << std::endl;
}

void Boid::leaderFollow(AgentUpdateContext ctx) {
	// DEBUG
	std::cout << "Performing 'Leader-Follow' Movement Behavior." << std::endl;
}
