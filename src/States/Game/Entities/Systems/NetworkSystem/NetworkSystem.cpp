#include "NetworkSystem.hpp"
#include "../../../World.hpp"
#include "../../../Networking/NetworkManager.hpp"
#include "../../Components/TransformComponent.hpp"
#include "../../Components/InputComponent.hpp"
#include "../../Components/VelocityComponent.hpp"
#include "../../Components/NetworkComponent.hpp"


NetworkSystem::NetworkSystem(World *world, NetworkManager *networkManager)
	: mWorld(world), mNetworkManager(networkManager) {}

void NetworkSystem::Update(float deltaTime)
{
	(void)deltaTime;
	if (!mNetworkManager) { return; }

	if (mNetworkManager->GetMode() == NetworkMode::HOST)
	{
		if (mNetworkManager->CheckForNewClient())
		{
			std::cout << "New client connected." << std::endl;
		}
		if (mNetworkManager->IsClientConnected()) {
			ReceiveInput();
			SendWorldState();
		}
	}
	else
	{
		auto entities = mWorld->GetEntitiesWith<TransformComponent, InputComponent, NetworkComponent>();
		for (EntityID entity : entities) {
			SendInput(entity);
		}
		ReceiveWorldState();
	}
}

bool NetworkSystem::ShouldProcessEntity(EntityID entity)
{
	return mWorld->HasComponent<TransformComponent>(entity) && mWorld->HasComponent<InputComponent>(entity) && 
	       mWorld->HasComponent<NetworkComponent>(entity);
}


void NetworkSystem::SendInput(EntityID entity)
{
	auto* input = mWorld->GetComponent<InputComponent>(entity);
	
	if (!input || !input->enabled) {
		return;
	}

	sf::Packet packet;
	packet << static_cast<int>(PacketType::MOVE);
	packet << entity;
	packet << input->isMovingRight << input->isMovingLeft << input->isJumping << input->isCrouching;

	if (mNetworkManager->GetMode() == NetworkMode::CLIENT) {
		mNetworkManager->SendUDPPacket(packet);
	}
}

void NetworkSystem::ReceiveInput()
{
	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;

	while (mNetworkManager->ReceiveUDPPacket(packet, sender, port) == sf::Socket::Status::Done)
	{
		
		int packetType;
		if (!(packet >> packetType)) {
			continue;
		}

		if (packetType == static_cast<int>(PacketType::MOVE)) {
			EntityID entityId;
			bool isMovingRight, isMovingLeft, isJumping, isCrouching;

			if (packet >> entityId >> isMovingRight >> isMovingLeft >> isJumping >> isCrouching)
			{
				auto* input = mWorld->GetComponent<InputComponent>(entityId);

				if (!input) {
					std::cerr << "InputComponent not found for entity ID: " << entityId << std::endl;
					continue;
				}

				input->isMovingRight = isMovingRight;
				input->isMovingLeft = isMovingLeft;
				input->isJumping = isJumping;
				input->isCrouching = isCrouching;
			}
		}
	}
}

void NetworkSystem::SendWorldState()
{
	if (!mNetworkManager || mNetworkManager->GetMode() != NetworkMode::HOST) {
		return;
	}

	sf::Packet packet;
	packet << static_cast<int>(PacketType::STATE_UPDATE);

	auto entities = mWorld->GetEntitiesWith<TransformComponent, NetworkComponent>();
	packet << static_cast<uint32_t>(entities.size());

	for (EntityID entity : entities) {
		auto* transform = mWorld->GetComponent<TransformComponent>(entity);
		auto* network = mWorld->GetComponent<NetworkComponent>(entity);
		
		packet << entity;

		packet << transform->x << transform->y;
		
		bool hasInput = mWorld->HasComponent<InputComponent>(entity);
		packet << hasInput;
		if (hasInput) {
			auto* input = mWorld->GetComponent<InputComponent>(entity);
			bool enabledForClient = !input->enabled && !network->isLocalPlayer;
			packet << enabledForClient;
		}
	}

	mNetworkManager->SendUDPPacket(packet);
}

void NetworkSystem::ReceiveWorldState()
{
	if (!mNetworkManager || mNetworkManager->GetMode() != NetworkMode::CLIENT) {
		return;
	}

	sf::Packet packet;
	sf::IpAddress sender;
	unsigned short port;

	while (mNetworkManager->ReceiveUDPPacket(packet, sender, port) == sf::Socket::Status::Done) {
		int packetType;
		if (!(packet >> packetType)) {
			std::cerr << "Failed to read packet type" << std::endl;
			continue;
		}

		if (packetType != static_cast<int>(PacketType::STATE_UPDATE)) {
			std::cerr << "Received non-state packet type: " << packetType << std::endl;
			continue;
		}

		uint32_t entityCount;
		if (!(packet >> entityCount)) {
			std::cerr << "Failed to read entity count from state packet" << std::endl;
			continue;
		}

		for (uint32_t i = 0; i < entityCount; ++i) {
			uint32_t targetEntity;
			float x, y;
			
			if (!(packet >> targetEntity >> x >> y)) {
				std::cerr << "Failed to read entity " << i << " transform data" << std::endl;
				break;
			}

			auto* transform = mWorld->GetComponent<TransformComponent>(targetEntity);
			auto* velocity = mWorld->GetComponent<VelocityComponent>(targetEntity);
			if (transform && velocity) {
				transform->x = x;
				transform->y = y;
				velocity->vx = 0.0f;
				velocity->vy = 0.0f;
			}

			bool hasInput;
			if (!(packet >> hasInput)) {
				std::cerr << "Failed to read input flag for entity " << targetEntity << std::endl;
				break;
			}

			if (hasInput) {
				bool enabledForClient;
				if (!(packet >> enabledForClient)) {
					std::cerr << "Failed to read input data for entity " << targetEntity << std::endl;
					break;
				}

				auto* input = mWorld->GetComponent<InputComponent>(targetEntity);
				if (input) {
					input->enabled = enabledForClient;
				}
			}
		}
	}
}