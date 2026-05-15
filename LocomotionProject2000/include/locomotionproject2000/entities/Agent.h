/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Agent.h
Description : Declares the Agent Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

/// <summary>
///		Agent class represents an entity in the world that can perform actions,
///		make decisions, interact with other agents, and interact with the environment.
/// 
///		It serves as the base class for shared agent state, behaviour, and
///		properties such as movement, transforms, and visual representation.
/// 
///		Derived classes can extend this foundation by implementing specialised
///		behaviours, decision-making systems, interaction logic, or movement
///		patterns while reusing the shared functionality provided by the base class.
/// </summary>
class Agent {
protected:
	// -- Agent Transform Properties -- //
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_rotation;
	// -- //

	// -- Agent Movement Properties -- //
	float m_maxSpeed;
	float m_maxForce;
	// -- //

	// -- Agent Rendering Properties -- //
	sf::ConvexShape m_shape;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	Agent() = default;

	/// <summary>
	///     Virtual destructor for safe polymorphic destruction.
	/// </summary>
	virtual ~Agent() = default;

	//==================================================
	// PRIMARY AGENT METHODS
	//==================================================

	/// <summary>
	///		Update the Agent's state, including movement, decision-making, and interactions.
	/// </summary>
	/// 
	/// <param name="dt">Delta Time as a floating-point.</param>
	/// <param name="agents">Reference to a list of all agents in the simulation.</param>
	virtual void update(float dt, const std::vector<Agent>& agents) = 0;

	//==================================================
	// BOID SETTER METHODS
	//==================================================
	
	/// <summary>
	///		Set the Position of the Agent.
	/// </summary>
	/// 
	/// <param name="position">2D Position vector.</param>
	void setPosition(const sf::Vector2f& position) {
		this->m_position = position;
	}

	/// <summary>
	///		Set the Velocity of the Agent.
	/// </summary>
	/// 
	/// <param name="velocity">2D Velocity vector.</param>
	void setVelocity(const sf::Vector2f& velocity) {
		this->m_velocity = velocity;
	}

	/// <summary>
	///		Set the Rotation of the Agent in degrees.
	/// </summary>
	/// 
	/// <param name="rotation">Rotation in degrees.</param>
	void setRotation(float rotation) {
		this->m_rotation = rotation;
	}

	/// <summary>
	///		Set the Maximum Speed of the Agent.
	/// </summary>
	/// 
	/// <param name="maxSpeed">Maximum Speed of the Agent.</param>
	void setMaxSpeed(float maxSpeed) {
		this->m_maxSpeed = maxSpeed;
	}

	/// <summary>
	///		Set the Maximum Force of the Agent.
	/// </summary>
	/// 
	/// <param name="maxForce">Maximum Force that can be applied to the Agent.</param>
	void setMaxForce(float maxForce) {
		this->m_maxForce = maxForce;
	}

	//==================================================
	// BOID GETTERS METHODS
	//==================================================

	/// <summary>
	///		Get the current Position of the Agent.
	/// </summary>
	/// 
	/// <returns>2D Position vector.</returns>
	sf::Vector2f getPosition() const {
		return this->m_position;
	}

	/// <summary>
	///		Get the current Velocity of the Agent.
	/// </summary>
	/// 
	/// <returns>2D Velocity vector.</returns>
	sf::Vector2f getVelocity() const {
		return this->m_velocity;
	}

	/// <summary>
	///		Get the current Rotation of the Agent.
	/// </summary>
	/// 
	/// <returns>Rotation in degrees.</returns>
	float getRotation() const {
		return this->m_rotation;
	}

	/// <summary>
	///		Get the Maximum Speed of the Agent.
	/// </summary>
	/// 
	/// <returns>Maximum Speed of the Agent.	</returns>
	float getMaxSpeed() const {
		return this->m_maxSpeed;
	}
	
	/// <summary>
	///		Get the Maximum Force of the Agent.
	/// </summary>
	/// 
	/// <param name="maxForce">Maximum Force that can be applied to the Agent.</param>
	float getMaxForce() const {
		return this->m_maxForce;
	}

	/// <summary>
	///		Get the Shape of the Agent.
	/// </summary>
	/// 
	/// <returns>Shape of the Agent.</returns>
	sf::ConvexShape getShape() const {
		return this->m_shape;
	}
};