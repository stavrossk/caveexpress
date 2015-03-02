#pragma once

#include "engine/common/Pointers.h"
#include "engine/common/IEventObserver.h"
#include <string>
#include <vector>

// forward decl
class IFrontend;

class IConsole: public IEventObserver {
protected:
	// the commandline that is going to get executed on enter
	std::string _commandLine;
	// commandline character will get overwritten if this is true
	bool _overwrite;
	int _frame;
	bool _cursorBlink;
	int _cursorPos;
	typedef std::vector<std::string> History;
	History _history;
	short _historyPos;
	bool _active;

	void executeCommandLine ();

public:
	IConsole ();

	virtual ~IConsole ()
	{
	}

	inline bool isActive() const
	{
		return _active;
	}

	virtual void init (IFrontend *frontend) = 0;
	virtual void logInfo (const std::string& string) = 0;
	virtual void logError (const std::string& string) = 0;
	virtual void logDebug (const std::string& string) = 0;
	virtual void render () = 0;
	virtual void update (uint32_t deltaTime) = 0;
	virtual bool onTextInput (const std::string& text) override;
	virtual bool onKeyPress (int32_t key, int16_t modifier) override { return false; }
	virtual void autoComplete ();

	// cursor move on the commandline
	void cursorLeft ();
	void cursorRight ();

	// history 'scroll' methods
	void cursorUp ();
	void cursorDown ();

	// removed the character under the cursor position
	virtual void cursorDelete (bool moveCursor = true);
};

typedef SharedPtr<IConsole> ConsolePtr;
