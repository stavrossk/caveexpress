#pragma once

#include "engine/common/ports/Unix.h"

class Darwin: public Unix {
public:
	Darwin ();
	virtual ~Darwin ();

public:
	int openURL (const std::string& url, bool newWindow) const override;
	std::string getHomeDirectory () override;
};
