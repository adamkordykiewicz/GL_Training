#ifndef GAME_H
#define GAME_H

#include "States/MainMenuState.h"
#include "GraphicsSettings.h"

class Game
{
	private:
		GraphicsSettings _graphicsSettings;
		StateData _stateData;
		sf::RenderWindow* _window;
		sf::Event _sfEvent;

		sf::Clock _dtClock;
		float _dt;

		std::stack<State*> _states;
		std::map<std::string, int> _supportedKeys;
		float _gridSize;

		void initVariables();
		void initGraphicsSettings();
		void initWindow();
		void initKeys();
		void initStateData();
		void initStates();

	public:
		Game();
		virtual ~Game();

		void endApplication();
		void updateDt();
		void updateSfmlEvents();
		void update();
		void render();
		void run();
		void gitmajonez();
};

#endif