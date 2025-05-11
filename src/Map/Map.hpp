#pragma once
#include "Yuna.hpp"

class Map {

	public:
		Map();
		~Map();

		void LoadMap(const std::string& mapFile);
		void Update();
		void HandleEvents();
		void Render();
};