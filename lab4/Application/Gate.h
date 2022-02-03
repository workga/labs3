#ifndef __H_GATE
#define __H_GATE


#include "Queue.h"
#include "GameObject.h"
#include "Unit.h"

struct WStep {
	UNIT_TYPE _type;
	int _level;
	int _num;
};

struct QStep {
	UNIT_TYPE _type;
	int _level;
	double _delay;
};

struct Wave {
	double _delay; //seconds
	double _gap;   //seconds

	Queue<WStep> _wsteps;
};

class Gate : public GameObject {
public:
	Gate();

	virtual void update(double dt);
	virtual void render(sf::RenderWindow& window);

	bool is_empty() { return _queue.empty(); };

private:
	Queue<QStep> _queue;
	int _units_total;

	void make_queue();
	void add_random_unit(double delay);
};

#endif


