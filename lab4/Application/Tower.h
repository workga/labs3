#ifndef __H_TOWER
#define __H_TOWER

#include "Table.h"
#include "GameObject.h"


class Unit;

struct TowerProps {
	double _radius;
	double _max_stamina; // amount of hp that tower can substract from unit without charging
	double _damage; // damage rate, hp/sec
	double _charging; // charge rate factor, (hp/sec)*100%
	double _price;
};

class Tower : public GameObject {
public:
	static Table<TowerProps> _table;

	Tower();
	void print();

	virtual void update(double dt);
	virtual void render(sf::RenderWindow& window);

	virtual void level_up();
	void charge(double dc);
	Unit* find_target(std::vector<Unit*>* units);
	void shoot(double dt);
private:

	int _level;

	double _radius;
	double _max_stamina;
	double _damage;
	double _charging;
	double _stamina;

	bool _charged;
	bool _shoot;

	int _target_id;
	Unit* _target_unit;
};

#endif