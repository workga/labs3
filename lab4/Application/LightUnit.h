#ifndef __H_LIGHT_UNIT
#define __H_LIGHT_UNIT

#include "Table.h"
#include "Unit.h"

struct LightUnitProps {
	double _max_health;
	double _recovery;
	double _speed;
	double _damage;
};

class LightUnit : public Unit {
public:
	LightUnit(int level);
	void create_path();

protected:
	virtual void set_level(int level);

private:
	static Table<LightUnitProps> _table;
	virtual void move(double dt);
};

#endif

