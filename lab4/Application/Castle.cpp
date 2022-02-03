#include "Map.h"
#include "Event.h"
#include "Game.h"
#include "Castle.h"

Table<CastleProps> Castle::_table = Table<CastleProps>();

Castle::Castle()
	: GameObject("Castle")
	, _level(0)
	, _alive(true) {

	level_up();
	_health = _max_health;
}

void Castle::update(double dt) {
	heal(_recovery * dt);
	earn(_profit * dt);
}

void Castle::render(sf::RenderWindow& window) {
	window.draw(_sprite);

	render_bar(window, _health, _max_health);
}

void Castle::level_up() {
	if (_level >= _table.get_max_level())
		throw std::runtime_error("Too big level.");

	CastleProps props = _table[_level + 1];

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
	_profit = props._profit;

	if (!_texture.loadFromFile("./sprites/castle_0" + std::to_string(_level) + ".png")) {
		throw std::runtime_error("Can't load texture from file.");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(Map::_TILE_SIZE/2, Map::_TILE_SIZE / 2);

	_health = _max_health;
}

void Castle::repair() {
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

void Castle::earn(double pp) {
	Game::game().increase_balance(pp);
	//Game::game().add_event(new E_INCREASE_BALANCE(pp))
}

void Castle::heal(double hp) {
	//if (!_alive) return;

	_health += hp;

	if (_health > _max_health)
		_health = _max_health;
}

void Castle::damage(double dp) {
	//if (!_alive) return;
	_health -= dp;

	if (_health <= 0)
		destroy();
}

void Castle::destroy() {
	if (!_alive) return;

	Game::game().add_event(new ECastleDestroyed);
	_alive = false;
}