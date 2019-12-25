//
// Created by Quentin Liardeaux on 12/19/19.
//

#ifndef R_TYPE_CLIENT_HPP
#define R_TYPE_CLIENT_HPP

#include <string>
#include <optional>

#include "protocol.hpp"
#include "Message.hpp"
#include "Protocol/Packet.hpp"
#include "ClientHandler.hpp"
#include "GameRoom.hpp"
#include "Lobby.hpp"
#include "IdProvider.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/enable_shared_from_this.hpp>

typedef boost::asio::ip::tcp BoostTcp;
typedef boost::asio::ip::udp BoostUdp;

class ClientHandler;
class GameRoom;
class Lobby;

class Client : public boost::enable_shared_from_this<Client> {
public:
    static boost::shared_ptr<Client> create(boost::asio::io_context &context);

    void start();
    void stop();

    BoostTcp::socket &getSocket() { return m_tcpSocket; }
    size_t getId() const { return m_id; }
    const std::string& getNickname() const { return m_nickname; }

    void setHandler(boost::shared_ptr<ClientHandler> handler) { m_handler = handler; }
    void setUdpSocket(uint16_t port) { m_udpPort = port; }

    void sendPlayerJoinGame(uint8_t playerId, std::string nickname);
    void sendPlayerQuitGame(uint8_t playerId);
    void startGame();

    ~Client();

private:
    explicit Client(boost::asio::io_context &context);

    void waitHeader(const boost::system::error_code &ec);
    void receivePacket(const boost::system::error_code &ec);
    void receiveBody(const boost::system::error_code &ec);
    std::unique_ptr<Message> handleRequest(uint8_t *data, uint16_t packetId);
    void dispatchPackets(const Message* msg);
    void sendMessage(const Message& msg);

    void connectClient(const ClientConnect *msg);
    void createGame(const CreateGame *msg);
    void joinGame(const JoinGame *msg);

    void dispatchUdpPackets();

    void movePlayer();
    void fireEntity();

    boost::asio::io_service m_ioService;
    BoostTcp::socket m_tcpSocket;
    packet_header_t m_packetHeader;
    uint8_t *m_packetData;
    boost::shared_ptr<ClientHandler> m_handler;
    size_t m_id;
    std::string m_nickname;
    uint16_t m_udpPort;
    std::string m_ipAddress;
    std::optional<BoostUdp::endpoint> m_remoteEndpoint;
    std::optional<BoostUdp::socket> m_udpSocket;
    bool m_isUdpRunning;
    boost::thread m_thread;
};

#endif //R_TYPE_CLIENT_HPP
