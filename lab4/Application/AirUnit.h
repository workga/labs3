#ifndef __H_AIR_UNIT
#define __H_AIR_UNIT

#include "Table.h"
#include "Unit.h"

struct AirUnitProps {
	double _max_health;
	double _recovery;
	double _speed;
	double _damage;
	double _bomb_damage;
};

class AirUnit : public Unit {
public:
	AirUnit(int level);

	void create_path();

protected:
	virtual void set_level(int level);

private:
	static Table<AirUnitProps> _table;
	virtual void move(double dt);

	double _bomb_damage;

	void bomb(Point p);
};

#endif

