/*
# MIT License

# Copyright(c) 2018 NovusCore

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

#include "AuthSocketHandler.h"
#include <Config\ConfigHandler.h>

int main()
{
    if (!ConfigHandler::Setup("authserver_configuration.json"))
    {
        std::getchar();
        return 0;
    }

    std::string ip = ConfigHandler::GetOption<std::string>("ip", "127.0.0.1");
    std::cout << ip << std::endl;

    asio::io_service io_service(2);
    AuthSocketHandler server(io_service, 3724);
    server.Init();
    server.Start();

    std::thread run_thread([&]
    {
        io_service.run();
    });

    printf("Authserver Running\n\n");
    std::getchar();

    return 0;
}
