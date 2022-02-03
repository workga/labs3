#ifndef __H_UNIT
#define __H_UNIT

enum class SURFACE;
#include <vector>
#include "GameObject.h"

enum class UNIT_TYPE {
	LIGHT,
	HEAVY,
	AIR
};

class Unit : public GameObject {
public:
	Unit(std::string name, UNIT_TYPE type, int level);

	virtual void update(double dt);
	virtual void render(sf::RenderWindow& window);
	void print();

	virtual void heal(double hp);
	virtual void damage(double dp);
	virtual void destroy();

	//static std::vector<Point> update_default_path(
	//	std::vector<SURFACE>& allowed_surfaces);
	//void update_path(
	//	std::vector<SURFACE>& allowed_surfaces);
	//virtual void update_path() = 0;

protected:

	UNIT_TYPE _type;
	int _level;

	double _max_health;
	double _speed;
	double _recovery;
	double _damage;

	double _health;
	bool _alive;

	std::vector<Point> _path;

	virtual void move(double dt) = 0;
private:
	Point _position_noise;
};

#endif


