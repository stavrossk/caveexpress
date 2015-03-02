#pragma once

#include "engine/common/Pointers.h"
#include <string>

class Texture;
typedef SharedPtr<Texture> TexturePtr;

class IParticleEnvironment {
public:
	virtual ~IParticleEnvironment() {
	}

	virtual int getRenderOffsetX() const = 0;
	virtual int getRenderOffsetY() const = 0;
	// return the pixel water surface relative screen coordinate (from the top of the render node)
	virtual int getWaterSurface() const = 0;
	// return the pixel ground screen relative coordinate (from the top of the render node)
	virtual int getWaterGround() const = 0;
	// return the pixel water width
	virtual int getWaterWidth() const = 0;
	// return the pixel width of the environment the particle is living in
	virtual int getPixelWidth() const = 0;
	// return the pixel height of the environment the particle is living in
	virtual int getPixelHeight() const = 0;

	virtual TexturePtr loadTexture (const std::string& name) const = 0;
};
