#pragma once

#include "engine/common/network/IProtocolHandler.h"
#include "engine/common/network/messages/ChangeAnimationMessage.h"
#include "engine/client/ClientMap.h"

class ChangeAnimationHandler: public IClientProtocolHandler {
private:
	ClientMap& _map;
public:
	ChangeAnimationHandler (ClientMap& map) :
			_map(map)
	{
	}

	void execute (const IProtocolMessage& message) override
	{
		const ChangeAnimationMessage *msg = static_cast<const ChangeAnimationMessage*>(&message);
		const uint16_t id = msg->getEntityId();
		const Animation& animation = msg->getAnimation();
		_map.changeAnimation(id, animation);
	}
};
