#include "Map.h"
#include "Event.h"
#include "Game.h"
#include "LightUnit.h"

#include <format>

Table<LightUnitProps> LightUnit::_table = Table<LightUnitProps>();

LightUnit::LightUnit(int level)
	: Unit("LightUnit", UNIT_TYPE::LIGHT, level) {

	set_level(_level);
	_health = _max_health;
	if (!_texture.loadFromFile("./sprites/light_unit_0" + std::to_string(_level) + ".png")) {
		throw std::runtime_error("Can't load texture from file.");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(Map::_TILE_SIZE / 2, Map::_TILE_SIZE / 2);

	create_path();
}

void LightUnit::set_level(int level) {
	if (level > _table.get_max_level())
		throw std::runtime_error("Too big level.");
	_level = level;

	LightUnitProps props = _table[_level];

	_max_health = props._max_health;
	_recovery = props._recovery;
	_speed = props._speed;
	_damage = props._damage;
}

void LightUnit::create_path() {
	_path = Game::game().get_map()->make_path(_type);
}

void LightUnit::move(double dt) {
	if (_path.empty()) {
		return;
	}

	Point point = _path[0];

	Tile& next_tile = Game::game().get_map()->get_tile(point.x, point.y);
	if (next_tile._surface == SURFACE::WALL)
		return;

	double displ = _speed * dt;
	double dist = distance(point);
	//std::cout << "DIST: " << dist << "DISPL: " << displ << "\n";

	if (dist <= displ) {
		//_position = point;
		set_pos(point.x, point.y);
		_path.erase(_path.begin());
	}
	else {
		double a = angle(point);
		Point new_pos(_position.x + displ * cos(a),
			_position.y + displ * sin(a));
		set_pos(new_pos.x, new_pos.y);
	}

	if (_path.empty()) {
		// placeholder
		std::cout << "[DEBUG] Unit finished its path.\n";
		Game::game().add_event(new ECastleDamage(_health * _damage));
		Game::game().add_event(new EUnitDamage(this, _health));
	}
}