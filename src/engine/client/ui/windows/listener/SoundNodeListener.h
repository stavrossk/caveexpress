#pragma once
#include "engine/client/sound/Sound.h"
#include "engine/common/ConfigManager.h"

class SoundNodeListener: public UINodeListener {
private:
	UIWindow *_window;
	bool _on;
public:
	SoundNodeListener (UIWindow *window, bool on) :
			_window(window), _on(on)
	{
	}

	void onClick () override
	{
		const bool soundState = Config.isSoundEnabled();
		if (soundState == _on)
			return;

		Config.toggleSound();

		if (_on) {
			SoundControl.init();
			_window->startMusic();
		} else {
			_window->stopMusic();
			SoundControl.close();
		}
	}
};
