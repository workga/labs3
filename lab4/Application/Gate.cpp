#include<iostream>
#include <ctime>
#include "Map.h"
#include "Game.h"
#include "Event.h"
#include "Gate.h"

#define RANDOM_WAVE true
#define RANDOM_WAVE_SIZE 100

Gate::Gate()
	: GameObject("Gate") {
	
	if (!_texture.loadFromFile("./sprites/gate_01.png")) {
		throw std::runtime_error("Can't load texture from file.");
	}
	_sprite.setTexture(_texture);
	_sprite.setOrigin(Map::_TILE_SIZE / 2, Map::_TILE_SIZE / 2);

	make_queue();
}

void Gate::update(double dt) {
	if (_queue.empty()) return;

	double time_elapsed = Game::game().elapsed_time();
	
	QStep& qstep = _queue.front();
	if (qstep._delay <= time_elapsed) {
		Game::game().add_event(new EUnitCreated(qstep._type, qstep._level));
		_queue.pop();
	}
}

void Gate::render(sf::RenderWindow& window) {
	window.draw(_sprite);

	render_bar(window, _queue.size(), _units_total, sf::Color::Magenta, sf::Color::Black);
}

void Gate::make_queue() {

	if (RANDOM_WAVE) {
		for (int i = 0; i < RANDOM_WAVE_SIZE; i++) {
			add_random_unit(i);
		}
	}
	else {
		// placeholder


		//struct Wave {
		//	double _delay; //seconds
		//	double _gap;   //seconds

		//	Queue<WStep> _wsteps;
		//};

		//struct WStep {
		//	UNIT_TYPE _type;
		//	int _level;
		//	int _num;
		//};
		Wave waves[] = {
			{10, 1},
			{10, 1},
			{10, 1},
		};


		waves[0]._wsteps.push({ UNIT_TYPE::HEAVY, 1, 3 });
		waves[0]._wsteps.push({ UNIT_TYPE::LIGHT, 1, 3 });
		waves[0]._wsteps.push({ UNIT_TYPE::AIR, 1, 3 });

		waves[1]._wsteps.push({ UNIT_TYPE::HEAVY, 2, 3 });
		waves[1]._wsteps.push({ UNIT_TYPE::LIGHT, 2, 3 });
		waves[1]._wsteps.push({ UNIT_TYPE::AIR, 2, 3 });

		waves[2]._wsteps.push({ UNIT_TYPE::HEAVY, 3, 3 });
		waves[2]._wsteps.push({ UNIT_TYPE::LIGHT, 3, 3 });
		waves[2]._wsteps.push({ UNIT_TYPE::AIR, 3, 3 });


		double delay = 0;
		for (auto& w : waves) {
			delay += w._delay;

			while (!w._wsteps.empty()) {
				auto& wstep = w._wsteps.front();
				QStep qstep = {
					wstep._type,
					wstep._level,
					delay
				};
				_queue.push(qstep);

				delay += w._gap;

				wstep._num--;
				if (wstep._num <= 0)
					w._wsteps.pop();
			}
			delay -= w._gap;
		}
	}

	_units_total = _queue.size();

	// debug
	std::cout << "[DEBUG] Gate's queue content (UNIT_TYPE, level, delay):\n";
	auto queue_copy = _queue;
	while (!queue_copy.empty()) {
		auto& qstep = queue_copy.front();
		std::cout << static_cast<int>(qstep._type) << " " <<
					 qstep._level << " " <<
					 qstep._delay << "\n";
		queue_copy.pop();
	}
	//
}

void Gate::add_random_unit(double delay) {
	if (!_queue.empty())
		std::cout << _queue.front()._delay << "\n";
	_queue.push({
		static_cast<UNIT_TYPE>(rand() % 3),
		(rand() % 3 + 1),
		delay
	});
}