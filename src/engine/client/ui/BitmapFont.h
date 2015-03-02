#pragma once

#include "engine/client/textures/Texture.h"
#include "engine/client/ui/FontDefinition.h"
#include <algorithm>

class IFrontend;

class BitmapFont {
	mutable TexturePtr _font;
	IFrontend *_frontend;
	FontDefPtr _fontDefPtr;
	uint32_t _time;
	int _rand;
public:
	BitmapFont (const FontDefPtr& fontDefPtr, IFrontend *frontend);
	virtual ~BitmapFont (void);
	int print (const std::string& text, const Color& color, int x, int y, bool rotate = true) const;
	int printMax (const std::string& text, const Color& color, int x, int y, int maxLength, bool rotate = true) const;
	int getCharHeight () const;
	int getCharWidth () const;
	void update (uint32_t deltaTime);
	int getMaxCharsForLength (const std::string& string, int pixelWidth) const;
	int getTextWidth (const std::string& string) const;
	int getTextHeight (const std::string& string) const;
	const std::string& getId () const;
};

inline int BitmapFont::getTextHeight (const std::string& string) const
{
	const int lines = 1 + std::count(string.begin(), string.end(), '\n');
	return getCharHeight() * lines;
}

inline int BitmapFont::getCharHeight () const
{
	return _fontDefPtr->getMetricsHeight();
}

inline const std::string& BitmapFont::getId () const
{
	return _fontDefPtr->id;
}
