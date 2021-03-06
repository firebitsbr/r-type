//
// Created by Quentin Liardeaux on 12/24/19.
//

#ifndef R_TYPE_USERDATA_HPP
#define R_TYPE_USERDATA_HPP

#include <string>
#include <optional>
#include <boost/asio.hpp>

typedef boost::asio::ip::udp BoostUdp;

class UserData {
public:
    UserData(uint16_t serverPort, uint16_t userPort,
            std::string remoteAddress, std::string localAddress,
            std::string nickname, std::string password, std::string roomName)
            : m_id(0)
            , m_serverPort(serverPort)
            , m_userPort(userPort)
            , m_remoteAddress(std::move(remoteAddress))
            , m_localAddress(std::move(localAddress))
            , m_nickname(std::move(nickname))
            , m_password(std::move(password))
            , m_roomName(std::move(roomName))
            , m_localEndpoint(boost::asio::ip::address_v4::any(), m_userPort) {}
    ~UserData() = default;

    [[nodiscard]] uint16_t getServerPort() const { return m_serverPort; }
    [[nodiscard]] uint16_t getUserPort() const { return m_userPort; }
    [[nodiscard]] const std::string& getRemoteIpAddress() const { return m_remoteAddress; }
    [[nodiscard]] const std::string& getLocalIpAddress() const { return m_localAddress; }
    [[nodiscard]] const std::string& getNickname() const { return m_nickname; }
    [[nodiscard]] const std::string& getPassword() const { return m_password; }
    [[nodiscard]] const std::string& getRoomName() const { return m_roomName; }
    [[nodiscard]] const BoostUdp::endpoint& getLocalEndpoint() const { return m_localEndpoint; }

    size_t m_id;
    std::optional<BoostUdp::endpoint> m_remoteEndpoint;
private:
    uint16_t m_serverPort;
    uint16_t m_userPort;
    std::string m_remoteAddress;
    std::string m_localAddress;
    std::string m_nickname;
    std::string m_password;
    std::string m_roomName;
    BoostUdp::endpoint m_localEndpoint;
};


#endif //R_TYPE_USERDATA_HPP
