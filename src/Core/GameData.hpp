#pragma once
#include <string>

class GameData {
private:
    static GameData* instance;
    std::string serverIP;
    int serverPort;
    bool isServer;
    std::string playerName;
    
    GameData() : serverIP(""), serverPort(7777), isServer(false), playerName("Player") {}
    
public:
    static GameData& getInstance() {
        if (!instance) {
            instance = new GameData();
        }
        return *instance;
    }
    
    // IP and Server settings
    void setServerIP(const std::string& ip) { serverIP = ip; }
    std::string getServerIP() const { return serverIP; }
    
    void setServerPort(int port) { serverPort = port; }
    int getServerPort() const { return serverPort; }
    
    void setIsServer(bool server) { isServer = server; }
    bool getIsServer() const { return isServer; }
    
    void setPlayerName(const std::string& name) { playerName = name; }
    std::string getPlayerName() const { return playerName; }
    
    // Clear all data
    void clear() {
        serverIP = "";
        serverPort = 7777;
        isServer = false;
        playerName = "Player";
    }
    
    // Utility functions
    std::string getConnectionString() const {
        return serverIP + ":" + std::to_string(serverPort);
    }
    
    bool isValidIP() const {
        return !serverIP.empty() && serverIP != "";
    }
};
