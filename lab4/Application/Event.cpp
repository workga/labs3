#include "iostream"

#include "Event.h"

#include "Game.h"

#include "Unit.h"
	#include "LightUnit.h"
	#include "HeavyUnit.h"
	#include "AirUnit.h"
#include "Wall.h"
#include "Castle.h"

//------/ GAME /------------------
void EFinish::activate() {
	Game::game().finish(_victory);
	debug("Game over.");
}


//void E_INCREASE_BALANCE::activate() {
//	Game::game().increase_balance(_pp);
//	
//}


//------/ UNITS /------------------
void EUnitCreated::activate() {
	Game::game().add_unit(_type, _level);

	double et = Game::game().elapsed_time();
	//debug(std::to_string(et));
	//debug("Unit created.");
}

void EUnitDamage::activate() {
	_unit->damage(_dp);

	//debug("Unit damaged");
}

void EUnitDestroyed::activate() {
	Game::game().remove_unit(_unit);

	/*debug("Unit destroyed");*/
}

//-----/ WALL /------------------
void EWallDamage::activate() {
	_wall->damage(_dp);

	debug("Wall damaged");
	std::cout << "dp: " << _dp << "\n";
}

void EWallDestroyed::activate() {
	Game::game().remove_wall(_wall);
	debug("Wall destroyed");
}


//-----/ CASTLE /------------------
void ECastleDamage::activate() {
	Game::game().get_castle()->damage(_dp);

	debug("Castle damaged");
}

void ECastleDestroyed::activate() {
	Game::game().add_event(new EFinish(false));
	debug("Castle destroyed");
}

