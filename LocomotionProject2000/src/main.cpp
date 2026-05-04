/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2025 Media Design School
File Name   : main.cpp
Description : The Main Thread. Starts and Executes the Locomotion Project 2000 SFML Application.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/core/Window.h"

int main() {
	// Create a Window
	Window window;

	// Start the Window's main process loop
	window.process();

	// Done
	return 0;
}