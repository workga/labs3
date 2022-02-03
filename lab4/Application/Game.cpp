#include <ctime>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>

#include "SFML/Graphics.hpp"


#include "Map.h"
#include "Event.h"
//#include "GameObject.h"
#include "Gate.h"
#include "Unit.h"
	#include "LightUnit.h"
	#include "HeavyUnit.h"
	#include "AirUnit.h"
#include "Tower.h"
#include "Wall.h"
#include "Castle.h"

#include "Game.h"

#define VERBOSE false
#define VERBOSE_MAP false
#define VERBOSE_UNITS false
#define VERBOSE_TOWERS false

Game* Game::_instance = nullptr;
bool Game::_initialized = false;

Game::Game()
	: _window(sf::VideoMode(_SIZE, _SIZE + Map::_TILE_SIZE), "Tower Defense")
	, _finish(true)
	, _time_start(0)
	, _time_cur(0)
	, _speed(_SPEED)
	, _level(0)
	, _balance(0)
	, _status_bar() {

	_map = new Map();
	_gate = new Gate();
	_castle = new Castle();

	if (!(
		_screen_textures[Screen::DEFEAT].loadFromFile("./sprites/screen_defeat.png") &&
		_screen_textures[Screen::VICTORY].loadFromFile("./sprites/screen_victory.png")
		)) {
		throw std::runtime_error("Can't load texture from file");
	}
	_screen_sprites[Screen::DEFEAT].setTexture(_screen_textures[Screen::DEFEAT]);
	_screen_sprites[Screen::VICTORY].setTexture(_screen_textures[Screen::VICTORY]);
}

Game& Game::game() {
	if (!_instance)
		_instance = new Game();
	return *_instance;
}

Game::~Game() {
	_instance = nullptr;

	delete _map;
	
	while (!_events.empty()) {
		delete _events.front();
		_events.pop();
	}
	// here delete input events
	
	delete _gate;
	
	for (auto& u : _units) {
		delete u;
		u = nullptr;
	}
	for (auto& t : _towers) {
		delete t;
		t = nullptr;
	}
	for (auto& w : _walls) {
		delete w;
		w = nullptr;
	}

	delete _castle;
}

void Game::init() {
	if (_initialized)
		return;
	else
		_initialized = true;

	_finish = false;

	_level = 1; // ...
	_map->init(_level);
	_map->print();

	_gate->set_pos(_map->get_start_pos());
	_map->set_gate(_gate);
	_castle->set_pos(_map->get_finish_pos());
	_map->set_castle(_castle);
}

void Game::start() {
	sf::Clock sf_clock; // starts as soon as it's created

	// start time and game loop
	_time_start = now_time();
	_time_cur = _time_start;

	double time_prev = _time_cur;
	while (!_finish) {
		_time_cur = now_time();
		double dt = _time_cur - time_prev;
		time_prev = _time_cur;

		update(dt);	
		handle_input();
		update_on_events();

		// stop if all units are dead
		if (_gate->is_empty() && _units.empty()) {
			finish(true);
		}

		render();
		//std::cout << "Elapsed time since previous frame(microseconds): " << clock.getElapsedTime().asMicroseconds() << std::endl;
		//clock.restart();
	}

	std::cout << "[INFO] GAME OVER!\n";
}

void Game::handle_input() {
	sf::Event sf_event;
	while (_window.pollEvent(sf_event)) {
		switch (sf_event.type) {
		case sf::Event::EventType::Closed: {
			_window.close();
			finish(false, true);

			break;
		}
		case sf::Event::MouseButtonReleased : {
			if (sf_event.mouseButton.button == sf::Mouse::Left) {
				if (sf_event.mouseButton.y < _SIZE) {
					handle_map_click(sf_event.mouseButton.y / Map::_TILE_SIZE,
									 sf_event.mouseButton.x / Map::_TILE_SIZE);
				}
				else {
					handle_bar_click(sf_event.mouseButton.x / Map::_TILE_SIZE,
									 sf_event.mouseButton.y / Map::_TILE_SIZE);
				}
			}
			break;
		}
		case sf::Event::MouseWheelScrolled: {
			if (sf_event.mouseWheelScroll.delta < 0)
				_status_bar.next_action();
			else if (sf_event.mouseWheelScroll.delta > 0)
				_status_bar.prev_action();

			break;
		}
		default: {

		}
		}
	}
}

void Game::handle_map_click(int x, int y) {
	Tile& tile = _map->get_tile(x, y);

	if (!tile._is_busy && _status_bar.get_current_action() == Action::BUILD) {
		if (tile._base == SURFACE::GRASS) {
			try {
				add_tower(Point(x, y));
				std::cout << "Build Tower.\n";	
			}
			catch (const std::runtime_error& err) {
				std::cout << err.what() << "\n";
			}
		}
		else if  (tile._base == SURFACE::ROAD) {
			try {
				add_wall(Point(x, y));
				std::cout << "Build Wall.\n";
			}
			catch (const std::runtime_error& err) {
				std::cout << err.what() << "\n";
			}
		}
	}
	else if (tile._building) {
		if (_status_bar.get_current_action() == Action::LEVEL_UP && 
			(tile._surface == SURFACE::WALL ||
			 tile._surface == SURFACE::CASTLE ||
			 tile._surface == SURFACE::TOWER)) {
			try {
				tile._building->level_up();
				std::cout << "Level up.\n";
			}
			catch (const std::runtime_error& err) {
				std::cout << err.what() << "\n";
			}
		}
		else if (_status_bar.get_current_action() == Action::REPAIR &&
				 (tile._surface == SURFACE::WALL ||
				  tile._surface == SURFACE::CASTLE)) {
			try {
				tile._building->repair();
				std::cout << "Repair.\n";
			}
			catch (const std::runtime_error& err) {
				std::cout << err.what() << "\n";
			}
		}
	}
}

void Game::handle_bar_click(int x, int y) {
	if (x <= (int)Action::ENUM_LEN) {
		_status_bar.set_action(static_cast<Action>(x));
	}
}

void Game::update(double dt) {

	_gate->update(dt);

	for (auto& u : _units)
		u->update(dt);
	for (auto& t : _towers)
		t->update(dt);
	for (auto& w : _walls)
		w->update(dt);

	_castle->update(dt);
}

void Game::update_on_events() {
	while (!_events.empty()) {
		_events.front()->activate();
		delete _events.front();
		_events.pop();
	}
}

void Game::render() {
	_window.clear();

	_map->render(_window);

	_gate->render(_window);

	_castle->render(_window);

	for (auto& t : _towers)
		t->render(_window);
	for (auto& w : _walls)
		w->render(_window);
	for (auto& u : _units)
		u->render(_window);


	_status_bar.render(_window);


	_window.display();

	// Log
	if (VERBOSE_MAP)
		_map->print();
	if (VERBOSE_UNITS) {
		for (auto& u : _units)
			u->print();
	}
	if (VERBOSE_TOWERS) {
		for (auto& t : _towers)
			t->print();
	}

	if (VERBOSE)
		std::cout << "\n\n";

}

void Game::render_gameover() {
	_window.clear();

	if (_victory)
		_window.draw(_screen_sprites[Screen::VICTORY]);
	else
		_window.draw(_screen_sprites[Screen::DEFEAT]);

	_window.display();
}

void Game::finish(bool victory, bool now) {
	_victory = victory;

	if (!now) {
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		render_gameover();
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	_finish = true;
}


// Interface
double Game::elapsed_time() {
	return (_time_cur - _time_start);
}

double Game::get_balance() {
	return _balance;
}

void Game::increase_balance(double pp) {
	_balance += pp;
}

void Game::decrease_balance(double pp) {
	if (_balance < pp) throw std::runtime_error("Too small balance.");
	_balance -= pp;
}

Point Game::get_start_pos() {
	return _gate->get_pos();
};

Point Game::get_finish_pos() {
	return _castle->get_pos();
};

int Game::get_tile_size() {
	return _map->_TILE_SIZE;
}

void Game::add_event(Event* event) {
	_events.push(event);
}

void Game::add_unit(UNIT_TYPE type, int level) {
	Unit* unit = nullptr;

	switch (type) {
		case UNIT_TYPE::LIGHT :	{
			unit = new LightUnit(level);
			break;
		}
		case UNIT_TYPE::HEAVY: {
			unit = new HeavyUnit(level);
			break;
		}
		case UNIT_TYPE::AIR: {
			unit = new AirUnit(level);
			break;
		}
		default: {
			throw std::runtime_error("[ERROR] Wrong UNIT_TYPE value.");
		}
	}

	unit->set_pos(_gate->get_pos().x, _gate->get_pos().y);
	_units.push_back(unit);
}


void Game::add_tower(Point pos) {
	Tile& tile = _map->get_tile(pos.x, pos.y);
	if (tile._is_busy)
		throw std::runtime_error("Tile is busy.");
	if (tile._building)
		throw std::runtime_error("Tile is built-up.");

	if (_balance < Tower::_table[1]._price)
		throw std::runtime_error("Too low balance");
	else
		decrease_balance(Tower::_table[1]._price);

	Tower* tower = new Tower();

	tower->set_pos(pos);

	tile._surface = SURFACE::TOWER;
	tile._is_busy = true;
	tile._building = tower;

	_towers.push_back(tower);
}

void Game::add_wall(Point pos) {
	Tile& tile = _map->get_tile(pos.x, pos.y);
	if (tile._is_busy)
		throw std::runtime_error("Tile is busy.");
	if (tile._building)
		throw std::runtime_error("Tile is built-up.");

	if (_balance < Wall::_table[1]._price)
		throw std::runtime_error("Too low balance");
	else
		decrease_balance(Wall::_table[1]._price);

	Wall* wall = new Wall();

	wall->set_pos(pos);

	tile._surface = SURFACE::WALL;
	tile._is_busy = true;
	tile._building = wall;

	_walls.push_back(wall);
}

void Game::remove_wall(Wall* wall) {
	Tile& tile = _map->get_tile(wall->get_pos().x, wall->get_pos().y);
	tile._surface = SURFACE::NONE;
	tile._is_busy = false;
	tile._building = nullptr;

	auto it = std::find(_walls.begin(), _walls.end() , wall);
	delete *it;
	_walls.erase(it);
}

void Game::remove_unit(Unit* unit) {
	auto it = std::find(_units.begin(), _units.end(), unit);
	delete* it;
	_units.erase(it);
}

double Game::now_time() {
	return (std::clock() / static_cast<double>CLOCKS_PER_SEC) * _speed;
}