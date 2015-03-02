#pragma once

#include "engine/common/ICommand.h"
#include "cavepacker/client/CavePackerClientMap.h"
#include <stdint.h>

class CmdUndo: public ICommand {
private:
	CavePackerClientMap& _map;

public:
	CmdUndo (CavePackerClientMap& map) :
			_map(map)
	{
	}

	void run (const Args& args) override
	{
		_map.undo();
	}
};
