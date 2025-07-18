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

	std::cout << "Attempting to connect to server at " << ip << ":" << port << std::endl;

	// Set a connection timeout
	mSocket.setBlocking(true); // Use blocking for initial connection
	sf::Socket::Status status = mSocket.connect(ip, port, sf::seconds(10));
	
	if (status != sf::Socket::Done) {
		std::string errorMsg = "Failed to connect to server at " + ip + ":" + std::to_string(port);
		switch (status) {
			case sf::Socket::Error:
				errorMsg += " - Network error";
				break;
			case sf::Socket::Disconnected:
				errorMsg += " - Connection rejected or server not available";
				break;
			case sf::Socket::NotReady:
				errorMsg += " - Connection timeout (server may be unreachable)";
				break;
			default:
				errorMsg += " - Unknown error (" + std::to_string(static_cast<int>(status)) + ")";
				break;
		}
		throw std::runtime_error(errorMsg);
	}

	std::cout << "TCP connection established successfully!" << std::endl;

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
	
	if (mSocket.send(handshakePacket) != sf::Socket::Done) {
		throw std::runtime_error("Failed to send handshake packet to server");
	}
	std::cout << "Sent handshake with UDP port: " << clientUdpPort << std::endl;
	
	// Wait for handshake response with timeout
	if (mSocket.receive(handshakePacket) != sf::Socket::Done) {
		throw std::runtime_error("Failed to receive handshake response from server");
	}
	
	if (handshakePacket.getDataSize() == 0) {
		throw std::runtime_error("Received empty handshake packet from server");
	}
	
	// Set socket back to non-blocking for game operation
	mSocket.setBlocking(false);
	
	std::cout << "Handshake successful. Connected to server at " << ip << ":" << port << std::endl;

	return true;
}

void NetworkManager::StartServer(unsigned short port) {
	if (mMode != NetworkMode::HOST) {
		throw std::runtime_error("NetworkManager is not in HOST mode.");
	}

	// Bind to all interfaces (0.0.0.0) instead of just local address
	sf::Socket::Status status = mListener.listen(port, sf::IpAddress::Any);
	if (status != sf::Socket::Done) {
		throw std::runtime_error("Failed to start server on port " + std::to_string(port) + ": " + std::to_string(static_cast<int>(status)));
	}

	mListener.setBlocking(false);

	// Get both local and public IP addresses for information
	sf::IpAddress localIp = sf::IpAddress::getLocalAddress();
	sf::IpAddress publicIp = sf::IpAddress::getPublicAddress();
	
	mServerIp = localIp; // Use local IP for internal reference
	mServerPort = port;

	sf::Socket::Status udpStatus = mUdpSocket.bind(port, sf::IpAddress::Any);
	if (udpStatus != sf::Socket::Done) {
		std::cout << "Failed to bind UDP socket to port " << port << ", trying alternative ports..." << std::endl;
		
		for (unsigned short altPort = port + 1; altPort <= port + 10; ++altPort) {
			udpStatus = mUdpSocket.bind(altPort, sf::IpAddress::Any);
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

	std::cout << "=== SERVER STARTED ===" << std::endl;
	std::cout << "Local IP: " << localIp.toString() << std::endl;
	if (publicIp != sf::IpAddress::None) {
		std::cout << "Public IP: " << publicIp.toString() << std::endl;
	}
	std::cout << "Port: " << mServerPort << std::endl;
	std::cout << "Clients should connect to: " << localIp.toString() << ":" << mServerPort << std::endl;
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
		std::cout << "=== NEW CLIENT CONNECTION ===" << std::endl;
		std::cout << "Client IP: " << clientIp.toString() << std::endl;
		std::cout << "Client Port: " << mSocket.getRemotePort() << std::endl;
		
		sf::Packet handshakePacket;
		if (mSocket.receive(handshakePacket) != sf::Socket::Done) {
			std::cerr << "Failed to receive handshake packet from client" << std::endl;
			mClientConnected = false;
			mSocket.disconnect();
			return false;
		}
		
		int packetType;
		unsigned short clientUdpPort;
		if (handshakePacket >> packetType >> clientUdpPort && packetType == static_cast<int>(PacketType::CONNECT)) {
			SetClientUDPAddress(clientIp, clientUdpPort);
			std::cout << "Client UDP info: " << clientIp.toString() << ":" << clientUdpPort << std::endl;
		} else {
			std::cerr << "Failed to parse client handshake packet" << std::endl;
			mClientConnected = false;
			mSocket.disconnect();
			return false;
		}
		
		handshakePacket.clear();
		handshakePacket << static_cast<int>(PacketType::CONNECT) << static_cast<int>(0);
		if (mSocket.send(handshakePacket) != sf::Socket::Done) {
			std::cerr << "Failed to send handshake response to client" << std::endl;
			mClientConnected = false;
			mSocket.disconnect();
			return false;
		}

		std::cout << "Handshake successful. Client fully connected!" << std::endl;
		std::cout << "==============================" << std::endl;

		return true;
	} else if (status != sf::Socket::NotReady) {
		std::cerr << "Error accepting client connection: " << static_cast<int>(status) << std::endl;
	}
	return false;
}

void NetworkManager::SendUDPPacket(sf::Packet& packet) 
{
	sf::Socket::Status status;
	if (mMode == NetworkMode::CLIENT) {
		// Client sends to server
		status = mUdpSocket.send(packet, mServerIp, mServerPort);
		if (status != sf::Socket::Done) {
			std::cerr << "Failed to send UDP packet to server " << mServerIp.toString() << ":" << mServerPort 
					  << " - Status: " << static_cast<int>(status) << std::endl;
		}
	} else if (mMode == NetworkMode::HOST && mClientConnected && mClientUdpPort != 0) {
		// Host sends to client
		status = mUdpSocket.send(packet, mClientUdpIp, mClientUdpPort);
		if (status != sf::Socket::Done) {
			std::cerr << "Failed to send UDP packet to client " << mClientUdpIp.toString() << ":" << mClientUdpPort 
					  << " - Status: " << static_cast<int>(status) << std::endl;
		}
	} else {
		std::cerr << "Cannot send UDP packet: no valid destination (mode=" << (mMode == NetworkMode::HOST ? "HOST" : "CLIENT") 
				  << ", connected=" << mClientConnected << ", port=" << mClientUdpPort << ")" << std::endl;
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