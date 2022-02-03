#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <random>
#include <functional>
#include <vector>

#include "Unit.h"
#include "Gate.h"
#include "Wall.h"
#include "Castle.h"
#include "Map.h"
#include "Game.h"

#define DEFAULT_MAP_N -1

const int Map::_default_maps[_NUM_OF_MAPS][_SIZE][_SIZE] = {
	{
		{0, 3, 3, 3, 3, 3, 3, 3, 3, 3},
		{3, 0, 0, 0, 0, 3, 1, 1, 1, 3},
		{3, 0, 2, 2, 0, 3, 0, 0, 1, 3},
		{3, 0, 2, 2, 0, 3, 3, 0, 1, 3},
		{3, 0, 0, 0, 0, 0, 3, 3, 3, 3},
		{3, 3, 3, 3, 0, 0, 0, 0, 3, 0},
		{3, 1, 0, 3, 3, 0, 0, 0, 3, 0},
		{3, 1, 0, 0, 3, 0, 0, 0, 3, 0},
		{3, 1, 1, 1, 3, 3, 3, 3, 3, 3},
		{3, 3, 3, 3, 3, 0, 0, 0, 3, 0}
	},
	{
		{0, 3, 0, 1, 0, 0, 0, 0, 1, 0},
		{0, 3, 0, 1, 1, 1, 1, 1, 1, 0},
		{0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 3, 3, 3, 3, 3, 3, 3, 0},
		{0, 0, 0, 0, 3, 0, 0, 0, 3, 0},
		{1, 1, 1, 0, 3, 0, 2, 0, 3, 0},
		{2, 2, 1, 0, 3, 0, 2, 0, 3, 0},
		{2, 2, 1, 0, 3, 0, 0, 0, 3, 0},
		{2, 2, 1, 0, 3, 3, 3, 3, 3, 0},
		{2, 2, 1, 0, 0, 0, 0, 0, 3, 0}
	},
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{3, 3, 3, 3, 3, 3, 3, 3, 3, 0},
		{0, 3, 0, 0, 0, 0, 0, 0, 3, 0},
		{0, 3, 3, 3, 3, 3, 3, 3, 3, 0},
		{0, 0, 3, 2, 2, 2, 2, 3, 0, 0},
		{0, 3, 3, 3, 3, 3, 3, 3, 3, 0},
		{0, 3, 0, 0, 0, 0, 0, 0, 3, 0},
		{0, 3, 1, 1, 1, 1, 1, 1, 3, 0},
		{0, 3, 0, 0, 0, 0, 0, 0, 3, 0},
		{0, 3, 3, 3, 3, 3, 3, 3, 3, 0}
	},
};


void Map::init(int level) {
	if (!(
		_textures[SURFACE::GRASS].loadFromFile("./sprites/grass_01.png") &&
		_textures[SURFACE::WATER].loadFromFile("./sprites/water_01.png") &&
		_textures[SURFACE::HILL].loadFromFile("./sprites/hill_01.png") &&
		_textures[SURFACE::ROAD].loadFromFile("./sprites/path_01.png")
		)) {
		throw std::runtime_error("Can't load texture from file");
	}

	set_size(_SIZE);

	int map_n = (DEFAULT_MAP_N >= 0) ? DEFAULT_MAP_N : rand() % _NUM_OF_MAPS;

	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			_scheme[i][j] = static_cast<SURFACE>(_default_maps[map_n][i][j]);

			Tile& tile = _tiles[i][j];

			tile._base = static_cast<SURFACE>(_scheme[i][j]);
			tile._surface = SURFACE::NONE;
			tile._is_busy = false;
			tile._building = nullptr;
			tile._sprite.setTexture(_textures[tile._base]);
			tile._sprite.setPosition(sf::Vector2f(j*_TILE_SIZE + _TILE_SIZE / 2,
												  i*_TILE_SIZE + _TILE_SIZE / 2));
			tile._sprite.setOrigin(_TILE_SIZE/2, _TILE_SIZE/ 2);
		}
	}

	_start_pos = { 0, 0 };
	_finish_pos = { static_cast<double>(_SIZE - 1),
					static_cast<double>(_SIZE - 1)};

	make_graph();

}

void Map::print() {
	std::cout << "[OUTPUT] Tiles:\n"; 
	for (auto& v : _tiles) {
		for (auto& t : v) {
			SURFACE s = (t._surface == SURFACE::NONE) ? t._base : t._surface;
			std::cout << static_cast<int>(s) << " ";
		}
		std::cout << "\n";
	}

	std::cout << "[OUTPUT] Scheme:\n";
	for (auto& v : _scheme) {
		for (auto& t : v) {
			std::cout << static_cast<int>(t) << " ";
		}
		std::cout << "\n";
	}

	std::cout << "[OUTPUT] Graph:\n";
	for (auto& v : _graph) {
		for (auto& t : v) {
			std::cout << t._adjs.size() << " ";
		}
		std::cout << "\n";
	}


}

void Map::render(sf::RenderWindow& window) {
	for (auto& v : _tiles) {
		for (auto& t : v) {
			window.draw(t._sprite);
		}
	}
}

void Map::make_graph() {
	for (int i = 0; i < _SIZE; i++) {
		for (int j = 0; j < _SIZE; j++) {
			Node& cur_node = _graph[i][j];

			if (_scheme[i][j] == SURFACE::ROAD || 
				Point(i, j) == _start_pos ||
				Point(i, j) == _finish_pos) {
				// set Node.is_road ??

				if (j > 0 && (_scheme[i][j - 1] == SURFACE::ROAD ||
							  Point(i, j - 1) == _start_pos)) {

					cur_node._adjs.push_back(Point(i, j - 1));
				}
				if (j < _SIZE - 1 && (_scheme[i][j + 1] == SURFACE::ROAD ||
									  Point(i, j + 1) == _finish_pos)) {

					cur_node._adjs.push_back(Point(i, j + 1));
				}
				if (i > 0 && (_scheme[i - 1][j] == SURFACE::ROAD ||
							 Point(i, j - 1) == _start_pos)) {

					cur_node._adjs.push_back(Point(i - 1, j));
				}
				if (i < _SIZE - 1 && (_scheme[i + 1][j] == SURFACE::ROAD ||
									  Point(i, j + 1) == _finish_pos)) {

					cur_node._adjs.push_back(Point(i + 1, j));
				}
			}
		}
	}
}

std::vector<Point> Map::make_path(UNIT_TYPE type) {


	// LIGHT_UNIT and HEAVY_UNIT path
	if (type == UNIT_TYPE::LIGHT || type == UNIT_TYPE::HEAVY) {
		// create copy of the graph and shuffle _adjs
		Node graph[_SIZE][_SIZE];

		static auto rng = std::default_random_engine{};
		for (int i = 0; i < _SIZE; i++) {
			for (int j = 0; j < _SIZE; j++) {
				graph[i][j] = _graph[i][j];
				std::shuffle(std::begin(graph[i][j]._adjs), std::end(graph[i][j]._adjs), rng);
			}
		}
		//

		// find path
		std::vector<Point> path;
		std::function<bool(Point p)> dfs;
		dfs = [&dfs, &graph, &path, this](Point p) -> bool {
			//std::cout << "DFS: Current point: (" << p.x << ", " << p.y << ")\n";

			if (p == _finish_pos) {
				path.push_back(p);
				return true;
			}

			Node& node = graph[(int)(p.x)][(int)(p.y)];
			node._visited = true;

			for (auto& adj_p : node._adjs) {
				Node& adj_node = graph[(int)(adj_p.x)][(int)(adj_p.y)];

				if (!adj_node._visited) {
					if (dfs(adj_p)) {
						path.push_back(p);
						return true;
					}
				}
			}

			return false;
		};

		dfs(_start_pos);
		std::reverse(path.begin(), path.end());
		return path;

	}
	// AIR_UNIT path
	else if ( type == UNIT_TYPE::AIR ){
		std::vector<Point> path;
		std::vector<Wall*>* walls = Game::game().get_walls();
		
		if (!walls->empty()) {
			Wall* w = (*walls)[rand() % walls->size()];
			Point wp = w->get_pos();

			path.push_back(wp);
		}
		path.push_back(_finish_pos);
		return path;
	}

}

int Map::get_size() {
	return _SIZE;
}

Tile& Map::get_tile(int xi, int yi) {
	return _tiles[xi][yi];
}


Point Map::get_start_pos() {
	return _start_pos;
}

Point Map::get_finish_pos() {
	return _finish_pos;
}

void Map::set_gate(Gate* gate) {
	Tile& gate_tile = _tiles[_start_pos.x][_start_pos.y];
	gate_tile._surface = SURFACE::GATE;
	gate_tile._is_busy = true;
	//gate_tile._building = gate;
}

void Map::set_castle(Castle* castle) {
	Tile& castle_tile = _tiles[_finish_pos.x][_finish_pos.y];
	castle_tile._surface = SURFACE::CASTLE;
	castle_tile._is_busy = true;
	castle_tile._building = castle;
}


void Map::set_size(int size) {
	_tiles.resize(size);
	for (auto& v : _tiles) 
		v.resize(size); 
}

void Map::set_tile_base(int xi, int yi, SURFACE base) {
	_tiles[xi][yi]._base = base;
}

void Map::set_tile_surface(int xi, int yi, SURFACE surface) {
	_tiles[xi][yi]._surface = surface;
}
