/*
    MIT License

    Copyright (c) 2018-2019 NovusCore

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#pragma once
#include <NovusTypes.h>
#include <entt.hpp>

#include "../Components/PositionComponent.h"
#include "../Components/UnitStatusComponent.h"
#include "../Components/Singletons/SingletonComponent.h"
#include "../Components/Singletons/PlayerUpdatesQueueSingleton.h"

namespace ClientUpdateSystem
{
	void Update(entt::registry &registry) 
    {
        SingletonComponent& singleton = registry.get<SingletonComponent>(0);
        PlayerUpdatesQueueSingleton& playerUpdatesQueue = registry.get<PlayerUpdatesQueueSingleton>(0);
        NovusConnection& novusConnection = *singleton.connection;

        auto view = registry.view<ConnectionComponent, PlayerUpdateDataComponent>();

        view.each([&novusConnection, playerUpdatesQueue](const auto, ConnectionComponent& clientConnection, PlayerUpdateDataComponent& clientUpdateData)
        {
            NovusHeader novusHeader;
            for (PlayerUpdatePacket playerUpdatePacket : playerUpdatesQueue.playerUpdatePacketQueue)
            {
                if (playerUpdatePacket.updateType == PlayerUpdateDataSystem::UPDATETYPE_CREATE_OBJECT ||
                    playerUpdatePacket.updateType == PlayerUpdateDataSystem::UPDATETYPE_CREATE_OBJECT2 &&
                    playerUpdatePacket.characterGuid != clientConnection.characterGuid)
                {
                    if (std::find(clientUpdateData.visibleGuids.begin(), clientUpdateData.visibleGuids.end(), playerUpdatePacket.characterGuid) == clientUpdateData.visibleGuids.end())
                    {
                        novusHeader.CreateForwardHeader(clientConnection.accountGuid, playerUpdatePacket.opcode, playerUpdatePacket.data.size());

                        Common::ByteBuffer packet(novusHeader.size);
                        novusHeader.AddTo(packet);
                        packet.Append(playerUpdatePacket.data);

                        novusConnection.SendPacket(packet);
                        clientUpdateData.visibleGuids.push_back(playerUpdatePacket.characterGuid);
                    }
                }

                /* Handle Updates to existing players here */
            }

            for (MovementPacket movementPacket : playerUpdatesQueue.playerMovementPacketQueue)
            {
                if (clientConnection.characterGuid != movementPacket.characterGuid)
                {
                    novusHeader.CreateForwardHeader(clientConnection.accountGuid, movementPacket.opcode, movementPacket.data.size());

                    Common::ByteBuffer packet(novusHeader.size);
                    novusHeader.AddTo(packet);
                    packet.Append(movementPacket.data);

                    novusConnection.SendPacket(packet);
                }
            }
        });

        // Clear Queues
        playerUpdatesQueue.playerUpdatePacketQueue.clear();
        playerUpdatesQueue.playerMovementPacketQueue.clear();
	}
}
