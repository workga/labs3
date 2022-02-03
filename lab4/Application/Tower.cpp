#include "Map.h"
#include "Event.h"
#include "Game.h"
#include "Unit.h"
#include "Tower.h"

Table<TowerProps> Tower::_table = Table<TowerProps>();

Tower::Tower()
	: GameObject("Tower")
	, _level(0) {

	level_up();

	_stamina = _max_stamina;
	_charged = true;
	_shoot = false;

	_target_id = 0;
	_target_unit = nullptr;
}

void Tower::print() {
	//std::string et = std::to_string(Game::game().elapsed_time());
	std::cout << "[ " <<
		"STAMINA:" << _stamina << ", \t" <<
		"S: " << _shoot << ", \t" <<
		"C: " << _charged <<
		" ]" << "\n";

}

void Tower::update(double dt) {
	// find target
	std::vector<Unit*> *units = Game::game().get_units();

	_target_unit = find_target(units);
	if (!_target_unit) {
		// didn't find target

		_target_id = 0;
		_shoot = false;
	}
	else {
		_target_id = _target_unit->get_id();

		_shoot = true;
	}

	// here target and id are valid
	if (!_shoot || !_charged) {
		double hp = dt * _charging * _max_stamina;
		charge(hp);
	} else {
		double dp = dt * _damage;
		shoot(dp);
	}
}

void Tower::render(sf::RenderWindow& window) {
	int tile_size = Game::game().get_tile_size();

	window.draw(_sprite);

	sf::CircleShape circle;
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Color(255, 0, 0, 128));
	circle.setOutlineThickness(2);
	circle.setOrigin(_radius*tile_size, _radius*tile_size);
	circle.setRadius(_radius*tile_size);
	circle.setPosition(_sprite.getPosition());

	if (_shoot && _charged) {
		sf::Vertex line[2];
		line[0].position = _sprite.getPosition();
		line[0].color = sf::Color::Red;
		line[1].position = _target_unit->get_sprite_pos();
		line[1].color = sf::Color::Red;
		window.draw(line, 2, sf::Lines);
	}

	window.draw(circle);
	render_bar(window, _stamina, _max_stamina, sf::Color::Blue, sf::Color::Cyan);
}

void Tower::charge(double hp) {
	_stamina += hp;

	if (_stamina >= _max_stamina) {
		_stamina = _max_stamina;
		_charged = true;
	}
}

void Tower::shoot(double dp) {
	Game::game().add_event(new EUnitDamage(_target_unit, dp));

	_stamina -= dp;

	if (_stamina <= 0) {
		_stamina = 0;
		_charged = false;
	}
}

// find nearest unit or matching target_id
Unit* Tower::find_target(std::vector<Unit*>* units) {
	Unit* target_unit = nullptr;

	double et = Game::game().elapsed_time();


	double cur_d = _radius;
	for (auto& u : *units) {
		double d = distance(u);
		if (d < cur_d) {
			target_unit = u;
			cur_d = d;
		}
		
		if (d < _radius && u->get_id() == _target_id) {
			target_unit = u;
			break;
		}
	}

	return target_unit;
}


void Tower::level_up() {
	if (_level >= _table.get_max_level())
		throw std::runtime_error("Too big level.");

	TowerProps props = _table[_level + 1];

	if (_level + 1 > 1) {
		double balance = Game::game().get_balance();
		if (balance < props._price)
			throw std::runtime_error("Too low balance.");
		else
			Game::game().decrease_balance(props._price);
	}

	_level++;

	_radius = props._radius;
	_max_stamina = props._max_stamina;
	_damage = props._damage;
	_charging = props._charging;

	if (!_texture.loadFromFile("./sprites/tower_0" + std::to_string(_level) + ".png")) {
		throw std::runtime_error("Can't load texture from file.");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(Map::_TILE_SIZE / 2, Map::_TILE_SIZE / 2);

	_stamina = _max_stamina;
}
