#ifndef __H_EVENT
#define __H_EVENT

// названия
class Wall;
enum class UNIT_TYPE;
class Unit;

#include <iostream>
#include <string>

class Event {
public:
	Event() {};
	virtual ~Event() {};

	virtual void activate() = 0;
	void debug(std::string msg) {
		std::cout << "[DEBUG] (Event): " << msg << "\n";
	}

	//virtual ~Event();
protected:

private:

};

//------/ GAME /-------------------
class EFinish : public Event {
public:
	EFinish(bool victory)
		: _victory(victory) {};

	virtual void activate();
private:
	bool _victory;
};


//class E_INCREASE_BALANCE : public Event {
//public:
//	E_INCREASE_BALANCE(double pp)
//		: _pp(pp) {};
//
//	virtual void activate();
//private:
//	double _pp;
//};


//------/ UNITS /------------------
class EUnitCreated : public Event {
public:
	EUnitCreated(UNIT_TYPE type, int level)
		: _type(type)
		, _level(level) {};

	virtual void activate();
private:
	UNIT_TYPE _type;
	int _level;
};

class EUnitDamage : public Event {
public:
	EUnitDamage(Unit* unit, double dp)
		: _unit(unit)
		, _dp(dp) {};

	virtual void activate();
private:
	Unit* _unit;
	double _dp;
};

class EUnitDestroyed : public Event {
public:
	EUnitDestroyed(Unit* unit)
		: _unit(unit) {};

	virtual void activate();
private:
	Unit* _unit;
};


//-----/ WALLS /-------------------
class EWallDamage : public Event {
public:
	EWallDamage(Wall* wall, double dp)
		: _wall(wall)
		, _dp(dp) {};

	virtual void activate();
private:
	Wall* _wall;
	double _dp;
};

class EWallDestroyed : public Event {
public:
	EWallDestroyed(Wall* wall)
		: _wall(wall) {};

	virtual void activate();
private:
	Wall* _wall;
};

//------/ CASTLE /-----------------

class ECastleDamage : public Event {
public:
	ECastleDamage(double dp)
		: _dp(dp) {};

	virtual void activate();
private:
	double _dp;
};

class ECastleDestroyed : public Event {
public:
	ECastleDestroyed() {};

	virtual void activate();
};

#endif


