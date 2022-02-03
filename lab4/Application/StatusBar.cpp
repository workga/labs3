#include <string>

#include "Map.h"
#include "Game.h"
#include "StatusBar.h"


StatusBar::StatusBar() {
	if (!(
		_textures[Action::NONE].loadFromFile("./sprites/action_none.png") &&
		_textures[Action::BUILD].loadFromFile("./sprites/action_build.png") &&
		_textures[Action::LEVEL_UP].loadFromFile("./sprites/action_level_up.png") &&
		_textures[Action::REPAIR].loadFromFile("./sprites/action_repair.png")
		)) {
		throw std::runtime_error("Can't load texture from file");
	}

	for (auto& t : _textures) {
		_sprites[t.first].setTexture(t.second);
		_sprites[t.first].setPosition(Map::_TILE_SIZE*((int)t.first), Game::_SIZE);
	}

	_current_action = Action::NONE;
}

void StatusBar::next_action() {
	_current_action = (Action)(((int)_current_action + 1) % (int)Action::ENUM_LEN);
}

void StatusBar::prev_action() {
	_current_action = (Action)(((int)Action::ENUM_LEN + (int)_current_action - 1) % (int)Action::ENUM_LEN);
}

void StatusBar::set_action(Action action) {
	_current_action = action;
}

Action StatusBar::get_current_action() {

	return _current_action;
}

void StatusBar::render(sf::RenderWindow & window) {
	for (auto& s : _sprites) {
		window.draw(s.second);
	}

	sf::RectangleShape frame;

	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::Yellow);
	frame.setOutlineThickness(3);

	frame.setSize(sf::Vector2f(Map::_TILE_SIZE, Map::_TILE_SIZE));
	frame.setOrigin(sf::Vector2f(
		Map::_TILE_SIZE/2,
		Map::_TILE_SIZE / 2));
	frame.setPosition(sf::Vector2f(
		_sprites[_current_action].getPosition().x + Map::_TILE_SIZE / 2,
		_sprites[_current_action].getPosition().y + Map::_TILE_SIZE / 2));
	frame.setScale(0.95, 0.95);

	window.draw(frame);

	sf::Font font;
	if (!font.loadFromFile("./sprites/font.ttf"))
		throw std::runtime_error("Can't load font from file.");

	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(Game::game().get_balance()));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(Game::_SIZE - 3 * Map::_TILE_SIZE, Game::_SIZE + Map::_TILE_SIZE/4);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	window.draw(text);
}
