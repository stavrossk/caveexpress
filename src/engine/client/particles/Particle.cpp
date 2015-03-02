#include "Particle.h"
#include "engine/client/ui/UI.h"
#include <sstream>

Particle::Particle(IParticleEnvironment& env) :
		_env(env), _active(true), _time(0), _deltaTime(0.0f), _alpha(1.0f), _angle(0), _fps(1.0f),
		_tps(1.0f), _lastFrame(0.0f), _lastThink(0.0f), _t(0.0f), _life(0.0f), _omega(0.0f)
{
}

Particle::~Particle ()
{
}

TexturePtr Particle::loadTexture (const std::string& image) const
{
	return _env.loadTexture(image);
}

inline void Particle::advanceVector (const vec2& veca, const float scale, const vec2& vecb, vec2& outVector) const
{
	outVector.x = veca.x + scale * vecb.x;
	outVector.y = veca.y + scale * vecb.y;
}

bool Particle::update (uint32_t deltaTime)
{
	run();

	if (!_active)
		return true;

	_deltaTime = deltaTime;
	_time += _deltaTime;
	_t = _time * 0.001f;
	_lastThink += _deltaTime;
	_lastFrame += _deltaTime;
	advanceVector(_s, 0.5f * _deltaTime * _deltaTime, _a, _s);
	advanceVector(_s, _deltaTime, _v, _s);
	advanceVector(_v, _deltaTime, _a, _v);
	_angle = _omega + _deltaTime * _angle;

	while (_tps && _lastThink * _tps >= 1.0f) {
		think();
		_lastThink -= 1.0f / _tps;
	}

	while (_fps && _lastFrame * _fps >= 1.0f) {
		// TODO: sprite
		_lastFrame -= 1.0f / _fps;
	}

	if (_life && _t >= _life)
		return false;

	return true;
}

void Particle::render (IFrontend* frontend, int x, int y, float zoom) const
{
	if (!_texture || !_texture->isValid())
		return;
	frontend->renderImage(_texture.get(), x + _s.x * zoom, y + _s.y * zoom, _texture->getWidth() * zoom, _texture->getHeight() * zoom, _angle, _alpha);
}

std::string Particle::toString() const
{
	std::stringstream s;
	s << "Particle[";
	const std::string textureName = _texture ? _texture->getName() : "none";
	s << "texture: '" << textureName << "', ";
	s << "active: '" << _active << "', ";
	s << "time: '" << _time << "', ";
	s << "deltaTime: '" << _deltaTime << "', ";
	s << "alpha: '" << _alpha << "', ";
	s << "angle: '" << _angle << "', ";
	s << "fps: '" << _fps << "', ";
	s << "tps: '" << _tps << "', ";
	s << "lastFrame: '" << _lastFrame << "', ";
	s << "lastThink: '" << _lastThink << "', ";
	s << "t: '" << _t << "', ";
	s << "life: '" << _life << "', ";
	s << "s: '" << _s << "', ";
	s << "v: '" << _v << "', ";
	s << "a: '" << _a << "', ";
	s << "omega: '" << _omega << "'";
	s << "]";
	return s.str();
}
