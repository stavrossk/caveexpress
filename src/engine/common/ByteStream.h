#pragma once

#include "engine/common/System.h"
#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <list>
#include <string>
#include <stdarg.h>
#include <SDL_endian.h>
#include <limits.h>

namespace Constant {
const int SCALE_FACTOR = 100;
}

#define BYTE_MASK 0XFF
#define WORD_MASK 0XFFFF

class ByteStream {
private:
	typedef std::vector<uint8_t> VectorBuffer;
	VectorBuffer _buffer;

public:
	ByteStream ();
	virtual ~ByteStream ();

	void addBool (bool value, bool prepend = false);
	void addByte (uint8_t byte, bool prepend = false);
	void addShortScaled (float value);
	void addShort (int16_t word, bool prepend = false);
	void addInt (int32_t dword);
	void addFloat (float value);
	void addString (const std::string& string);
	void addFormat (const char *fmt, ...);

	bool readBool ();
	uint8_t readByte ();
	float readShortScaled ();
	int16_t readShort ();
	int32_t readInt ();
	float readFloat ();
	std::string readString ();
	void readFormat (const char *fmt, ...);

	int32_t peekInt () const;
	int16_t peekShort () const;

	// get the raw data pointer for the buffer
	const uint8_t* getBuffer () const;

	void append (const uint8_t *buf, size_t size);

	bool empty () const;

	// clear the buffer if it's no longer needed
	void clear ();

	// return the amount of bytes in the buffer
	size_t getSize () const;

	void resize (size_t size);

	ByteStream &operator<<(const uint8_t &x) {
		addByte(x, false);
		return *this;
	}

	ByteStream &operator<<(const int16_t &x) {
		addShort(x);
		return *this;
	}

	ByteStream &operator<<(const bool &x) {
		addBool(x);
		return *this;
	}

	ByteStream &operator<<(const int32_t &x) {
		addInt(x);
		return *this;
	}

	ByteStream &operator<<(const float &x) {
		addFloat(x);
		return *this;
	}

	ByteStream &operator<<(const std::string &x) {
		addString(x);
		return *this;
	}
};

inline bool ByteStream::empty () const
{
	return _buffer.empty();
}

inline void ByteStream::resize (size_t size)
{
	_buffer.resize(size);
}

inline void ByteStream::append (const uint8_t *buf, size_t size)
{
	// TODO: optimize
	for (int i = 0; i < size; ++i) {
		addByte(buf[i]);
	}
}

inline const uint8_t* ByteStream::getBuffer () const
{
	return &_buffer.front();
}

inline void ByteStream::clear ()
{
	_buffer.clear();
}

inline size_t ByteStream::getSize () const
{
	return _buffer.size();
}

inline void ByteStream::addByte (uint8_t byte, bool prepend)
{
	if (prepend) {
		_buffer.insert(_buffer.begin(), byte);
	} else {
		_buffer.push_back(byte);
	}
}

inline void ByteStream::addBool (bool value, bool prepend)
{
	addByte(value, prepend);
}

inline void ByteStream::addString (const std::string& string)
{
	const size_t length = string.length();
	for (int i = 0; i < length; i++) {
		_buffer.push_back(uint8_t(string[i]));
	}
	_buffer.push_back(uint8_t('\0'));
}

inline void ByteStream::addShortScaled (float value)
{
	addShort(value * Constant::SCALE_FACTOR);
}

inline void ByteStream::addShort (int16_t word, bool prepend)
{
	const int16_t swappedWord = SDL_SwapLE16(word);
	if (prepend) {
		_buffer.insert(_buffer.begin(), uint8_t(swappedWord >> CHAR_BIT));
		_buffer.insert(_buffer.begin(), uint8_t(swappedWord));
	} else {
		_buffer.push_back(uint8_t(swappedWord));
		_buffer.push_back(uint8_t(swappedWord >> CHAR_BIT));
	}
}

inline void ByteStream::addInt (int32_t dword)
{
	int32_t swappedDWord = SDL_SwapLE32(dword);
	_buffer.push_back(uint8_t(swappedDWord));
	_buffer.push_back(uint8_t(swappedDWord >>= CHAR_BIT));
	_buffer.push_back(uint8_t(swappedDWord >>= CHAR_BIT));
	_buffer.push_back(uint8_t(swappedDWord >> CHAR_BIT));
}

inline void ByteStream::addFloat (float value)
{
	union toint {
		float f;
		uint32_t i;
	} tmp;
	tmp.f = value;
	addInt(tmp.i);
}

inline uint8_t ByteStream::readByte ()
{
	if (_buffer.empty())
		System.exit("buffer underrun in readByte", 1);
	const uint8_t byte = _buffer.front();
	_buffer.erase(_buffer.begin());
	return byte;
}

inline float ByteStream::readShortScaled ()
{
	return readShort() / static_cast<float>(Constant::SCALE_FACTOR);
}

inline bool ByteStream::readBool ()
{
	return readByte() != 0;
}

inline int16_t ByteStream::readShort ()
{
	if (_buffer.size() < 2)
		System.exit("buffer underrun in readShort", 1);
	const int16_t *word = reinterpret_cast<const int16_t*>(getBuffer());
	const int16_t val = SDL_SwapLE16(*word);
	_buffer.erase(_buffer.begin(), std::next(_buffer.begin(), 2));
	return val;
}

inline float ByteStream::readFloat ()
{
	union toint {
		float f;
		uint32_t i;
	} tmp;
	tmp.i = readInt();

	return tmp.f;
}

inline int32_t ByteStream::readInt ()
{
	if (_buffer.size() < 4)
		System.exit("buffer underrun in readInt", 1);
	const int32_t *word = reinterpret_cast<const int32_t*>(getBuffer());
	const int32_t val = SDL_SwapLE32(*word);
	_buffer.erase(_buffer.begin(), std::next(_buffer.begin(), 4));
	return val;
}
