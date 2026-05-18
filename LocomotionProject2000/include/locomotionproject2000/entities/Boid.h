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

#pragma once
#include <random>

#include "Agent.h"
#include "locomotionproject2000/world/Obstacle.h"

/// <summary>
///		Movement Behaviour States of the Boids.
/// </summary>
enum class BehaviourState {
	NONE = 0,
	SEEK = 1,
	FLEE = 2,
	WANDER = 3,
	ARRIVAL = 4,
	FLOCK = 5,
	LEADER_FOLLOW = 6
};

class Boid: public Agent {
private:
	// -- Boid Properties -- //
	BehaviourState m_currentBehaviour;
	float m_wanderAngle;
	// -- //

	// -- Boid Object Avoidance Properties -- // 
	float m_detectionRadius;
	float m_detectionLength;
	float m_detectionWidth;
	std::vector<Obstacle> m_nearbyObstacles;
	// -- //

	// -- Boid Group Behaviour Properties -- // 
	float m_desiredSeparation;
	float m_neighbourDistance;
	// -- // 

	// -- Other -- // 
	std::mt19937 m_rng{ std::random_device{}() };
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor.
	/// </summary>
	Boid();

	/// <summary>
	///		Constructor with an initial position and movement behaviour.
	/// </summary>
	/// 
	/// <param name="position">Initial 2D position vector.</param>
	/// <param name="movementBehaviour">Initial Movement Behaviour.</param>
	Boid(sf::Vector2f position, BehaviourState movementBehaviour);

	/// <summary>
	///     Destructor.
	/// </summary>
	~Boid();

	//==================================================
	// PRIMARY BOID METHODS
	//==================================================

	/// <summary>
	///		Update the Boid's state, including movement, decision-making, and interactions.
	/// </summary>
	/// 
	/// <param name="ctx">Revelant context for the update process.</param>
	void update(AgentUpdateContext ctx) override;

	/// <summary>
	///		Draw the Boid to the given Window.
	/// </summary>
	/// 
	/// <param name="window">Reference to the SFML Render Window.</param>
	void draw(sf::RenderWindow& window) override;

	/// <summary>
	///		Set the Movement Behaviour State of the Boid.
	/// </summary>
	/// 
	/// <param name="movementBehaviour">Movement Behaviour State.</param>
	void setMovementBehaviour(BehaviourState movementBehaviour);

private:
	//==================================================
	// BOID MOVEMENT BEHAVIOUR METHODS
	//==================================================

	/// <summary>
	///		Seek Movement Behaviour.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	void seek(AgentUpdateContext ctx);

	/// <summary>
	///		Flee Movement Behaviour.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	void flee(AgentUpdateContext ctx);

	/// <summary>
	///		Wander Movement Behaviour.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	void wander(AgentUpdateContext ctx);

	/// <Arrival>
	///		Flee Movement Behaviour.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	void arrival(AgentUpdateContext ctx);

	/// <summary>
	///		Flock Movement Behaviour.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	void flock(AgentUpdateContext ctx);

	/// <summary>
	///		Follow the Leader Movement Behaviour.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	void leaderFollow(AgentUpdateContext ctx);

	//==================================================
	// BOID MOVEMENT BEHAVIOUR HELPER METHODS
	//==================================================

	/// <summary>
	///		Get the Separation Steering Force.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	/// 
	/// <returns>
	///		2D Separation Steering Force Vector.
	/// </returns>
	sf::Vector2f separation(AgentUpdateContext ctx);

	/// <summary>
	///		Get the Alignment Steering Force.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	/// 
	/// <returns>
	///		2D Alignment Steering Force Vector.
	/// </returns>
	sf::Vector2f alignment(AgentUpdateContext ctx);

	/// <summary>
	///		Get the Cohesion Steering Force.
	/// </summary>
	/// 
	/// <param name="ctx">Agent Update Context struct that holds relevant information.</param>
	/// 
	/// <returns>
	///		2D Cohesion Steering Force Vector.
	/// </returns>
	sf::Vector2f cohesion(AgentUpdateContext ctx);
};