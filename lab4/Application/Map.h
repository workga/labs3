#ifndef __H_MAP
#define __H_MAP

#include <vector>
#include "SFML/Graphics.hpp"
#include "GameObject.h"

enum class UNIT_TYPE;
class Gate;
class Castle;
class IBuilding;

enum class SURFACE {
	GRASS,
	WATER,
	HILL,

	ROAD,

	GATE,
	WALL,
	TOWER,
	CASTLE,

	NONE
};


struct Tile {
	SURFACE _base;
	SURFACE _surface;
	bool _is_busy;
	GameObject* _building;
	sf::Sprite _sprite;
};


class Map {
public:
	static const int _TILE_SIZE = 64;
	static const int _SIZE = 10;

	void init(int level);
	void print();
	void render(sf::RenderWindow& window);

	int get_size();
	Tile& get_tile(int xi, int yi);

	Point get_start_pos();
	Point get_finish_pos();

	void set_gate(Gate* gate);
	void set_castle(Castle* castle);

	std::vector<Point> make_path(UNIT_TYPE type);

private:
	std::map<SURFACE, sf::Texture> _textures;
	static const int _NUM_OF_MAPS = 3;
	static const int _default_maps[_NUM_OF_MAPS][_SIZE][_SIZE];

	SURFACE _scheme[_SIZE][_SIZE];
	struct Node {
		bool _visited = false;
		std::vector<Point> _adjs;
	};
	Node _graph[_SIZE][_SIZE];

	std::vector<std::vector<Tile>> _tiles; 

	Point _start_pos;
	Point _finish_pos;


	void set_size(int size);
	void set_tile_base(int xi, int yi, SURFACE base);
	void set_tile_surface(int xi, int yi, SURFACE surface);
	
	void make_graph();
};



#endif


