#ifndef __H_STATUS_BAR
#define __H_STATUS_BAR

#include "SFML/Graphics.hpp"

enum class Action {
	NONE,
	BUILD,
	LEVEL_UP,
	REPAIR,


	ENUM_LEN
};

class StatusBar {
public:
	StatusBar();

	void next_action();
	void prev_action();
	void set_action(Action action);

	Action get_current_action();

	void render(sf::RenderWindow& window);
private:
	std::map<Action, sf::Texture> _textures;
	std::map<Action, sf::Sprite> _sprites;

	Action _current_action;


};

#endif __H_STATUS_BAR

