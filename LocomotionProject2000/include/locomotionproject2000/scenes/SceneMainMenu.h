/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : SceneMainMenu.h
Description : Declares the SceneMainMenu Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once

#include "locomotionproject2000/scenes/Scene.h"

/// <summary>
///		The Main Menu Scene class.
/// </summary>
class SceneMainMenu: public Scene {
private:
	// -- Managers -- //

	// -- //

	// -- Main Scene Properties -- //

	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructor.
	/// </summary>
	SceneMainMenu();

	/// <summary>
	///		Destructor.
	/// </summary>
	~SceneMainMenu();

	//==================================================
	// PRIMARY MAIN SCENE METHODS
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
};

