#include "IEntity.h"
#include "cavepacker/server/map/Map.h"
#include "engine/common/SpriteDefinition.h"
#include "engine/common/ConfigManager.h"

uint32_t IEntity::GLOBAL_ENTITY_NUM = 0;

IEntity::IEntity (const EntityType &type, Map& map) :
		_id(GLOBAL_ENTITY_NUM++), _type(type), _time(0), _map(map)
{
	setSpriteID("");
}

IEntity::~IEntity ()
{
}

SpriteDefPtr IEntity::getSpriteDef () const
{
	const std::string& spriteName = SpriteDefinition::get().getSpriteName(_type, Animation::NONE);
	const SpriteDefPtr& def = SpriteDefinition::get().getSpriteDefinition(spriteName);
	return def;
}

float IEntity::getAngle () const
{
	return 0.0f;
}

void IEntity::update (uint32_t deltaTime)
{
	_time += deltaTime;
	for (EntityObservers::iterator i = _observers.begin(); i != _observers.end(); ++i) {
		(*i)->onUpdate(this);
	}
}

void IEntity::remove ()
{
}

void IEntity::onSpawn ()
{
}

std::string IEntity::toString () const
{
	std::stringstream s;
	s << *this;
	return s.str();
}

void IEntity::print (std::ostream &stream, int level) const
{
	stream << "IEntity[id: " << _id << ", type:" << _type.name;
	stream << "]";
}