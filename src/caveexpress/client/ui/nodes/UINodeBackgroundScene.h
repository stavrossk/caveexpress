#pragma once

#include "engine/client/ui/nodes/UINode.h"
#include "engine/common/String.h"
#include "engine/client/ui/BitmapFont.h"
#include "engine/common/Payment.h"
#include "engine/common/Config.h"
#include "engine/common/ThemeType.h"
#include "engine/common/MapFailedReason.h"
#include <map>

class UINodeBackgroundScene: public UINode {
private:
	int _imageWidth;
	int _imageHeight;
	int _amountHorizontal;
	int _amountVertical;

	typedef std::vector<TexturePtr> TextureVector;
	TextureVector _tilesRock;
	TextureVector _groundsRock;
	TextureVector _tilesIce;
	TextureVector _groundsIce;
	TexturePtr _caveOffIce;
	TexturePtr _caveArtIce;
	TexturePtr _caveOffRock;
	TexturePtr _caveArtRock;

	typedef std::map<const MapFailedReason*, TexturePtr> FailedMap;
	FailedMap _failed;
	const MapFailedReason* _reason;
	const ThemeType* _theme;

	void renderFailedHitpoints (int x, int y) const;
	void renderFailedNpcFish (int x, int y) const;
	void renderFailedNpcMammut (int x, int y) const;
	void renderFailedNpcWalking (int x, int y) const;
	void renderFailedWaterHeight (int x, int y) const;
	void renderFailedNpcFlying (int x, int y) const;

	void renderFailedOnGround (int x, int y, const MapFailedReason& reason, float offsetY) const;
	void renderFailedCenter (int x, int y, const MapFailedReason& reason) const;

	void renderBackground (int x, int y) const;
	void renderCave (int x, int y) const;
	int renderGround (int x, int y) const;
	void renderWater (int x, int y) const;

public:
	UINodeBackgroundScene (IFrontend *frontend);
	void updateReason (const MapFailedReason& reason, const ThemeType& theme);
	void render (int x, int y) const override;
};
