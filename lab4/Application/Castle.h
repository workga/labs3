#ifndef __H_CASTLE
#define __H_CASTLE

#include "Table.h"
#include "GameObject.h"


struct CastleProps {
	double _max_health;
	double _recovery;
	double _profit;
	double _price;
};

class Castle : public GameObject {
public:
	Castle();

	virtual void update(double dt);
	virtual void render(sf::RenderWindow& window);

	virtual void level_up();
	virtual void repair();
	void earn(double pp);
	void heal(double hp);
	void damage(double dp);
	void destroy();

private:
	static Table<CastleProps> _table;

	int _level;
	double _max_health;
	double _health;
	double _recovery;
	double _profit;
	bool _alive;

};

#endif

