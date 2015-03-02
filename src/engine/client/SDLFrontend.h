#pragma once

#include "engine/common/IFrontend.h"
#include "engine/common/IConsole.h"
#include "engine/common/ConfigVar.h"
#include "engine/common/Logger.h"
#include "engine/common/NonCopyable.h"
#include <SDL.h>
#include <vector>
#include <map>
#include <string>

class SDLFrontend: public IFrontend, public NonCopyable, public IEventObserver {
private:
	SDL_Renderer *_renderer;
protected:
	EventHandler *_eventHandler;
	SDL_Window *_window;
	SDL_Haptic *_haptic;
	// stores the current rendered frames per second
	unsigned int _numFrames;
	// stores the time since frontend start
	uint32_t _time;
	// stores the time base for fps calculation
	uint32_t _timeBase;
	SharedPtr<IConsole> _console;

	ConfigVarPtr _debugSleep;

	bool _softwareRenderer;

	Color _color;

	void setWindowTitle (const std::string& title);
	inline uint32_t getDisplayFormat () const;

	inline void checkError (const char *file, unsigned int line, const char *function) const
	{
		const char *error = SDL_GetError();
		if (*error != '\0') {
			error(LOG_CLIENT, String::format("%s (%s:%i => %s)", error, file, line, function));
			SDL_ClearError();
		} else {
			error(LOG_CLIENT, String::format("unknown error (%s:%i => %s)", file, line, function));
		}
	}
	#define sdlCheckError() /*OpenGLStateHandlerCheckError(__FILE__, __LINE__, __PRETTY_FUNCTION__);*/checkError(__FILE__, __LINE__, __PRETTY_FUNCTION__)

	void setVSync (bool vsync);
	void setSDLColor (const Color& rgba);
	void getTrimmed (const Texture* texture, int& x, int& y, int& w, int& h) const;
	void initJoystickAndHaptic ();
public:
	SDLFrontend (SharedPtr<IConsole> console);
	virtual ~SDLFrontend ();

	virtual void initRenderer ();
	virtual void setHints ();
	virtual void setGLAttributes ();

	virtual void resetColor ();
	virtual void setColor (const Color& rgba);

	virtual void renderBegin ();
	virtual void renderEnd ();

	// IEventObserver
	virtual void onWindowResize () override;
	virtual void onPrepareBackground () override;
	virtual void onForeground () override;
	void onJoystickDeviceRemoved (int32_t device);
	void onJoystickDeviceAdded (int32_t device);

	// IFrontend implementation
	virtual void makeScreenshot (const std::string& filename) override;
	virtual int renderFilledPolygon (int *vx, int *vy, int n, const Color& color) override;
	virtual int renderPolygon (int *vx, int *vy, int n, const Color& color) override;
	virtual void setFullscreen (bool fullscreen) override;
	virtual bool isFullscreen () override;
	virtual void setCursorPosition (int x, int y) override;
	virtual void showCursor (bool show) override;
	virtual void renderImage (Texture* texture, int x, int y, int w, int h, int16_t angle, float alpha = 1.0f) override;
	virtual bool loadTexture (Texture *texture, const std::string& filename) override;
	virtual void bindTexture (Texture* texture, int textureUnit) override;
	virtual void renderRect (int x, int y, int w, int h, const Color& color) override;
	virtual void renderFilledRect (int x, int y, int w, int h, const Color& fillColor) override;
	virtual void renderLine (int x1, int y1, int x2, int y2, const Color& color) override;
	virtual void renderLineWithTexture (int x1, int y1, int x2, int y2, Texture* texture) override;
	virtual void updateViewport (int x, int y, int width, int height) override;
	virtual void enableScissor (int x, int y, int width, int height) override;
	virtual void destroyTexture (void *data) override;
	virtual void minimize () override;
	virtual void disableScissor () override;
	virtual void render () override;
	virtual void update (uint32_t deltaTime) override;
	virtual void connect () override;
	virtual void onMapLoaded () override;
	virtual void onStart () override;
	virtual void onInit () override;
	virtual void shutdown () override;
	virtual bool handlesInput () const override;
	virtual bool setFrameCallback (int interval, void (*callback) (void*), void *callbackParam) override;
	virtual int init (int width, int height, bool fullscreen, EventHandler &eventHandler) override;
	virtual void initUI (ServiceProvider& serviceProvider) override;
	virtual bool rumble (float strength, int lengthMillis) override;
	virtual bool hasJoystick () const override { return SDL_NumJoysticks() > 0; }
	virtual bool isConsoleActive () const override;
};
