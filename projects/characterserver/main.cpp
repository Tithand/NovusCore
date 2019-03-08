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

#include <Config\ConfigHandler.h>
#include <Database\DatabaseConnector.h>

#include "Connections\NovusConnection.h"

int main()
{
    if (!ConfigHandler::Setup("characterserver_configuration.json"))
    {
        std::getchar();
        return 0;
    }
	DatabaseConnector::Setup("127.0.0.1", "root", "ascent");
    srand((uint32_t)time(NULL));

    asio::io_service io_service(2);
    NovusConnection novusConnection(new asio::ip::tcp::socket(io_service), ConfigHandler::GetOption<std::string>("relayserverip", "127.0.0.1"), ConfigHandler::GetOption<uint16_t>("relayserverport", 8085));

    if (!novusConnection.Start())
    {
        std::getchar();
        return 0;
    }
    std::cout << "Characterserver established node connection to Relayserver." << std::endl;

    std::thread run_thread([&]
    {
        io_service.run();
    });

    std::getchar();
	return 0;
}