#pragma once
#include "Yuna.hpp"
#include "Block/Block.hpp"

typedef std::vector<std::vector<std::vector<int>>> MapData;

class Map {
	private:
		Yuna::Core::ResourceManager*				mResourceManager;
		std::map<int, Block>				mBlockDefinitions;
		size_t mTileSize = 64; 
		MapData mMapData;

	public:
		void LoadMap(Yuna::Core::ResourceManager& tResourceManager, const std::string& tMapFile);
		void Update();
		void HandleEvents();
		void Render(Yuna::Core::Window *tWindow, sf::IntRect tViewRect);

		MapData *GetMapData() { return &mMapData; };
		std::map<int, Block>& GetBlockDefinitions() { return mBlockDefinitions; }
		size_t GetTileSize() const { return mTileSize; }

};