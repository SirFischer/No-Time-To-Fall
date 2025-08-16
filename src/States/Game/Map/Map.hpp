#pragma once
#include "Yuna.hpp"
#include "Block/Block.hpp"
#include <unordered_map>

typedef std::vector<std::vector<std::vector<int>>> MapData;

class Map {
	private:
		Yuna::Core::ResourceManager*				mResourceManager;
		std::unordered_map<int, Block>				mBlockDefinitions;
		size_t mTileSize = 32; 
		MapData mMapData;

	public:
		void LoadMap(Yuna::Core::ResourceManager& tResourceManager, const std::string& tMapFile);
		void Update();
		void HandleEvents();
		void Render(Yuna::Core::Window *tWindow, sf::IntRect tViewRect);

		void AddBlock(const Block& tBlock, const sf::Vector2i& tPosition);

		MapData *GetMapData() { return &mMapData; };
		std::unordered_map<int, Block>& GetBlockDefinitions() { return mBlockDefinitions; }
		size_t GetTileSize() const { return mTileSize; }
		sf::Vector2f GetNearestSafePosition(const sf::Vector2f& tPosition);

};