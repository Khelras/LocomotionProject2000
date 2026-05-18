/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Target.h
Description : Declares the Target Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include "Boid.h"

class Target: public Agent {
private:
	// -- Target Properties -- //
	BehaviourState m_currentBehaviour;
	float m_wanderAngle;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor
	/// </summary>
	Target();

	/// <summary>
	///		Default Destructor.
	/// </summary>
	~Target();

	//==================================================
	// PRIMARY TARGET METHODS
	//==================================================

	/// <summary>
	///		Update the Target's state, including movement, decision-making, and interactions.
	/// </summary>
	/// 
	/// <param name="ctx">Revelant context for the update process.</param>
	void update(AgentUpdateContext ctx) override;

	/// <summary>
	///		Draw the Target to the given Window.
	/// </summary>
	/// 
	/// <param name="window">Reference to the SFML Render Window.</param>
	void draw(sf::RenderWindow& window) override;

	/// <summary>
	///		Get the Movement Behaviour State of the Target.
	/// </summary>
	/// <returns></returns>
	BehaviourState getMovementBehaviour() const;

	/// <summary>
	///		Set the Movement Behaviour State of the Target.
	/// </summary>
	/// 
	/// <param name="movementBehaviour">Movement Behaviour State.</param>
	void setMovementBehaviour(BehaviourState movementBehaviour);
};