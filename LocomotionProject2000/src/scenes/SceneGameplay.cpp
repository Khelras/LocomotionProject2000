/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2026 Media Design School
File Name   : SceneGameplay.cpp
Description : Defines the SceneGameplay Class Functions and Properties.
Author      : Angelo Joseph Arawiran Bohol
Mail        : angelo.bohol@mds.ac.nz
**************************************************************************/

#include "locomotionproject2000/scenes/SceneGameplay.h"
#include "locomotionproject2000/core/Settings.h"

SceneGameplay::SceneGameplay() {
	// Background Color
	this->m_backgroundColor = sf::Color::Black;

	// Center the Target
	float centerX = static_cast<float>(Settings::getInstance().windowWidth) / 2.0f;
	float centerY = static_cast<float>(Settings::getInstance().windowHeight) / 2.0f;
	this->m_target.setPosition(sf::Vector2f(centerX, centerY));

	// Default Movement Behaviour
	this->m_currentBehaviour = BehaviourState::NONE;

	// UI
	if (this->m_font.openFromFile("assets/fonts/arial.ttf")) {
		// Text Attributes
		unsigned int fontSize = 25;
		float textMargin = 10.0f;
		sf::Vector2f textPos(0.0f, 0.0f);
		textPos.x += textMargin;

		// Load the Target Mode Text
		this->m_targetModeText = std::make_unique<sf::Text>(this->m_font);
		this->m_targetModeText->setCharacterSize(fontSize);
		this->m_targetModeText->setString("Target Mode: ...");
		textPos.y += textMargin;
		this->m_targetModeText->setPosition(textPos);

		// Load the Boid Movement State Text
		this->m_boidMovementStateText = std::make_unique<sf::Text>(this->m_font);
		this->m_boidMovementStateText->setCharacterSize(fontSize);
		this->m_boidMovementStateText->setString("Boid Movement Behaviour State: ...");
		textPos.y += this->m_targetModeText->getLocalBounds().size.y + textMargin;
		this->m_boidMovementStateText->setPosition(textPos);
		
		// Load the Boid Total Text
		this->m_boidTotalText = std::make_unique<sf::Text>(this->m_font);
		this->m_boidTotalText->setCharacterSize(fontSize);
		this->m_boidTotalText->setString("Total Boids: ...");
		textPos.y += this->m_boidMovementStateText->getLocalBounds().size.y + textMargin;
		this->m_boidTotalText->setPosition(textPos);

		// Load the Obstacle Total Text
		this->m_obstacleTotalText = std::make_unique<sf::Text>(this->m_font);
		this->m_obstacleTotalText->setCharacterSize(fontSize);
		this->m_obstacleTotalText->setString("Total Obstacles: ...");
		textPos.y += this->m_boidTotalText->getLocalBounds().size.y + textMargin;
		this->m_obstacleTotalText->setPosition(textPos);

	} else {
		// DEBUG
		std::cerr << "Unable to open file from path: 'assets/fonts/arial.ttf'" << std::endl;
	}

	// -- Left Mouse Button Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Mouse Button Press, then check if the Mouse Button was the Left Mouse Button
			if (const auto* key = event.getIf<sf::Event::MouseButtonPressed>()) {
				return key->button == sf::Mouse::Button::Left;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Left-Mouse Button Pressed in context of Gameplay Scene!" << std::endl;

			// Spawn a Boid at the Position of the Mouse
			sf::Vector2i mousePos = sf::Mouse::getPosition(ctx.window);
			sf::Vector2f spawnPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			this->m_agents.push_back(std::make_unique<Boid>(spawnPos, this->m_currentBehaviour));
		}
	});
	// -- //

	// -- Middle Mouse Button Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Mouse Button Press, then check if the Mouse Button was the Middle Mouse Button
			if (const auto* key = event.getIf<sf::Event::MouseButtonPressed>()) {
				return key->button == sf::Mouse::Button::Middle;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Middle-Mouse Button Pressed in context of Gameplay Scene!" << std::endl;

			// Move the Target to the Position of the Mouse
			sf::Vector2i mousePos = sf::Mouse::getPosition(ctx.window);
			sf::Vector2f newPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			this->m_target.setPosition(newPos);
		}
	});
	// -- //

	// -- Right Mouse Button Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Mouse Button Press, then check if the Mouse Button was the Right Mouse Button
			if (const auto* key = event.getIf<sf::Event::MouseButtonPressed>()) {
				return key->button == sf::Mouse::Button::Right;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Right-Mouse Button Pressed in context of Gameplay Scene!" << std::endl;

			// Spawn an Obstacle at the Position of the Mouse
			sf::Vector2i mousePos = sf::Mouse::getPosition(ctx.window);
			sf::Vector2f spawnPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			this->m_obstacles.emplace_back(spawnPos);
		}
	});
	// -- //


	// -- Space Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Space Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Space;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Space Key Pressed in context of Gameplay Scene!" << std::endl;

			// Toggle the Movement Behaviour of the Target
			BehaviourState state = (this->m_target.getMovementBehaviour() == BehaviourState::NONE) 
				? BehaviourState::WANDER : BehaviourState::NONE;
			this->m_target.setMovementBehaviour(state);
		}
	});
	// -- //

	// -- D Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the D Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::D;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "D Key Pressed in context of Gameplay Scene!" << std::endl;

			// Toggle the Debug Drawing Setting
			Settings::getInstance().shouldDrawDebugs = (Settings::getInstance().shouldDrawDebugs) ? false : true;
		}
	});
	// -- //

	// -- C Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the C Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::C;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "C Key Pressed in context of Gameplay Scene!" << std::endl;

			// Clear the Obstacles List
			this->m_obstacles.clear();
		}
	});
	// -- //

	// -- Number 0 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 0 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num0;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-0 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to None for all Boids
			this->m_currentBehaviour = BehaviourState::NONE;
		}
	});
	// -- //

	// -- Number 1 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 1 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num1;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-1 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Seek for all Boids
			this->m_currentBehaviour = BehaviourState::SEEK;
		}
	});
	// -- //

	// -- Number 2 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 2 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num2;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-2 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Flee for all Boids
			this->m_currentBehaviour = BehaviourState::FLEE;
		}
	});
	// -- //

	// -- Number 3 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 3 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num3;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-3 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Pursue for all Boids
			this->m_currentBehaviour = BehaviourState::PURSUE;
		}
	});
	// -- //

	// -- Number 4 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 4 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num4;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-4 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Evade for all Boids
			this->m_currentBehaviour = BehaviourState::EVADE;
		}
	});
	// -- //

	// -- Number 5 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 5 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num5;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-5 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Wander for all Boids
			this->m_currentBehaviour = BehaviourState::WANDER;
		}
	});
	// -- //

	// -- Number 6 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 6 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num6;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-6 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Arrival for all Boids
			this->m_currentBehaviour = BehaviourState::ARRIVAL;
		}
	});
	// -- //

	// -- Number 7 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 7 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num7;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-7 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Flock for all Boids
			this->m_currentBehaviour = BehaviourState::FLOCK;
		}
	});
	// -- //

	// -- Number 8 Key Pressed -- //
	this->m_commands.push_back({
		// Execution Criteria
		[](const sf::Event& event) {
			// First check if the Event was a Key Press, then check if the Key was the Number 8 Key
			if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
				return key->scancode == sf::Keyboard::Scancode::Num8;
			}

			// Otherwise, the event does not match the criteria
			return false;
		},
		// Command Action
		[this](const CommandContext& ctx) {
			// DEBUG
			std::cout << "Num-8 Key Pressed in context of Gameplay Scene!" << std::endl;

			// Set the Movement Behaviour to Leader-Follow for all Boids
			this->m_currentBehaviour = BehaviourState::ARRIVAL;
		}
	});
	// -- //
}

SceneGameplay::~SceneGameplay() {
}

void SceneGameplay::handleEvent(const sf::Event& event, const CommandContext& ctx) {
	// Loop through all Registered Commands and check if any of them match the given SFML Event
	for (auto& command : this->m_commands) {
		// Check if this Registered Command matches the given SFML Event
		if (command.match(event)) {
			// Execute the Registered Command's action using the provided context
			command(ctx);
		}
	}
}

void SceneGameplay::update(float dt) {
	// Agent Update Context
	AgentUpdateContext ctx{ dt, this->m_target, this->m_agents, this->m_obstacles };

	// Update Target State
	this->m_target.update(ctx);

	// Loop through all the Agents
	for (auto& agent : this->m_agents) {
		// Attempt to Dynamic Cast to Boids
		if (Boid* boid = dynamic_cast<Boid*>(agent.get())) {
			// Update the Movement Behaviour of the Boid
			boid->setMovementBehaviour(this->m_currentBehaviour);
		}

		// Update Agent State
		agent->update(ctx);
	}

	// Update the UI
	this->updateUI();
}

void SceneGameplay::draw(sf::RenderWindow& window) {
	// Loop through all the Agents
	for (auto& agent : this->m_agents) {
		// Draw the Agent
		agent->draw(window);
	}

	// Draw the Target
	this->m_target.draw(window);

	// Loop through all the Obstacles
	for (auto& obstacle : this->m_obstacles) {
		// Draw the Obstacle
		window.draw(obstacle.getShape());
	}

	// Draw the UI Text
	window.draw(*this->m_targetModeText.get());
	window.draw(*this->m_boidMovementStateText.get());
	window.draw(*this->m_boidTotalText.get());
	window.draw(*this->m_obstacleTotalText.get());
}

void SceneGameplay::updateUI() {
	// Update the Target Mode String
	std::string targetModeString = "Target Mode: ";
	switch (this->m_target.getMovementBehaviour()) {
		case BehaviourState::NONE: targetModeString += "NONE"; break; // None
		case BehaviourState::SEEK: targetModeString += "SEEK"; break; // Seek
		case BehaviourState::FLEE: targetModeString += "FLEE"; break; // Flee
		case BehaviourState::PURSUE: targetModeString += "PURSUE"; break; // Pursue
		case BehaviourState::EVADE: targetModeString += "EVADE"; break; // Evade
		case BehaviourState::WANDER: targetModeString += "WANDER"; break; // Wander
		case BehaviourState::ARRIVAL: targetModeString += "ARRIVAL"; break; // Arrival
		case BehaviourState::FLOCK: targetModeString += "FLOCK"; break; // Flock
		case BehaviourState::LEADER_FOLLOW: targetModeString += "LEADER_FOLLOW"; break; // Follow the Leader
		default: targetModeString += "NONE"; break; // Default
	}

	// Update the Boid Movement State String
	std::string boidMovementStateString = "Boid Movement Behaviour State: ";
	switch (this->m_currentBehaviour) {
		case BehaviourState::NONE: boidMovementStateString += "NONE"; break; // None
		case BehaviourState::SEEK: boidMovementStateString += "SEEK"; break; // Seek
		case BehaviourState::FLEE: boidMovementStateString += "FLEE"; break; // Flee
		case BehaviourState::PURSUE: boidMovementStateString += "PURSUE"; break; // Pursue
		case BehaviourState::EVADE: boidMovementStateString += "EVADE"; break; // Evade
		case BehaviourState::WANDER: boidMovementStateString += "WANDER"; break; // Wander
		case BehaviourState::ARRIVAL: boidMovementStateString += "ARRIVAL"; break; // Arrival
		case BehaviourState::FLOCK: boidMovementStateString += "FLOCK"; break; // Flock
		case BehaviourState::LEADER_FOLLOW: boidMovementStateString += "LEADER_FOLLOW"; break; // Follow the Leader
		default: boidMovementStateString += "NONE"; break; // Default
	}

	// Update the Boid Total String
	std::string boidTotalString = "Total Boids: ";
	boidTotalString += std::to_string(this->m_agents.size());


	// Update the Obstacle Total String
	std::string obstacleTotalString = "Total Obstacles: ";
	obstacleTotalString += std::to_string(this->m_obstacles.size());

	// Update all the String to UI Text
	this->m_targetModeText->setString(targetModeString);
	this->m_boidMovementStateText->setString(boidMovementStateString);
	this->m_boidTotalText->setString(boidTotalString);
	this->m_obstacleTotalText->setString(obstacleTotalString);
}
