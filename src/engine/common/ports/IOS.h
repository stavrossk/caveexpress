#pragma once

#include "engine/common/ports/Unix.h"

class IOS: public Unix {
public:
	IOS ();
	virtual ~IOS ();

public:
	void showAds (bool show) override;
	int openURL (const std::string& url, bool newWindow) const override;
	bool isFullscreenSupported () override { return false; }
	std::string getHomeDirectory () override;
};

