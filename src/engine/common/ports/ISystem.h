#pragma once

#include "engine/common/IFrontend.h"
#include "engine/common/DateUtil.h"
#include <string>
#include <vector>
#include <iostream>
#include <SDL.h>

struct PaymentEntry {
	PaymentEntry (const std::string& _name, const std::string& _id, const std::string& _price) :
			name(_name), id(_id), price(_price)
	{
	}
	std::string name;
	std::string id;
	std::string price;
};

typedef std::vector<std::string> DirectoryEntries;
typedef DirectoryEntries::const_iterator DirectoryEntriesIter;

class ISystem {
private:
	ISystem (const ISystem&);
	ISystem& operator= (const ISystem&);

public:

	ISystem ()
	{
	}

	virtual ~ISystem ()
	{
	}

	virtual void init () {}

	void signalHandler (int s) {
		backtrace("");
		exit("quitting via signal", s);
	}

	virtual std::string getCurrentWorkingDir () = 0;

	virtual std::string getCurrentUser () = 0;

	virtual std::string getLanguage () { return ""; }

	virtual void syncFiles() {}

	// return a slash terminates path to the home directory where the game saves its data to
	virtual std::string getHomeDirectory () = 0;

	virtual std::string getDatabaseDirectory () = 0;

	virtual void exit (const std::string& reason, int errorCode) = 0;

	virtual void tick (uint32_t deltaTime) {}

	virtual void logError (const std::string& error) const {
		const std::string str = dateutil::getDateString() + " " + error;
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\n", str.c_str());
	}

	virtual void logOutput (const std::string& string) const {
		const std::string str = dateutil::getDateString() + " " + string;
		SDL_Log("%s\n", str.c_str());
	}

	virtual std::string normalizePath (const std::string& path) = 0;

	virtual bool mkdir (const std::string& directory) = 0;

	virtual DirectoryEntries listDirectory (const std::string& basedir, const std::string& subdir = "") = 0;

	virtual void showAds (bool show) {}

	virtual bool showFullscreenAds () { return false; }

	virtual bool supportPayment () { return false; }

	/**
	 * @brief Handle quit in a system specific manner. The default is to not handle it differently.
	 *
	 * @return @c true in cases where you don't want to interrupt the mainloop
	 */
	virtual bool quit () { return false; }

	virtual bool buyItem (const std::string& id) { return false; }

	virtual void achievementUnlocked (const std::string& id, bool increment) { }

	virtual bool hasAchievement (const std::string& id) { return false; }

	virtual bool track (const std::string& hitType, const std::string& screenName) { logOutput(hitType + " => " + screenName); return true; }

	virtual int getScreenPadding () { return 0; }

	virtual bool hasMouseOrFinger () { return true; }

	virtual int getAdHeight() const { return 0; }

	virtual bool hasItem (const std::string& id) { return false; }

	virtual bool isOUYA () const { return false; }

	virtual int openURL (const std::string& url, bool newWindow) const { return 0; }

	virtual void getPaymentEntries (std::vector<PaymentEntry>& entries) { }

	virtual bool wantBackButton () { return true; }

	virtual bool wantCursor () { return true; }

	virtual bool supportFocusChange () { return true; }

	virtual bool isSmallScreen (IFrontend* frontend) { return frontend->getWidth() <= 1024 || frontend->getHeight() <= 768; }

	virtual bool isFullscreenSupported () { return true; }

	virtual bool canDisableJoystick () { return true; }

	virtual bool supportGooglePlay () { return false; }

	virtual void backtrace (const char *errorMessage) {}

	virtual bool hasTouch () const
	{
		return SDL_GetNumTouchDevices() > 0;
	}

	/**
	 * @return -1 indicates an error - 0 success
	 */
	virtual int exec (const std::string& command, std::vector<std::string>& arguments) const { return 0; }
};
