#ifndef __H_HEAVY_UNIT
#define __H_HEAVY_UNIT

#include "Table.h"
#include "Unit.h"

struct HeavyUnitProps {
	double _max_health;
	double _recovery;
	double _speed;
	double _damage;
};

class HeavyUnit : public Unit {
public:
	HeavyUnit(int level);

	void create_path();

protected:
	virtual void set_level(int level);

private:
	static Table<HeavyUnitProps> _table;

	virtual void move(double dt);

	void attack(Point p);
};

#endif

