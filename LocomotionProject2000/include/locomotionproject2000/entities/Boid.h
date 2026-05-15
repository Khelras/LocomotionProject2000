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
#include "Agent.h"

class Boid: public Agent {
private:
	// -- Boid Behavior State Properties -- //
	enum class BehaviorState {
		SEEK = 1,
		FLEE = 2,
		PURSUE = 3,
		EVADE = 4,
		WANDER = 5,
		ARRIVAL = 6,
		FLOCK = 7,
		LEADER_FOLLOW = 8
	} m_currentBehavior;
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
	///		Constructor with an initial position.
	/// </summary>
	/// 
	/// <param name="position">Initial position of the Boid.</param>
	Boid(sf::Vector2f position);

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
};