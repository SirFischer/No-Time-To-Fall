#include "Map.hpp"
#include <cmath>
#include <algorithm>


void Map::LoadMap(Yuna::Core::ResourceManager& tResourceManager, const std::string& mapFile)
{
	mResourceManager = &tResourceManager;
	std::ifstream file(mapFile);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open map file: " + mapFile);
	}

	while (file.good())
	{
		std::string line;
		std::getline(file, line);
		if (line.empty() || line[0] == '#') // Comment or empty line
			continue;
		
		if (line.find("signature") != std::string::npos)
		{
			//data example: signature=34 assets/textures/blocks/grass.jpg
			auto pos = line.find('=');
			if (pos == std::string::npos)
			{
				throw std::runtime_error("Invalid signature line in map file: " + line);
			}
			std::string signature = line.substr(pos + 1, line.find(' ', pos + 1) - pos - 1);
			int blockID = std::stoi(signature);
			std::string texturePath = "assets/maps/" + line.substr(line.find(' ', pos + 1) + 1);

			Block def;
			def.SetSize(sf::Vector2f(mTileSize, mTileSize));
			def.SetTexture(*tResourceManager.LoadTexture(texturePath));
			mBlockDefinitions[blockID] = def;
			continue;
		}

		if (line.find("map") != std::string::npos)
		{
			/**
			 	map=
				elem=34
				gpos=5 0
				pos=500.937500 0.812500
			 */
			while (std::getline(file, line) && !line.empty())
			{
				if (line.find("elem=") != std::string::npos)
				{
					auto pos = line.find('=');
					if (pos == std::string::npos)
					{
						throw std::runtime_error("Invalid elem line in map file: " + line);
					}
					
					int blockID = std::stoi(line.substr(pos + 1));

					if (mBlockDefinitions.find(blockID) == mBlockDefinitions.end())
					{
						throw std::runtime_error("Block ID " + std::to_string(blockID) + " not defined in map file: " + mapFile);
					}

					std::getline(file, line); // Read gpos line

					if (line.find("gpos=") != std::string::npos)
					{
						auto gposPos = line.find('=');
						if (gposPos == std::string::npos)
						{
							throw std::runtime_error("Invalid gpos line in map file: " + line);
						}
						std::string gposStr = line.substr(gposPos + 1);
						std::istringstream gposStream(gposStr);
						int gridX, gridY;
						gposStream >> gridX >> gridY;

						if (gridX >= (int)mMapData.size()) {
							mMapData.resize(gridX + 1);
							for (auto& column : mMapData) {
								column.reserve(50);
							}
						}
						if (gridY >= (int)mMapData[gridX].size()) {
							mMapData[gridX].resize(gridY + 1);
						}

						mMapData[gridX][gridY].push_back(blockID);
					}
				}
			}
		}
	}
}

sf::Vector2f Map::GetNearestSafePosition(const sf::Vector2f& tPosition)
{
	if (mMapData.empty()) {
		return tPosition;
	}

	int gridX = static_cast<int>(std::floor(tPosition.x / mTileSize));

	for (int offset = 0; offset < 10; ++offset) {
		if (gridX - offset >= 0 && gridX - offset < (int)mMapData.size()) {
			for (int y = 0; y < (int)mMapData[gridX - offset].size(); ++y) {
				if (!mMapData[gridX - offset][y].empty()) {
					return (sf::Vector2f((gridX - offset) * mTileSize, (y - 1) * mTileSize));
				}
			}
		}
	}

	return tPosition;
}

void Map::AddBlock(const Block& tBlock, const sf::Vector2i& tPosition)
{
	if (tPosition.x < 0 || tPosition.y < 0)
		return;

	// Ensure the map data is large enough
	if (tPosition.x >= (int)mMapData.size()) {
		mMapData.resize(tPosition.x + 1);
	}
	if (tPosition.y >= (int)mMapData[tPosition.x].size()) {
		mMapData[tPosition.x].resize(tPosition.y + 1);
	}

	if (!mMapData[tPosition.x][tPosition.y].empty())
	{
		return;
	}

	int blockID = -1;

	for(const auto& pair : mBlockDefinitions)
	{
		if (tBlock == pair.second)
		{
			blockID = pair.first;
			break;
		}
	}

	if (blockID == -1)
	{
		blockID = static_cast<int>(mBlockDefinitions.size());
		mBlockDefinitions[blockID] = tBlock;
	}

	mMapData[tPosition.x][tPosition.y].push_back(blockID);
}





void Map::Update()
{
}

void Map::HandleEvents()
{
}

void Map::Render(Yuna::Core::Window *tWindow, sf::IntRect tViewRect)
{
	const int mapWidth = static_cast<int>(mMapData.size());
	int startX = std::max(0, tViewRect.left);
	int endX = std::min(mapWidth, tViewRect.left + tViewRect.width);
	
	for (int i = startX; i < endX; ++i)
	{
		const auto& column = mMapData[i];
		const int mapHeight = static_cast<int>(column.size());
		int startY = std::max(0, tViewRect.top);
		int endY = std::min(mapHeight, tViewRect.top + tViewRect.height);
		
		for (int j = startY; j < endY; ++j)
		{
			const auto& blockIDs = column[j];
			
			if (blockIDs.empty()) continue;
			
			for (const int blockID : blockIDs)
			{
				auto blockIt = mBlockDefinitions.find(blockID);
				if (blockIt != mBlockDefinitions.end()) {
					Block& block = blockIt->second;
					const sf::Vector2f blockSize = block.GetSize();
					block.SetPosition(sf::Vector2f(i * blockSize.x, j * blockSize.y));
					block.Render(tWindow);
				}
			}
		}
	}
}