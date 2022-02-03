#include "Map.h"
#include "Event.h"
#include "Wall.h"
#include "Game.h"

#include "AirUnit.h"

Table<AirUnitProps> AirUnit::_table = Table<AirUnitProps>();

AirUnit::AirUnit(int level)
	: Unit("AirUnit", UNIT_TYPE::AIR, level) {

	set_level(_level);
	_health = _max_health;
	if (!_texture.loadFromFile("./sprites/air_unit_0" + std::to_string(_level) + ".png")) {
		throw std::runtime_error("Can't load texture from file.");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(Map::_TILE_SIZE / 2, Map::_TILE_SIZE / 2);

	create_path();
}

void AirUnit::set_level(int level) {
	if (level > _table.get_max_level())
		throw std::runtime_error("Too big level.");
	_level = level;

	AirUnitProps props = _table[_level];

	_max_health = props._max_health;
	_recovery = props._recovery;
	_speed = props._speed;
	_damage = props._damage;
	_bomb_damage = props._bomb_damage;
}

void AirUnit::create_path() {
	_path = Game::game().get_map()->make_path(_type);
}

void AirUnit::move(double dt) {
	if (_path.empty()) {
		return;
	}

	Point point = _path[0];

	double displ = _speed * dt;
	double dist = distance(point);
	//std::cout << "DIST: " << dist << "DISPL: " << displ << "\n";

	if (dist <= displ) {
		//_position = point;
		set_pos(point.x, point.y);
		_path.erase(_path.begin());

		bomb(point);
	}
	else {
		double a = angle(point);
		Point new_pos(_position.x + displ * cos(a),
			_position.y + displ * sin(a));
		set_pos(new_pos.x, new_pos.y);
	}

	_sprite.rotate(-dt*_speed*100);

	if (_path.empty()) {
		// placeholder
		std::cout << "[DEBUG] Unit finished its path.\n";
		Game::game().add_event(new ECastleDamage(_health * _damage));
		Game::game().add_event(new EUnitDamage(this, _health));
	}
}

void AirUnit::bomb(Point p) {
	Tile& tile = Game::game().get_map()->get_tile(p.x, p.y);
	if (tile._surface == SURFACE::WALL) {
		std::cout << "[DEBUG] AirUnit found Wall.\n";
		Game::game().add_event(new EWallDamage(dynamic_cast<Wall*>(tile._building), _bomb_damage));
		return;
	}
}