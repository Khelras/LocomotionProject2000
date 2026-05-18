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

#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

#include "locomotionproject2000/entities/Boid.h"
#include "locomotionproject2000/core/Settings.h"

Boid::Boid() {
	// Default Properties
	this->m_currentBehaviour = BehaviourState::NONE;
	this->m_wanderAngle = 0.0f;

	// Object Avoidance Properties
	this->m_detectionRadius = 300.0f;
	this->m_detectionLength = 0.0f;
	this->m_detectionWidth = 0.0f;
	
	// Group Behaviours Properties
	this->m_desiredSeparation = 50.0f;
	this->m_neighbourDistance = 200.0f;
}

Boid::Boid(sf::Vector2f position, BehaviourState movementBehaviour) : Boid() {
	// Shape of the Boid
	std::unique_ptr<sf::ConvexShape> convex = std::make_unique<sf::ConvexShape>(4);
	convex->setPoint(0, sf::Vector2f(20.0f, 0.0f)); // Tip
	convex->setPoint(1, sf::Vector2f(-10.0f, 10.0f)); // Back-Left
	convex->setPoint(2, sf::Vector2f(-5.0f, 0.0f)); // Back-Middle
	convex->setPoint(3, sf::Vector2f(-10.0f, -10.0f)); // Back-Right
	convex->setOrigin(sf::Vector2f(0.0f, 0.0f));
	convex->setFillColor(sf::Color::White);
	this->m_shape = std::move(convex);
	this->m_shape->setScale(sf::Vector2f(0.8f, 0.8f));

	// Width of the Detection Box of the Boid (From the Back two Points of the Boid)
	this->m_detectionWidth = (this->m_shape->getPoint(1) - this->m_shape->getPoint(3)).length() * 1.5f; // Extra for Safety

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
		case BehaviourState::SEEK: this->seek(ctx); break; // Seek Movement Behaviour
		case BehaviourState::FLEE: this->flee(ctx); break; // Flee Movement Behaviour
		case BehaviourState::WANDER: this->wander(ctx); break; // Wander Movement Behaviour
		case BehaviourState::ARRIVAL: this->arrival(ctx); break; // Arrival Movement Behaviour
		case BehaviourState::FLOCK: this->flock(ctx); break; // Flock Movement Behaviour
		case BehaviourState::LEADER_FOLLOW: this->leaderFollow(ctx); break; // Follow the Leader Movement Behaviour
		default: { // Default
			// Stop
			this->m_velocity = sf::Vector2f(0.0f, 0.0f);
		} break; 
	}

	// Detect Nearby Obstacles
	this->m_nearbyObstacles.clear();
	std::queue<Obstacle> obstacles = ctx.obstacles;
	while (obstacles.empty() == false) {
		// Get the first Obstacle in the Queue
		Obstacle obstacle = obstacles.front();

		// Check if this Obstacle is within the Detection Radius
		float within = this->m_detectionRadius + obstacle.getShape().getRadius();
		float distance = (obstacle.getPosition() - this->m_position).length();
		if (distance <= within) {
			// Obstacle is Nearby
			this->m_nearbyObstacles.push_back(obstacle);
		}

		// Pop it out
		obstacles.pop();
	}

	// Forward and Right Vectors for Local Space of boids
	sf::Vector2f forward = (this->m_velocity.lengthSquared() == 0.0f) ? sf::Vector2f(1.0f, 0.0f) : this->m_velocity.normalized();
	sf::Vector2f right = forward.perpendicular();

	// Calculate the Detection Length based on the a total Speed Percentage of Max Speed
	float detectionLengthMin = 50.0f; // 50 Minimum
 	float detectionLengthMax = 300.0f; // 300 Maximum
	float speedPercentage = this->m_velocity.length() / this->m_maxSpeed;
	this->m_detectionLength = detectionLengthMin + speedPercentage * (detectionLengthMax - detectionLengthMin);

	// Loop through all Nearby Obstacles
	for (const Obstacle& obstacle : this->m_nearbyObstacles) {
		// Calculate the Relative Position of the Obstacle to the Boid
		sf::Vector2f toObstacle = obstacle.getPosition() - this->m_position;

		// Project the Obstacle to the Local Space of the Boid
		sf::Vector2f local; // Local Space of the Boid
		local.x = toObstacle.dot(forward);
		local.y = toObstacle.dot(right);

		// Ignore Obstacles behind the Boid
		if (local.x < 0) continue;

		// Ignore Obstalces further than the Length of the Detection Box
		if (local.x > this->m_detectionLength) continue; 

		// Using the Width of the Detection Box to see if this Obstacle will Intersect the Boid
		float obstacleExpandedRadius = obstacle.getShape().getRadius() + this->m_detectionWidth / 2.0f;
		if (std::abs(local.y) > obstacleExpandedRadius) continue;

		// Cacluate the Side to Steer towards and the Forward Factor
		float side = (local.y > 0) ? -1.0f : 1.0f;
		float forwardFactor = 1.0f - (local.x / this->m_detectionLength);
		forwardFactor = std::clamp(forwardFactor , 0.0f, 1.0f);

		// Calculate the Lateral Force
		float overlap = obstacleExpandedRadius - std::abs(local.y);
		float lateralForce = overlap * forwardFactor * this->m_maxForce; // scaled!
		sf::Vector2f lateralForceLocal(0, side * lateralForce * local.x);

		// Calculate the Braking Force
		float brakingFactor = 1.0f - (local.x / this->m_detectionLength);
		brakingFactor = std::clamp(brakingFactor, 0.f, 1.f);
		sf::Vector2f brakeLocal(-this->m_velocity.length() * brakingFactor , 0);

		// Combine the Lateral and Breaking Force and bring it back to the World
		sf::Vector2f totalLocal = lateralForceLocal + brakeLocal;
		sf::Vector2f totalWorld = forward * totalLocal.x + right * totalLocal.y;

		// Max Steering Force Specific to Object Avoidance
		float maxSteeringForce = this->m_maxSpeed * 3.0f; // 3x more than Max Speed

		// Calculate the Final Steering Force
		sf::Vector2f steering = totalWorld;
		steering = (steering.lengthSquared() > maxSteeringForce * maxSteeringForce)
			? steering.normalized() * maxSteeringForce : steering;

		// Cacluate the Acceleration (F = ma >> a = F/m)
		this->m_acceleration += steering / this->m_mass; // consistent with seek
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

	// Update the Shape Angle of the Boid
	//sf::Vector2f forward = (this->m_velocity.lengthSquared() == 0.0f) ? sf::Vector2f(1.0f, 0.0f) : this->m_velocity.normalized();
	sf::Angle angle = sf::radians(std::atan2f(forward.y, forward.x));
	this->m_shape->setRotation(angle);

	// Lastly, Update the Transform Properties of the Shape
	this->m_shape->setPosition(this->m_position);
	this->m_acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Boid::draw(sf::RenderWindow& window) {
	// Draw the Boid
	window.draw(*this->m_shape.get());

	// -- DEBUG Drawings -- //
	if (Settings::getInstance().shouldDrawDebugs == true) {
		// Detection Length Line (Forward Ray)
		sf::Vector2f forward = (this->m_velocity.lengthSquared() == 0.0f) ? sf::Vector2f(1.0f, 0.0f) : this->m_velocity.normalized();
		sf::Vector2f lineEnd = this->m_position + forward * this->m_detectionLength; // End of Line

		// Construct the Line
		sf::VertexArray line(sf::PrimitiveType::LineStrip, 2);
		sf::Color lineColor = sf::Color(0, 255, 0, 200);
		line[0].position = this->m_position; // Start
		line[0].color = lineColor;
		line[1].position = lineEnd; // End
		line[1].color = lineColor;

		// Draw the Line
		window.draw(line);
	}
	// -- //
}

void Boid::setMovementBehaviour(BehaviourState movementBehaviour) {
	this->m_currentBehaviour = movementBehaviour;
}