#ifndef __H_GAME_OBJECT
#define __H_GAME_OBJECT

#include <cmath>
#include <string>
#include "SFML/Graphics.hpp"

struct Point {
	double x;
	double y;
	bool operator==(const Point& other) {
		return (x == other.x && y == other.y);
	}
};

class GameObject {
public:
	virtual ~GameObject() {};

	virtual void update(double dt) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	Point get_pos() { return _position; };
	sf::Vector2f get_sprite_pos() { return _sprite.getPosition(); };
	void set_pos(double x, double y);
	void set_pos(Point p) { set_pos(p.x, p.y); };

	double distance(GameObject* obj);
	double distance(Point p);
	double angle(Point p);


	int get_id() { return _id; };

	virtual void level_up() {};
	virtual void repair() {};
	//virtual ~GameObject();
protected:
	int _id;
	GameObject(std::string name);

	static std::string _name;
	Point _position;
	sf::Texture _texture;
	sf::Sprite _sprite;

	void render_bar(sf::RenderWindow& window,
					double value,
					double max_value,
					sf::Color left_clr = sf::Color::Green,
					sf::Color right_clr = sf::Color::Red,
					double scale = 0.9);

private:
	static int _last_id;


};

#endif