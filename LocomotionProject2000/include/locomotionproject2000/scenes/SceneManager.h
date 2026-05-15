/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : SceneManager.h
Description : Declares the SceneManager Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include <memory>
#include <string>
#include <map>
#include <stack>

#include "locomotionproject2000/scenes/SceneMainMenu.h"
#include "locomotionproject2000/scenes/SceneGameplay.h"

/// <summary>
///		SceneManager class is responsible for managing various scenes and 
/// </summary>
class SceneManager {
private:
	// -- Scene Manager Properties -- //
	std::map<std::string, std::shared_ptr<Scene>> m_sceneRegistry;
	std::stack<std::shared_ptr<Scene>> m_sceneStack;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Constructs the Scene Manager class and registers all the scenes (pre-defined).
	/// </summary>
	SceneManager();

	/// <summary>
	///		Default destructor.
	/// </summary>
	~SceneManager() = default;

	//==================================================
	// PRIMARY SCENE MANAGER METHODS
	//==================================================

	/// <summary>
	///		Handle the given event in relation to the current active scene.
	/// </summary>
	/// 
	/// <param name="event">The raw SFML event.</param>
	/// <param name="ctx">Context information provided for any command execution.</param>
	void handleEvent(const sf::Event& event, const CommandContext& ctx);

	/// <summary>
	///		Update loop for the Scene Manager
	/// </summary>
	/// 
	/// <param name="dt">Delta Time as a floating-point.</param>
	void update(float dt);

	/// <summary>
	///     Renders the current active scene and its contents to the Window.
	/// </summary>
	/// 
	/// <param name="window">Render window target for drawing.</param>
	void render(sf::RenderWindow& window);

	/// <summary>
	///		Get the current active scene.
	/// </summary>
	/// 
	/// <returns>The current active scene as a weak pointer.</returns>
	std::weak_ptr<Scene> getActiveScene();

	/// <summary>
	///		Transition to another scene by a given name.	
	/// </summary>
	/// 
	/// <param name="sceneName"The name of the scene to switch to.></param>
	void goToScene(const std::string& sceneName);
};
