#include <cmath>
#include "Map.h"
#include "Event.h"
#include "Game.h"
#include "Unit.h"

Unit::Unit(std::string name, UNIT_TYPE type, int level)
	: GameObject(name)
	, _type(type)
	, _level(level)
	, _alive(true) {

	int max = Map::_TILE_SIZE / 4;
	int min = -Map::_TILE_SIZE / 4;

	_position_noise.x = rand() % (max - min + 1) + min;
	_position_noise.y = rand() % (max - min + 1) + min;
}

void Unit::print() {
	//std::string et = std::to_string(Game::game().elapsed_time());
	std::cout << "[ " << 
					 "X: " << _position.x << ", \t" << 
					 "Y: " << _position.y << ", \t" <<
					 "HP:" << _health << "/" << _max_health << ", \t" <<
					 "AIM: ( " << _path[0].x << ", " << _path[0].y << " )" <<
				 " ]" << "\n";

}

void Unit::update(double dt) {
	heal(_recovery * dt);
	move(dt);
}

void Unit::render(sf::RenderWindow& window) {
	_sprite.move(_position_noise.x, _position_noise.y);
	
	window.draw(_sprite);
	render_bar(window, _health, _max_health);
	
	_sprite.move(-_position_noise.x, -_position_noise.y);
}

void Unit::heal(double hp) {
	if (!_alive) return;

	_health += hp;

	if (_health > _max_health)
		_health = _max_health;
}

void Unit::damage(double dp) {
	if (!_alive) return;
	_health -= dp;

	if (_health <= 0) {
		_health = 0;
		destroy();
	}
}

void Unit::destroy() {
	if (!_alive) return;

	Game::game().add_event(new EUnitDestroyed(this));
	_alive = false;
}