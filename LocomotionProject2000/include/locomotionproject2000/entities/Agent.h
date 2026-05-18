/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Agent.h
Description : Declares and Defines the Agent Base Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <memory>
#include <utility>

#include "locomotionproject2000/core/Settings.h"

// Relevate Forward-Declared Classes for the AgentUpdateContext struct
class Target;
class Agent;
class Obstacle;

/// <summary>
///		Context required for the Agent's update() function.
/// </summary>
struct AgentUpdateContext {
	/// <summary>
	///		Delta Time as a floating-point.
	/// </summary>
	float dt;

	/// <summary>
	///		A reference to the Target
	/// </summary>
	const Target& target;

	/// <summary>
	///		A reference to a list of Agents.
	/// </summary>
	const std::vector<std::unique_ptr<Agent>>& agents;

	/// <summary>
	///		A reference to a list of Obstacles.
	/// </summary>
	const std::queue<Obstacle>& obstacles;
};



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
	// -- Agent Movement Properties -- 
	sf::Vector2f m_position{ 0.0f, 0.0f };
	sf::Vector2f m_velocity{ 0.0f, 0.0f };
	sf::Vector2f m_acceleration{ 0.0f, 0.0f };
	float m_mass{ 1.0f };
	float m_maxSpeed{ 150.0f };
	float m_maxForce{ 100.0f };
	// -- //

	// -- Agent Rendering Properties -- //
	std::unique_ptr<sf::Shape> m_shape;
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
	

	/// <summary>
	///		Update the Agent's state including movement, decision-making, and interactions.
	/// </summary>
	/// 
	/// <param name="ctx">Revelant context for the update process.</param>
	virtual void update(AgentUpdateContext ctx) = 0;

	/// <summary>
	///		Draw the Agent to the given Window.
	/// </summary>
	/// 
	/// <param name="window">Reference to the SFML Render Window.</param>
	virtual void draw(sf::RenderWindow& window) = 0;

	//==================================================
	// AGENT GETTERS METHODS
	//==================================================

	/// <summary>
	///		Get the current Position of the Agent.
	/// </summary>
	/// 
	/// <returns>2D Position vector of the Agent.</returns>
	sf::Vector2f getPosition() const {
		return this->m_position;
	}

	/// <summary>
	///		Get the current Velocity of the Agent.
	/// </summary>
	/// 
	/// <returns>2D Velocity vector of the Agent.</returns>
	sf::Vector2f getVelocity() const {
		return this->m_velocity;
	}

	/// <summary>
	///		Get the current Acceleration of the Agent.
	/// </summary>
	/// 
	/// <returns>2D Acceleration vector of the Agent.</returns>
	sf::Vector2f getAcceleration() const {
		return this->m_acceleration;
	}

	/// <summary>
	///		Get the Mass of the Agent.
	/// </summary>
	/// 
	/// <returns>Mass of the Agent.</returns>
	float getMass() const {
		return this->m_mass;
	}

	/// <summary>
	///		Get the Maximum Speed of the Agent.
	/// </summary>
	/// 
	/// <returns>Maximum Speed of the Agent.</returns>
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
	/// <returns>2D Shape of the Agent.</returns>
	sf::Shape* getShape() const {
		return this->m_shape.get();
	}

	//==================================================
	// AGENT SETTER METHODS
	//==================================================
	
	/// <summary>
	///		Set the Position of the Agent.
	/// </summary>
	/// 
	/// <param name="position">2D Position vector.</param>
	void setPosition(const sf::Vector2f& position) {
		this->m_position = position;
		this->m_shape->setPosition(position);
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
	///		Set the Acceleration of the Agent
	/// </summary>
	/// 
	/// <param name="acceleration">2D Acceleration vector.</param>
	void setAcceleration(const sf::Vector2f& acceleration) {
		this->m_acceleration = acceleration;
	}

	/// <summary>
	///		Set the Mass of the Agent.
	/// </summary>
	/// 
	/// <param name="mass">Mass of the Agent</param>
	void setMass(const float& mass) {
		this->m_mass = mass;
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

protected:
	//==================================================
	// AGENT HELPER METHODS
	//==================================================

	/// <summary>
	///		Get the Shortest "To and From" while accounting
	///		for Border-Wrapping as a Traversal method.
	/// </summary>
	/// 
	/// <returns>Shortest Path Vector.</returns>
	sf::Vector2f getShortestPathVector(const sf::Vector2f& from, const sf::Vector2f& to) {
		// Difference between To and From
		sf::Vector2f shortestPath = to - from;

		// Border-Wrapping Dimenions
		float screenWidth = static_cast<float>(Settings::getInstance().windowWidth);
		float screenHeight = static_cast<float>(Settings::getInstance().windowHeight);

		// -- X-Axis Wrapping -- //
		// Check if Euclidean Distance is Greater than Half of the Screen Width (Un-ideal form fo Travel)
		if (std::abs(shortestPath.x) > (screenWidth / 2.0f)) {
			// "To" is to the Right of "From"
			if (shortestPath.x > 0.0f) {
				// Therefore, "From" will Travel Left (into the Border and Wrap around) to reach "To"
				shortestPath.x -= screenWidth;
			}
			// "To" is to the Left of "From"
			else {
				// Therefore, "From" will Travel Right (into the Border and Wrap around) to reach "To"
				shortestPath.x += screenWidth;
			}
		}
		// -- //

		// -- Y-Axis Wrapping -- //
			// Check if Euclidean Distance is Greater than Half of the Screen Height (Un-ideal form fo Travel)
		if (std::abs(shortestPath.y) > (screenHeight / 2.0f)) {
			// "To" is Below of "From"
			if (shortestPath.y > 0.0f) {
				// Therefore, "From" will Travel Upwards (into the Border and Wrap around) to reach "To"
				shortestPath.y -= screenHeight;
			}
			// "To" is Above of "From"
			else {
				// Therefore, "From" will Travel Downwards (into the Border and Wrap around) to reach "To"
				shortestPath.y += screenHeight;
			}
		}
		// -- //

		// Return the Ideal Traveling Vector
		return shortestPath;
	}
};