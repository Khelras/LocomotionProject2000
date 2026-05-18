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

void Boid::wander(AgentUpdateContext ctx) {
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
	std::uniform_real_distribution<float> dis(-1.0f, 1.0f); // RNG from -1.0f to 1.0f (Floating-Point Inclusive)
	this->m_wanderAngle += dis(this->m_rng) * wanderJitter; // Scale the RNG with the Wander Jitter for the new Wander Angle

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
}


void Boid::arrival(AgentUpdateContext ctx) {
	// Calculate our Desired Velocity
	sf::Vector2f targetPos = ctx.target.getPosition();
	sf::Vector2f desiredVelocity = this->getShortestPathVector(this->m_position, targetPos);

	// Calculate Slowing Down Radius (Kinematics Approximation)
	float slowingRadius = (this->m_mass * (this->m_maxSpeed * this->m_maxSpeed)) / (2.0f * this->m_maxForce);
	
	// Check the Distance between the Boid and the Target
	float distance = desiredVelocity.length();
	if (distance < slowingRadius) {
		// Check if it is VERY Close (Prevents Normalisation Errors on Zero-Vectors)
		if (distance < 0.01f) {
			this->m_velocity = sf::Vector2f(0.f, 0.f);
			//this->m_acceleration = sf::Vector2f(0.f, 0.f);
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
	// Wander as the Base Locomotion
	this->wander(ctx);

	sf::Vector2f seperationForce = this->separation(ctx);
	sf::Vector2f alignmentForce = this->alignment(ctx);
	sf::Vector2f cohesionForce = this->cohesion(ctx);

	// Weights
	seperationForce *= 2.4f;
	alignmentForce *= 1.2f;
	cohesionForce *= 2.0f;

	// Apply the Force
	this->m_acceleration += seperationForce / this->m_mass;
	this->m_acceleration += alignmentForce / this->m_mass;
	this->m_acceleration += cohesionForce / this->m_mass;
}

void Boid::leaderFollow(AgentUpdateContext ctx) {
	// Weights
	float arriveForceWeight = 1.5f;
	float evadeForceWeight = 5.0f;
	float separationForceWeight = 1.2f;

	// -- Arrival Behaviour Movement -- //
	// Get the Forward Vector of the Target Leader
	sf::Vector2f leaderVelocity = ctx.target.getVelocity(); 
	sf::Vector2f leaderForward = (leaderVelocity.lengthSquared() == 0.0f) ? sf::Vector2f(1.0f, 0.0f) : leaderVelocity.normalized();

	// Calculate the "Behind" offset Point from the Target Leader
	float behindDistance = ctx.target.getLeadingBehindOffset();
	sf::Vector2f behindPoint = ctx.target.getPosition() - leaderForward * behindDistance;

	// Arrive at the Behind Point and NOT the Target Leader
	sf::Vector2f desiredVelocity = this->getShortestPathVector(this->m_position, behindPoint);

	// Calculate Slowing Down Radius (Kinematics Approximation)
	float slowingRadius = (this->m_mass * (this->m_maxSpeed * this->m_maxSpeed)) / (2.0f * this->m_maxForce);

	// Check if Boid is within the Slowing Down Radius
	float distance = desiredVelocity.length();
	if (distance < slowingRadius) {
		// Small Distance
		if (distance < 0.01f) {
			// Come to a Stop
			this->m_velocity = sf::Vector2f(0.f, 0.f);
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

	// Apply the Arrival Steering Force
	this->m_acceleration += (steering * arriveForceWeight) / this->m_mass;
	// -- //
	


	// -- Evasion Behaviour Movement -- //
	// Calculate the Distance from the Boid to the Leader
	sf::Vector2f leaderPos = ctx.target.getPosition();
	float distanceToLeader = this->getShortestPathVector(this->m_position, leaderPos).length();

	// Calculate the Evasion Radius
	float evadeRadius = ctx.target.getLeadingBehindOffset() * 4.0f;

	// Check if the Distance to the Leader is within the Evasion Radius
	if (distanceToLeader < evadeRadius) {
		// Predict where the Leader will be
		float lookAhead = distanceToLeader / this->m_maxSpeed;
		sf::Vector2f predicted = leaderPos + leaderVelocity * lookAhead;

		// Flee from taht Predicted Position
		sf::Vector2f evadeDesired = this->getShortestPathVector(predicted, this->m_position).normalized() * this->m_maxSpeed;
		sf::Vector2f evadeSteering = evadeDesired - this->m_velocity;
		evadeSteering = (evadeSteering.lengthSquared() > this->m_maxForce * this->m_maxForce)
			? evadeSteering.normalized() * this->m_maxForce : evadeSteering;

		// Apply the Evade Steering Force
		this->m_acceleration += (evadeSteering * evadeForceWeight) / this->m_mass;
	}
	// -- //



	// -- Separation Steering Force -- //
	sf::Vector2f separationForce = this->separation(ctx);
	this->m_acceleration += (separationForce * separationForceWeight) / this->m_mass;
	// -- //
}

sf::Vector2f Boid::separation(AgentUpdateContext ctx) {
	sf::Vector2f steering(0.0f, 0.0f);
	int count = 0;
	for (const auto& other : ctx.agents) {
		// Ensure Other is not Itself
		if (other.get() == this) continue;

		// Calculate the Distance between Other and This
		sf::Vector2f toOther = this->getShortestPathVector(this->m_position, other->getPosition());
		float distance = toOther.length();

		// Check if the Distance is lesser than the Desired Separation
		if (distance < this->m_desiredSeparation && distance > 0.0f) {
			sf::Vector2f difference = -this->getShortestPathVector(this->m_position, other->getPosition());
			difference = difference.normalized();
			difference /= distance;
			steering += difference;
			count++;
		}
	}

	if (count > 0) steering /= static_cast<float>(count);

	if (steering.length() > 0.0f) {
		steering = steering.normalized() * this->m_maxSpeed;
		steering -= this->m_velocity;
		return steering = (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
			? steering.normalized() * this->m_maxForce : steering;
	}

	// Otherwise, Return a Zero Vector
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f Boid::alignment(AgentUpdateContext ctx) {
	sf::Vector2f sum(0.0f, 0.0f);
	int count = 0;
	for (const auto& other : ctx.agents) {
		// Ensure Other is not Itself
		if (other.get() == this) continue;

		// Calculate the Distance between Other and This
		float distance = (other->getPosition() - this->m_position).length();

		// Check if the Calculated Distance is within the Neighbour Distance
		if (distance < this->m_neighbourDistance) {
			sum += other->getVelocity();
			count++;
		}
	}

	if (count > 0) {
		sum /= static_cast<float>(count);
		sum = (sum.lengthSquared() == 0.0f) ? sum : sum.normalized() * this->m_maxSpeed;

		// Calculate the Steering Force
		sf::Vector2f steering = sum - this->m_velocity;
		return steering = (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
			? steering.normalized() * this->m_maxForce : steering;
	}

	// Otherwise, Return a Zero Vector
	return sf::Vector2f(0.0f, 0.0f);
}

sf::Vector2f Boid::cohesion(AgentUpdateContext ctx) {
	sf::Vector2f sum(0.0f, 0.0f);
	int count = 0;
	for (const auto& other : ctx.agents) {
		// Ensure Other is not Itself
		if (other.get() == this) continue;

		// Calculate the Distance between Other and This
		sf::Vector2f toOther = this->getShortestPathVector(this->m_position, other->getPosition());
		float distance = toOther.length();

		// Check if the Calculated Distance is within the Neighbour Distance
		if (distance < this->m_neighbourDistance) {
			sum += toOther; // accumulate OFFSET vectors, not world positions
			count++;
		}
	}

	if (count > 0) {
		// Calculate the Average offset from THIS Boid
		sum /= static_cast<float>(count);

		// Seek Center
		sf::Vector2f desired = sum;
		desired = (desired.lengthSquared() == 0.0f) ? desired : desired.normalized() * this->m_maxSpeed;

		sf::Vector2f steering = desired - this->m_velocity;
		return (steering.lengthSquared() > this->m_maxForce * this->m_maxForce)
			? steering.normalized() * this->m_maxForce : steering;
	}

	return sf::Vector2f(0.f, 0.f);
}