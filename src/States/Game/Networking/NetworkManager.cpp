#include "NetworkManager.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdint>

NetworkManager::~NetworkManager() {
	Cleanup();
}

void NetworkManager::Cleanup() {
	mSocket.setBlocking(false);
	mUdpSocket.setBlocking(false);
	mListener.setBlocking(false);

	mSocket.disconnect();
	mUdpSocket.unbind();
	mListener.close();
}

bool NetworkManager::ConnectToServer(const std::string& ip, unsigned short port) {
	if (mMode != NetworkMode::CLIENT) {
		throw std::runtime_error("NetworkManager is not in CLIENT mode.");
	}

	sf::Socket::Status status = mSocket.connect(ip, port);
	if (status != sf::Socket::Done) {
		throw std::runtime_error("Failed to connect to server: " + std::to_string(static_cast<int>(status)));
	}

	mServerIp = sf::IpAddress(ip);
	mServerPort = port;

	if (mUdpSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
		throw std::runtime_error("Failed to bind UDP socket to any available port");
	}

	mUdpSocket.setBlocking(false);
	
	// Get the actual UDP port that was bound
	unsigned short clientUdpPort = mUdpSocket.getLocalPort();
	std::cout << "Client bound to UDP port: " << clientUdpPort << std::endl;

	sf::Packet handshakePacket;
	handshakePacket << static_cast<int>(PacketType::CONNECT) << clientUdpPort;
	mSocket.send(handshakePacket);
	std::cout << "Sent handshake with UDP port: " << clientUdpPort << std::endl;
	
	mSocket.receive(handshakePacket);
	if (handshakePacket.getDataSize() == 0) {
		throw std::runtime_error("Failed to receive handshake packet from server.");
	}
	std::cout << "Handshake successful. Connected to server at " << ip << ":" << port << std::endl;

	std::cout << "Connected to server at " << mServerIp.toString() << ":" << mServerPort << std::endl;

	return true;
}

void NetworkManager::StartServer(unsigned short port) {
	if (mMode != NetworkMode::HOST) {
		throw std::runtime_error("NetworkManager is not in HOST mode.");
	}

	sf::Socket::Status status = mListener.listen(port);
	if (status != sf::Socket::Done) {
		throw std::runtime_error("Failed to start server: " + std::to_string(static_cast<int>(status)));
	}

	mListener.setBlocking(false);

	mServerIp = sf::IpAddress::getLocalAddress();
	mServerPort = port;

	sf::Socket::Status udpStatus = mUdpSocket.bind(port);
	if (udpStatus != sf::Socket::Done) {
		std::cout << "Failed to bind UDP socket to port " << port << ", trying alternative ports..." << std::endl;
		
		for (unsigned short altPort = port + 1; altPort <= port + 10; ++altPort) {
			udpStatus = mUdpSocket.bind(altPort);
			if (udpStatus == sf::Socket::Done) {
				std::cout << "UDP socket bound to alternative port: " << altPort << std::endl;
				break;
			}
		}
		
		if (udpStatus != sf::Socket::Done) {
			throw std::runtime_error("Failed to bind UDP socket to port " + std::to_string(port) + " or any alternative port");
		}
	}

	mUdpSocket.setBlocking(false);

	std::cout << "Server started on IP " << mServerIp.toString() << " and port " << mServerPort << std::endl;
	std::cout << "Waiting for clients to connect..." << std::endl;
}

bool NetworkManager::CheckForNewClient() {
	if (mMode != NetworkMode::HOST || mClientConnected) {
		return false;
	}
	
	sf::Socket::Status status = mListener.accept(mSocket);
	if (status == sf::Socket::Done) {
		mClientConnected = true;
		sf::IpAddress clientIp = mSocket.getRemoteAddress();
		std::cout << "Client connected: " << clientIp.toString() << std::endl;
		
		sf::Packet handshakePacket;
		mSocket.receive(handshakePacket);
		
		int packetType;
		unsigned short clientUdpPort;
		if (handshakePacket >> packetType >> clientUdpPort && packetType == static_cast<int>(PacketType::CONNECT)) {
			SetClientUDPAddress(clientIp, clientUdpPort);
			std::cout << "Client UDP info: " << clientIp.toString() << ":" << clientUdpPort << std::endl;
		} else {
			std::cerr << "Failed to parse client handshake packet" << std::endl;
		}
		
		handshakePacket.clear();
		handshakePacket << static_cast<int>(PacketType::CONNECT) << static_cast<int>(0);
		mSocket.send(handshakePacket);

		std::cout << "Handshake successful. Client connected." << std::endl;

		return true;
	}
	return false;
}

void NetworkManager::SendUDPPacket(sf::Packet& packet) 
{
	if (mMode == NetworkMode::CLIENT) {
		mUdpSocket.send(packet, mServerIp, mServerPort);
	} else if (mMode == NetworkMode::HOST && mClientConnected && mClientUdpPort != 0) {
		mUdpSocket.send(packet, mClientUdpIp, mClientUdpPort);
	} else {
		std::cerr << "Cannot send UDP packet: no valid destination" << std::endl;
	}
}

sf::Socket::Status NetworkManager::ReceiveUDPPacket(sf::Packet& packet, sf::IpAddress& sender, unsigned short& port) 
{
	return mUdpSocket.receive(packet, sender, port);
}

void NetworkManager::SetClientUDPAddress(const sf::IpAddress& ip, unsigned short port) 
{
	mClientUdpIp = ip;
	mClientUdpPort = port;
	std::cout << "Set client UDP address to " << ip.toString() << ":" << port << std::endl;
}