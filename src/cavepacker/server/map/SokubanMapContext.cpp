#include "SokubanMapContext.h"
#include "engine/common/FileSystem.h"

namespace {
const int WALL = '#';
const int PLAYER = '@';
const int PACKAGE = '$';
const int TARGET = '.';
const int GROUND = ' ';
const int PACKAGEONTARGET = '*';
const int PLAYERONTARGET = '+';
}

SokubanMapContext::SokubanMapContext(const std::string& map) :
		IMapContext(map) {
}

SokubanMapContext::~SokubanMapContext() {
}

void SokubanMapContext::onMapLoaded() {
}

bool SokubanMapContext::load(bool skipErrors) {
	info(LOG_SERVER, "load the map " + _name);
	resetTiles();

	FilePtr filePtr = FS.getFile(_name);
	if (!filePtr->exists()) {
		error(LOG_SERVER,
				"sokuban map file " + filePtr->getURI().print()
						+ " does not exist");
		return false;
	}

	char *buffer;
	const int fileLen = filePtr->read((void **) &buffer);
	ScopedArrayPtr<char> p(buffer);
	if (!buffer || fileLen <= 0) {
		error(LOG_SERVER, "sokuban map file " + filePtr->getURI().print());
		return false;
	}

	int col = 0;
	int row = 0;
	int maxCol = 0;
	for (int i = 0; i < fileLen; ++i) {
		switch (buffer[i]) {
		case WALL:
			addWall(col, row);
			break;
		case GROUND:
			addGround(col, row);
			break;
		case PLAYER:
			addPlayer(col, row);
			break;
		case PACKAGE:
			addPackage(col, row);
			break;
		case TARGET:
			addTarget(col, row);
			break;
		case PACKAGEONTARGET:
			addTarget(col, row);
			addPackage(col, row);
			break;
		case '\n':
			col = -1;
			++row;
			break;
		}
		++col;
		maxCol = std::max(maxCol, col);
	}

	_settings[msn::WIDTH] = string::toString(maxCol);
	_settings[msn::HEIGHT] = string::toString(row);

	return true;
}

void SokubanMapContext::addTile(const std::string& tile, int col, int row) {
	SpriteDefPtr spriteDefPtr = SpriteDefinition::get().getSpriteDefinition(
			tile);
	if (!spriteDefPtr) {
		info(LOG_SERVER, "could not add tile: " + tile);
		return;
	}

	const EntityAngle angle = spriteDefPtr->angle;
	const MapTileDefinition def(col, row, spriteDefPtr, angle);
	_definitions.push_back(def);
}

inline void SokubanMapContext::addTarget(int col, int row) {
	addTile("target", col, row);
}

inline void SokubanMapContext::addWall(int col, int row) {
	addTile("wall", col, row);
}

inline void SokubanMapContext::addPackage(int col, int row) {
	addTile("package", col, row);
}

inline void SokubanMapContext::addPlayer(int col, int row) {
	addTile("player", col, row);
	_settings[msn::PLAYER_X] = string::toString(col);
	_settings[msn::PLAYER_Y] = string::toString(row);
}

inline void SokubanMapContext::addGround(int col, int row) {
	addTile("ground", col, row);
}
