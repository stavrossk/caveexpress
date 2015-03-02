#pragma once

#include "engine/client/ui/nodes/UINode.h"
#include "engine/common/Direction.h"
#include "engine/client/IMapControl.h"

class ClientMap;
class IUINodeMap;

// UI node that implements player controls via on screen hud elements
class UINodeMapOnScreenCursorControl: public UINode, public IMapControl {
private:
	ClientMap &_map;

public:
	UINodeMapOnScreenCursorControl (IFrontend *frontend, IUINodeMap *mapNode);
	virtual ~UINodeMapOnScreenCursorControl ();

	void hide () override { setVisible(false); }
	void show () override { setVisible(true); }

	// IMapControl
	bool isPressed () const override
	{
		return false;
	}

	// UINode
	bool isActive () const override;
};
