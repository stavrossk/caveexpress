#pragma once

#include "engine/client/ui/nodes/UINode.h"
#include "engine/common/Direction.h"
#include "engine/client/IMapControl.h"

class UIWindow;
class ClientMap;
class IUINodeMap;

// UI node that implements player controls via mouse, joystick or touch events
class UINodeMapControl: public UINode, public IMapControl {
private:
	ClientMap &_map;
	Direction _direction;
	Direction _oldDirection;
	bool _joystick;

public:
	UINodeMapControl (IFrontend *frontend, IUINodeMap *mapNode);
	virtual ~UINodeMapControl ();

	// IMapControl
	bool isPressed () const override { return false; }
	void hide () override { setVisible(false); }
	void show () override { setVisible(true); }

	// UINode
	void renderDebug (int x, int y, int textY) const override;
	void removeFocus () override;
	bool isActive () const;
	void update (uint32_t deltaTime) override;
	bool onJoystickMotion (bool horizontal, int value) override;
};
