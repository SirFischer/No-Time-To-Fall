#pragma once
#include <SFML/Network.hpp>

enum class NetworkMode {
	HOST,
	CLIENT
};

enum class PacketType {
	CONNECT,
	DISCONNECT,
	MOVE,
	STATE_UPDATE
};

class NetworkManager {
	private:
		NetworkMode mMode = NetworkMode::HOST;
		sf::TcpSocket mSocket;
		sf::TcpListener mListener;

		sf::UdpSocket mUdpSocket;
		sf::IpAddress mServerIp;
		unsigned short mServerPort = 7645;
		bool mClientConnected = false;
		
		// Client UDP information (for host to send back to client)
		sf::IpAddress mClientUdpIp;
		unsigned short mClientUdpPort = 0;

	public:
		NetworkManager() = default;
		~NetworkManager();

		void SetMode(NetworkMode mode) { mMode = mode; }
		NetworkMode GetMode() const { return mMode; } 

		bool ConnectToServer(const std::string& ip, unsigned short port); 
		void StartServer(unsigned short port);
		bool CheckForNewClient();
		void Cleanup();

		void SendUDPPacket(sf::Packet& packet);
		sf::Socket::Status ReceiveUDPPacket(sf::Packet& packet, sf::IpAddress& sender, unsigned short& port);
		
		void SetClientUDPAddress(const sf::IpAddress& ip, unsigned short port);

		bool IsClientConnected() const { return mClientConnected; }


};
