#ifndef __H_GAME
#define __H_GAME

#include <stdexcept>
#include <vector>
#include "Queue.h"
#include "SFML/Graphics.hpp"

#include "StatusBar.h"

class Map;
struct Tile;
class Event;

struct Point;
class Gate;
class Unit;
	enum class UNIT_TYPE;
class Tower;
class Wall;
class Castle;

/**
 * @brief Main class that controlls game loop.
 * 	
 * Game class controlls all game events and updates, stores all game entities.
 * This class is implemented as Singltone.
 *
 */
class Game {
public:
	static const int _SIZE = 640;

	/**
	 * @brief get Game class instance
	 * 
	 * Singltone's interface.
	 * Create new Game instance, if it doesn't exist, and return the pointer to this instance.
	 *
	 * @return Game instance.
	 */
	static Game& game();
	~Game();

	/**
	 * @brief init Game instance
	 *
	 * It inits map, gate, castle and other default entities
	 */
	void init();

	/**
	 * @brief start Game loop
	 * 
	 * It starts game loop for the game instance
	 */
	void start();

	/**
	 * @brief finish Game loop
	 * 
	 * Exit game loop and remove all stored entities such as game objects and events.
	 */
	void finish(bool victory, bool now = false);


	/**
	 * @brief get time, elapsed from game start
	 * 
	 * It returns time in seconds considering the speed factor of the game.
	 * 
	 * @return Time elapsed from game start. 
	 */
	double elapsed_time();

	/**
	 * @brief get current user's balance
	 */
	double get_balance();


	/**
	 * @brief add some amount of gold to user's balance
	 * 
	 * @param pp Amount of gold to add to user's balance.
	 */
	void increase_balance(double pp);

	/**
	 * @brief substract some amount of gold from user's balance
	 *
	 * @param pp Amount of gold to substract from user's balance.
	 */
	void decrease_balance(double pp);


	/**
	 * @brief get pointer to Map instance of the game
	 * 
	 * @return Pointer to Map 
	 */
	Map* get_map() { return _map; };


	/**
	 * @brief get position where units are spawned
	 * 
	 * This position is actually position of the Gate.
	 * 
	 * @return start position Point
	 */
	Point get_start_pos();

	/**
	 * @brief get position where units go
	 * 
	 * This position is actually position of the Castle
	 * 
	 * @return finish position Point
	 */
	Point get_finish_pos();

	int get_tile_size();

	/**
	 * @brief add Event to events queue
	 * 
	 * @param event Pointer to event which you want to add in event queue
	 */
	void add_event(Event* event);

	/**
	 * @brief add unit to units list
	 * 
	 * @param type Type of the Unit: LIGHT, HEAVY, AIR
	 * @param level Level of unit
	 */
	void add_unit(UNIT_TYPE type, int level);

	/**
	 * @brief remove unit from units list
	 * 
	 * @param unit Pointer to unit to remove from unit list
	 */
	void remove_unit(Unit* unit);

	/**
	 * @brief get list of units
	 * 
	 * @return Pointer to vector of all units' pointers
	 */
	std::vector<Unit*>* get_units() { return &_units; };

	/**
	 * @brief calculate default pathes for units
	 * 
	 * It calculates new default pathes from starting position to finish position for each type of unit.
	 * Use it if map was changed (ex. user built tower or units removed wall)
	 * 
	 */
	//static void update_default_paths();

	/**
	 * @brief add tower to towers list
	 * 
	 * @param pos Position on the map where to add new tower
	 */
	void add_tower(Point pos);


	/**
	 * @brief add wall to walls list
	 * 
	 * @param pos Position on the map where to add new wall
	 */
	void add_wall(Point pos);
	

	/**
	 * @brief remove wall from walls list
	 * 
	 * @param wall Pointer to wall to remove from walls list
	 */
	void remove_wall(Wall* wall);
	
	std::vector<Wall*>* get_walls() { return &_walls; };

	/**
	 * @brief get pointer to Castle instance of the game
	 * 
	 * @return Pointer to Castle 
	 */
	Castle* get_castle() { return _castle; };


private:
	Game();
	static Game* _instance;
	static bool _initialized;

	bool _finish;
	bool _victory;
	enum class Screen {
		VICTORY,
		DEFEAT
	};
	std::map<Screen, sf::Texture> _screen_textures;
	std::map<Screen, sf::Sprite> _screen_sprites;

	const double _SPEED = 1;
	sf::RenderWindow _window;

	double _time_start;
	double _time_cur;
	double _speed;

	int _level;
	Map* _map;
	StatusBar _status_bar;

	double _balance;

	Queue<Event*> _events;

	Gate* _gate;
	std::vector<Unit*> _units;
	std::vector<Wall*> _walls;
	std::vector<Tower*> _towers;
	Castle* _castle;

	void update(double dt);
	void handle_input();
	void handle_map_click(int x, int y);
	void handle_bar_click(int x, int y);
	void update_on_events();
	void render();
	void render_gameover();

	double now_time();
};

#endif
