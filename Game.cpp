#include "Game.h"

void Game::initVariables()
{
	_window = nullptr;
	_dt = 0.f;
	_gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
	_graphicsSettings.loadFromFile("Config/graphics_settings.ini");
}

void Game::initWindow()
{
	if(_graphicsSettings._fullscreen)
	{
		_window = new sf::RenderWindow
		(
			_graphicsSettings._resolution,
			_graphicsSettings._title,
			sf::Style::Fullscreen,
			_graphicsSettings._contextSettings
		);
	}
	else
	{
		_window = new sf::RenderWindow
		(
			_graphicsSettings._resolution,
			_graphicsSettings._title,
			sf::Style::Titlebar | sf::Style::Close,
			_graphicsSettings._contextSettings
		);
	}

	_window->setFramerateLimit(_graphicsSettings._frameRateLimit);
	_window->setVerticalSyncEnabled(_graphicsSettings._verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if(ifs.is_open())
	{
		std::string key = "";
		int keyValue = 0;

		while(ifs >> key >> keyValue)
		{
			_supportedKeys[key] = keyValue;
		}
	}

	ifs.close();

	for(auto i: _supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStateData()
{
	_stateData._window = _window;
	_stateData._graphicsSettings = &_graphicsSettings;
	_stateData._supportedKeys = &_supportedKeys;
	_stateData._states = &_states;
	_stateData._gridSize = _gridSize;
}

void Game::initStates()
{
	_states.push(new MainMenuState(&_stateData));
}

Game::Game()
{
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeys();
	initStateData();
	initStates();
}

Game::~Game()
{
	delete _window;

	while(!_states.empty())
	{
		delete _states.top();
		_states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending application." << std::endl;
}

void Game::updateDt()
{
	_dt = _dtClock.restart().asSeconds();
}

void Game::updateSfmlEvents()
{
	while(_window->pollEvent(_sfEvent))
	{
		if (sf::Event::Closed == _sfEvent.type)
		{
			_window->close();
		}
	}
}

void Game::update()
{
	updateSfmlEvents();

	if(!_states.empty())
	{
		if(_window->hasFocus())
		{
			_states.top()->update(_dt);

			if(_states.top()->getQuit())
			{
				_states.top()->endState();
				delete _states.top();
				_states.pop();
			}
		}
	}
	else
	{
		endApplication();
		_window->close();
	}
}

void Game::render()
{
	_window->clear();

	if(!_states.empty())
	{
		_states.top()->render(_window);
	}

	_window->display();
}

// this code has no comments
void Game::run()
{
	while(_window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}
