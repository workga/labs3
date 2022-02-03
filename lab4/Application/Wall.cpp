#include "Map.h"
#include "Game.h"
#include "Event.h"
#include "Wall.h"

Table<WallProps> Wall::_table = Table<WallProps>();

Wall::Wall()
	: GameObject("Wall")
	, _level(0)
	, _alive(true) {

	level_up();
	_health = _max_health;
}

void Wall::update(double dt) {
	heal(_recovery * dt);
}

void Wall::render(sf::RenderWindow& window) {
	window.draw(_sprite);

	render_bar(window, _health, _max_health);
}


void Wall::level_up() {
	if (_level >= _table.get_max_level())
		throw std::runtime_error("Too big level.");

	WallProps props = _table[_level + 1];

	if (_level + 1 > 1) {
		double balance = Game::game().get_balance();
		if (balance < props._price)
			throw std::runtime_error("Too low balance.");
		else
			Game::game().decrease_balance(props._price);
	}
	_level++;

	_max_health = props._max_health;
	_recovery = props._recovery;

	if (!_texture.loadFromFile("./sprites/wall_0" + std::to_string(_level) + ".png")) {
		throw std::runtime_error("Can't load texture from file.");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(Map::_TILE_SIZE / 2, Map::_TILE_SIZE / 2);

	_health = _max_health;
}

void Wall::repair() {
	double balance = Game::game().get_balance();

	double price = (1 - _health / _max_health) * _table[_level]._price;
	double hp = _max_health - _health;

	if (balance < price) {
		std::cout << "Can't repair completely. Repaired partly.\n";
		hp = hp * (balance / price);
		price = balance;
	}

	Game::game().decrease_balance(price);
	heal(hp);
}

void Wall::heal(double hp) {
	if (!_alive) return;

	_health += hp;

	if (_health > _max_health)
		_health = _max_health;
}

void Wall::damage(double dp) {
	if (!_alive) return;
	_health -= dp;

	if (_health <= 0) {
		_health = 0;
		destroy();
	}
}

void Wall::destroy() {
	if (!_alive) return;
	
	Game::game().add_event(new EWallDestroyed(this));
	_alive = false;
}
