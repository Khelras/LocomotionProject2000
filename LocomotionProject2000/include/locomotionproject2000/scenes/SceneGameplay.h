/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : SceneGameplay.h
Description : Declares the SceneGameplay Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once

#include "Scene.h"
#include "locomotionproject2000/entities/Target.h"
#include "locomotionproject2000/world/Obstacle.h"

/// <summary>
///		The Gameplay Scene class.
/// </summary>
class SceneGameplay: public Scene {
private:
	// -- Managers -- //

	// -- //

	// -- Gameplay Scene Properties -- //
	BehaviourState m_currentBehaviour;
	Target m_target;
	std::vector<std::unique_ptr<Agent>> m_agents;
	std::vector<Obstacle> m_obstacles;
	// -- //

	// -- Gameplay Scene UI -- //
	sf::Font m_font;
	std::unique_ptr<sf::Text> m_targetModeText;
	std::unique_ptr<sf::Text> m_boidMovementStateText;
	std::unique_ptr<sf::Text> m_boidTotalText;
	std::unique_ptr<sf::Text> m_obstacleTotalText;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	SceneGameplay();

	/// <summary>
	///		Destructor.
	/// </summary>
	~SceneGameplay();

	//==================================================
	// PRIMARY GAMEPLAY SCENE METHODS
	//==================================================

	/// <summary>
	///     Check the given event against all Commands and their execution criterias.
	/// </summary>
	/// 
	/// <param name="event">The raw SFML event.</param>
	/// <param name="ctx">Context information provided for command execution.</param>
	void handleEvent(const sf::Event& event, const CommandContext& ctx) override;

	/// <summary>
	///     Updates scene logic.
	/// </summary>
	/// 
	/// <param name="dt">Delta Time as a floating-point.</param>
	void update(float dt) override;

	/// <summary>
	///     Renders scene contents to the Window.
	/// </summary>
	/// 
	/// <param name="window">Render target for drawing.</param>
	void draw(sf::RenderWindow& window) override;

private:
	//==================================================
	// GAMEPLAY SCENE HELPER METHODS
	//==================================================

	/// <summary>
	///		Update the UI.
	/// </summary>
	void updateUI();
};

