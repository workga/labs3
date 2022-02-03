#include <cmath>
#include "Map.h"
#include "GameObject.h"
#include "Game.h"

std::string GameObject::_name = "GameObject";
int GameObject::_last_id = 0;

GameObject::GameObject(std::string name) {
	_name = name;	
	_id = ++_last_id;
	_position = { 0, 0 };
}

void GameObject::set_pos(double x, double y) {
	_position = { x, y };

	int tile_size = Game::game().get_tile_size();
	_sprite.setPosition(sf::Vector2f(y*tile_size + Map::_TILE_SIZE / 2,
									 x*tile_size + Map::_TILE_SIZE / 2));
};

double GameObject::distance(GameObject* obj) {
	return distance(obj->get_pos());
}

double GameObject::distance(Point p) {
	Point s = _position;

	return sqrt(
		(s.x - p.x) * (s.x - p.x) +
		(s.y - p.y) * (s.y - p.y)
	);
}

double GameObject::angle(Point p) {
	Point s = _position;

	return atan2((p.y - s.y), (p.x - s.x));
}


void GameObject::render_bar(sf::RenderWindow& window,
							double value,
							double max_value,
							sf::Color left_clr,
							sf::Color right_clr,
							double scale) {

	sf::RectangleShape bar_green;
	bar_green.setSize(sf::Vector2f(
		Map::_TILE_SIZE * (value / max_value),
		Map::_TILE_SIZE / 10));
	bar_green.setScale(scale, 1);

	bar_green.setFillColor(left_clr);
	bar_green.setOrigin(Map::_TILE_SIZE / 2, 0);
	bar_green.setPosition(
		_sprite.getPosition().x,
		_sprite.getPosition().y - Map::_TILE_SIZE / 2);

	sf::RectangleShape bar_red;
	bar_red.setSize(sf::Vector2f(
		Map::_TILE_SIZE * (1 - value / max_value),
		Map::_TILE_SIZE / 10));
	bar_red.setScale(scale, 1);

	bar_red.setFillColor(right_clr);
	bar_red.setOrigin(Map::_TILE_SIZE / 2, 0);
	bar_red.setPosition(
		(_sprite.getPosition().x + scale*(Map::_TILE_SIZE * (value / max_value))),
		_sprite.getPosition().y - Map::_TILE_SIZE / 2);

	window.draw(bar_green);
	window.draw(bar_red);

}