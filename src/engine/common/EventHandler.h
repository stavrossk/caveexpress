#pragma once

#include <vector>
#include <string>
#include <stdint.h>

// forward decl
class IEventObserver;
union SDL_Event;

class EventHandler {
private:
	bool _multiGesture;

	typedef std::vector<IEventObserver*> EventObservers;
	EventObservers _observers;

	std::string getControllerButtonName (uint8_t button) const;

public:
	EventHandler ();
	virtual ~EventHandler ();

	// returns true if the processed event did not lead to the application quit
	bool handleEvent (SDL_Event &event);
	// returns true if the event was processed, false if it should get added to the event queue.
	bool handleAppEvent (SDL_Event &event);

	void registerObserver (IEventObserver* observer);
	void removeObserver (IEventObserver* observer);
	void joystickDeviceAdded (int32_t device);
	void joystickDeviceRemoved (int32_t device);
	void lowMemory ();
	void prepareShutdown ();
	void prepareBackground ();
	void prepareForeground ();
	void background ();
	void foreground ();
	void controllerButtonPress (const std::string& button);
	void controllerButtonRelease (const std::string& button);
	void joystickButtonPress (uint8_t button);
	void joystickButtonRelease (uint8_t button);
	void joystickMotion (bool horizontal, int value);
	void mouseWheel (int32_t x, int32_t y);
	void mouseMotion (int32_t x, int32_t y, int32_t relX, int32_t relY);
	void mouseButtonPress (int32_t x, int32_t y, uint8_t button);
	void mouseButtonRelease (int32_t x, int32_t y, uint8_t button);
	void textInput (const std::string& text);
	void keyRelease (int32_t key);
	void keyPress (int32_t key, int16_t modifier = 0);
	void fingerPress (int64_t finger, float x, float y);
	void fingerRelease (int64_t finger, float x, float y);
	void fingerMotion (int64_t finger, float x, float y, float dx, float dy);
	void gestureRecord (int64_t gestureId);
	void gesture (int64_t gestureId, float error, int32_t numFingers);
	void multiGesture (float theta, float dist, int32_t numFingers);
};
