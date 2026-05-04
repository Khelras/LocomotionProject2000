/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name   : Scene.h
Description : Declares and Defines the Scene Base Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "locomotionproject2000/core/Command.h"

/// <summary>
///     Base Scene class representing a self-contained state of the application.
///     A Scene groups together elements such as objects, UI, logic, and assets relevant to that state of the application.
///     Each Scene defines their own update and rendering loop based on their group of elements.
/// </summary>
class Scene {
protected:
    // -- Scene Properties -- //
    std::vector<Command> m_commands;
    // -- //

public:
    //==================================================
    // CONSTRUCTOR AND DESTRUCTOR
    //==================================================

    /// <summary>
    ///     Constructor.
    /// </summary>
    Scene() = default;

    /// <summary>
    ///     Virtual destructor for safe polymorphic destruction.
    /// </summary>
    virtual ~Scene() = default;

    //==================================================
    // PRIMARY BASE SCENE METHODS
    //==================================================

    /// <summary>
    ///     Called when the scene is first created or entered.
    ///     Use for initialization.
    /// </summary>
    virtual void onEnter() {};

    /// <summary>
    ///     Called when the Scene is being exited or replaced.
    ///     Use for cleanup upon exiting.
    /// </summary>
    virtual void onExit() {};

    /// <summary>
    ///     Check the given event against all Commands and their execution criterias.
    /// </summary>
    /// 
    /// <param name="event">The raw SFML event.</param>
    /// <param name="ctx">Context information provided for command execution.</param>
    virtual void handleEvent(const sf::Event& event, const CommandContext& ctx) = 0;

    /// <summary>
    ///     Updates scene logic.
    /// </summary>
    /// 
    /// <param name="dt">Delta Time as a floating-point.</param>
    virtual void update(float dt) = 0;

    /// <summary>
    ///     Renders scene contents to the Window.
    /// </summary>
    /// 
    /// <param name="window">Render target for drawing.</param>
    virtual void draw(sf::RenderWindow& window) = 0;
};

