#include "Map.hpp"


void Map::LoadMap(Yuna::Core::ResourceManager& tResourceManager, const std::string& mapFile)
{
	std::ifstream file(mapFile);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open map file: " + mapFile);
	}

	while (file.good())
	{
		std::string line;
		std::getline(file, line);
		// Process the line to extract block information
		if (line.empty() || line[0] == '#') // Skip empty lines and comments
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

			mBlockDefinitions[blockID] = Block();
			mBlockDefinitions[blockID].SetSize(sf::Vector2f(mTileSize, mTileSize)); // Set default size, can be adjusted later
			mBlockDefinitions[blockID].SetTexture(*tResourceManager.LoadTexture(texturePath));
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
					std::cout << "Processing elem line: " << line << std::endl;
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

						// Ensure the map data is large enough
						if (gridX >= (int)mMapData.size())
							mMapData.resize(gridX + 1);
						if (gridY >= (int)mMapData[gridX].size())
							mMapData[gridX].resize(gridY + 1);

						// Add the block ID to the map data
						mMapData[gridX][gridY].push_back(blockID);
					}
				}
			}
		}
	}

	for (const auto& blockDef : mBlockDefinitions)
	{
		std::cout << "Block ID: " << blockDef.first << std::endl;

	}

}

void Map::Update()
{
}

void Map::HandleEvents()
{
}

void Map::Render(Yuna::Core::Window *tWindow, sf::IntRect tViewRect)
{
	for (int i = tViewRect.left; i < tViewRect.left + tViewRect.width; ++i)
	{
		for (int j = tViewRect.top; j < tViewRect.top + tViewRect.height; ++j)
		{
			if (i >= 0 && i < (int)mMapData.size() && j >= 0 && j < (int)mMapData[i].size())
			{
				for (const auto& blockID : mMapData[i][j])
				{
					auto block = mBlockDefinitions[blockID];
					block.SetPosition(sf::Vector2f(i * block.GetSize().x, j * block.GetSize().y));
					block.Render(tWindow);
				}
			}
		}
	}
}