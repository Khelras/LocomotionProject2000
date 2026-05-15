/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : Window.h
Description : Declares the Window Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include "locomotionproject2000/scenes/SceneManager.h"

/// <summary>
///		Window class inherits from SFML's RenderWindow class which allows for easy Window processing within it's own class.
/// </summary>
class Window : public sf::RenderWindow {
private:
	// -- Managers -- //
	SceneManager m_sceneManager;
	// -- //

	// -- Window Properties -- //
	sf::Vector2u m_resolution;
	// -- //

public:
	//==================================================
	// CONSTRUCTOR AND DESTRUCTOR
	//==================================================

	/// <summary>
	///		Construct an SFML RenderWindow using the default video mode and window name specified
	///		within the default constructor.
	/// </summary>
	Window();

	/// <summary>
	///		Construct an SFML RenderWindow with a specified video mode and window name.
	/// </summary>
	/// 
	/// <param name="mode">Define the video resolution of the Window.</param>
	/// <param name="name">Window name or title.</param>
	Window(sf::VideoMode mode, const std::string& name);

	/// <summary>
	///		Destructor.
	/// </summary>
	~Window();

	//==================================================
	// PRIMARY WINDOW METHODS
	//==================================================

	/// <summary>
	///		Primary process loop of the Window and the whole application.
	/// </summary>
	void process();

	/// <summary>
	///		Clear the back buffer. The back buffer can be cleared to a specified background color.
	/// </summary>
	void clear();

	/// <summary>
	///		Draw and render objects to the back buffer.
	/// </summary>
	void draw();

	/// <summary>
	///		Swap buffers and display the back buffer.
	/// </summary>
	void display();
};

