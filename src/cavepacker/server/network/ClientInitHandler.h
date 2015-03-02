#pragma once

#include "engine/common/network/IProtocolHandler.h"
#include "engine/common/network/messages/ClientInitMessage.h"
#include "cavepacker/server/map/Map.h"

class ClientInitHandler: public IServerProtocolHandler {
private:
	Map& _map;
public:
	ClientInitHandler (Map& map) :
			_map(map)
	{
	}

	void execute (const ClientId& clientId, const IProtocolMessage& message) override
	{
		Player *player = _map.getPlayer(clientId);
		if (player == nullptr) {
			error(LOG_SERVER, "init for player with clientId " + string::toString((int)clientId) + " failed");
			return;
		}
		const ClientInitMessage* msg = static_cast<const ClientInitMessage*>(&message);
		player->setName(msg->getName());
		_map.sendPlayersList();
	}
};
