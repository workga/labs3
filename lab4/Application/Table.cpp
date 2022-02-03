#include "Table.h"
#include "Wall.h"
#include "Tower.h"
#include "Castle.h"
#include "LightUnit.h"
#include "HeavyUnit.h"
#include "AirUnit.h"

// PLACEHOLDER

//struct LightUnitProps {
//	double _max_health;
//	double _recovery;
//	double _speed;
//	double _damage;
//};
template<>
LightUnitProps Table<LightUnitProps>::levels[] = {
	{ 3, 0.3, 3, 0.3 },
	{ 4, 0.4, 4, 0.4 },
	{ 5, 0.5, 5, 0.5 }
};

//struct HeavyUnitProps {
//	double _max_health;
//	double _recovery;
//	double _speed;
//	double _damage;
//};
template<>
HeavyUnitProps Table<HeavyUnitProps>::levels[] = {
	{ 6, 0.6, 1.5, 0.6 },
	{ 8, 0.8, 2, 0.8 },
	{ 10, 1, 2.5, 1 }
};

//struct AirUnitProps {
//	double _max_health;
//	double _recovery;
//	double _speed;
//	double _damage;
//	double _bomb_damage;
//};
template<>
AirUnitProps Table<AirUnitProps>::levels[] = {
	{ 3, 0.3, 1.5, 1.5, 5 },
	{ 4, 0.4, 2, 2, 10 },
	{ 5, 0.5, 2.5, 2.5, 15 }
};

//struct WallProps {
//	double _max_health;
//	double _recovery;
//  double _price;
//};
template<>
WallProps Table<WallProps>::levels[] = {
	{ 10, 1, 1 },
	{ 20, 2, 2 },
	{ 30, 3, 3 }
};

//struct TowerProps {
//	double _radius;
//	double _max_stamina; // amount of hp that tower can substract from unit without charging
//	double _damage; // damage rate, hp/sec
//	double _charging; // charge rate factor, (hp/sec)*100%
//  double _price;
//};
template<>
TowerProps Table<TowerProps>::levels[] = {
	{ 3, 3, 2, 0.3, 2 },
	{ 4, 4, 4, 0.4, 4 },
	{ 5, 5, 6, 0.5, 6 }
};

//struct CastleProps {
//	double _max_health;
//	double _recovery;
//	double _profit;
//  double _price;
//};
template<>
CastleProps Table<CastleProps>::levels[] = {
	{ 60, 1, 1, 2 },
	{ 80, 2, 2, 4 },
	{ 100, 3, 3, 6 }
};
//