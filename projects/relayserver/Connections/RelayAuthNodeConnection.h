/*
# MIT License

# Copyright(c) 2018-2019 NovusCore

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files(the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions :

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
*/
#pragma once

#include <asio\ip\tcp.hpp>
#include <Networking\BaseSocket.h>
#include <Networking\TcpServer.h>
#include <Cryptography\BigNumber.h>
#include <Cryptography\StreamCrypto.h>
#include <unordered_map>

enum RelayCommand
{
    RELAY_CHALLENGE         = 0x00,
    RELAY_PROOF             = 0x01,
    RELAY_CONFIRM_SESSION   = 0x02
};
enum RelayStatus
{
    RELAYSTATUS_CHALLENGE   = 0,
    RELAYSTATUS_PROOF       = 1,
    RELAYSTATUS_AUTHED      = 2,
    RELAYSTATUS_CLOSED      = 3
};

#pragma pack(push, 1)
struct sRelayChallenge
{
    u8 command;
    u8 K[32];
};
#pragma pack(pop)

struct RelayMessageHandler;
class RelayAuthNodeConnection : public Common::BaseSocket
{
public:
    static std::unordered_map<u8, RelayMessageHandler> InitMessageHandlers();

    RelayAuthNodeConnection(asio::ip::tcp::socket* socket, std::string address, u16 port) : Common::BaseSocket(socket), _status(RELAYSTATUS_CHALLENGE), _crypto(), _address(address), _port(port)
    { 
        _crypto = new StreamCrypto();
        _key = new BigNumber();
    }

    bool Start() override;
    void HandleRead() override;

    bool HandleCommandChallenge();
    bool HandleCommandProof();

    RelayStatus _status;
private:
    std::string _address;
    u16 _port;

    StreamCrypto* _crypto;
    BigNumber* _key;
};

#pragma pack(push, 1)
struct RelayMessageHandler
{
    RelayStatus status;
    size_t packetSize;
    bool (RelayAuthNodeConnection::*handler)();
};
#pragma pack(pop)