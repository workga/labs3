#ifndef __H_WALL
#define __H_WALL

#include "Table.h"
#include "GameObject.h"

struct WallProps {
	double _max_health;
	double _recovery;
	double _price;
};

class Wall : public GameObject {
public:
	static Table<WallProps> _table;
	Wall();

	virtual void update(double dt);
	virtual void render(sf::RenderWindow& window);

	virtual void level_up();
	virtual void repair();
	void heal(double hp);
	void damage(double dp);
	void destroy();
private:

	int _level;
	double _max_health;
	double _health;
	double _recovery;
	bool _alive;


};

#endif

