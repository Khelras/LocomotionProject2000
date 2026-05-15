/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Obstacle.cpp
Description : Defines the Obstacle Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/world/Obstacle.h"

Obstacle::Obstacle() {
	// Default Properties
	this->m_position = sf::Vector2f(0.0f, 0.0f);
	this->m_shape.setPosition(this->m_position);
	this->m_shape.setRadius(20);
	this->m_shape.setFillColor(sf::Color::Red);
}

Obstacle::Obstacle(sf::Vector2f position) : Obstacle() {
	// Set the Position of the Obstacle
	this->m_position = position;
	this->m_shape.setPosition(position);
}

Obstacle::~Obstacle() {
}

sf::Vector2f Obstacle::getPosition() const {
	return this->m_position;
}

sf::CircleShape Obstacle::getShape() const {
	return this->m_shape;
}

void Obstacle::setPosition(sf::Vector2f position) {
	this->m_position = position;
	this->m_shape.setPosition(position);
}
