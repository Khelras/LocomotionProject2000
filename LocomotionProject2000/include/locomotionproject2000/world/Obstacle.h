/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Obstacle.h
Description : Declares the Obstacle Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>

// Simple Obstacle Class
class Obstacle {
private:
	// -- Obstacle Properties -- //
	sf::Vector2f m_position;
	sf::CircleShape m_shape;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Default Constructor.
	/// </summary>
	Obstacle();

	/// <summary>
	///		Constructor with an initial position.
	/// </summary>
	/// 
	/// <param name="position">Initial 2D position vector.</param>
	Obstacle(sf::Vector2f position);

	/// <summary>
	///		Default Destructor.
	/// </summary>
	~Obstacle();

	//==================================================
	// OBSTACLE GETTER METHODS
	//==================================================

	/// <summary>
	///		Get the Position of the Obstacle.
	/// </summary>
	/// 
	/// <returns>2D Position vector of the Agent</returns>
	sf::Vector2f getPosition() const;

	/// <summary>
	///		Get the Shape of the Obstacle.
	/// </summary>
	/// <returns>2D Circle Shape of the Obstacle.</returns>
	sf::CircleShape getShape() const;

	//==================================================
	// OBSTACLE SETTER METHODS
	//==================================================

	/// <summary>
	///		Set the Position of the Obstacle.
	/// </summary>
	/// <param name="position">2D Position vector.</param>
	void setPosition(sf::Vector2f position);
};