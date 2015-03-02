#include "tests/ByteStreamTest.h"
#include "engine/common/Logger.h"
#include <cstdlib>
#include <limits.h>
#include <math.h>
#include <SDL_timer.h>
#include <stdlib.h>
#include <string>

#ifndef srandom
#define srandom srand
#endif
#ifndef random
#define random rand
#endif

namespace {
const uint8_t BYTE_ADD = UCHAR_MAX;
const int16_t SHORT_ADD = SHRT_MAX;
const int32_t INT_ADD = INT_MAX;
}

TEST(ByteStreamTest, testCopy) {
	std::vector<ByteStream> v;
	for (int j = 0; j < 1000; ++j) {
		ByteStream byteStream;
		for (int i = 0; i < 1000; ++i) {
			byteStream.addInt(i);
		}
		byteStream.addByte(1, true);
		v.push_back(byteStream);
	}

	for (std::vector<ByteStream>::const_iterator i = v.begin(); i != v.end(); ++i) {
		ByteStream s = *i;
		ASSERT_EQ(4001, s.getSize());
	}

	ASSERT_EQ(1000, v.size());
}

TEST(ByteStreamTest, testWriteByte) {
	ByteStream byteStream;
	const size_t previous = byteStream.getSize();
	byteStream.addByte(BYTE_ADD);
	ASSERT_EQ(previous + 1, byteStream.getSize());
}

TEST(ByteStreamTest, testWriteShort) {
	ByteStream byteStream;
	const size_t previous = byteStream.getSize();
	byteStream.addShort(SHORT_ADD);
	ASSERT_EQ(previous + 2, byteStream.getSize());
}

TEST(ByteStreamTest, testWriteEmptyString) {
	ByteStream byteStream;
	byteStream.addString("");
	ASSERT_EQ(1, byteStream.getSize());
	const std::string empty = byteStream.readString();
	ASSERT_EQ("", empty);
	ASSERT_EQ(0, byteStream.getSize());
}

TEST(ByteStreamTest, testWriteInt) {
	ByteStream byteStream;
	const size_t previous = byteStream.getSize();
	byteStream.addInt(INT_ADD);
	ASSERT_EQ(previous + 4, byteStream.getSize());
}

TEST(ByteStreamTest, testPeekShort) {
	int16_t peek;
	ByteStream byteStream;
	peek = byteStream.peekShort();
	byteStream.addByte(1);
	ASSERT_EQ(-1, peek);
	byteStream.addByte(1);
	peek = byteStream.peekShort();
	ASSERT_EQ(257, peek);
	ASSERT_EQ(257, byteStream.readShort());
	peek = byteStream.peekShort();
	ASSERT_EQ(-1, peek);
}

TEST(ByteStreamTest, testReadByte) {
	ByteStream byteStream;
	byteStream.addByte(BYTE_ADD);
	const size_t previous = byteStream.getSize();
	const uint8_t byte = byteStream.readByte();
	ASSERT_EQ(BYTE_ADD, byte);
	ASSERT_EQ(previous - 1, byteStream.getSize());
}

TEST(ByteStreamTest, testReadShort) {
	ByteStream byteStream;
	byteStream.addShort(SHORT_ADD);
	const size_t previous = byteStream.getSize();
	const int16_t word = byteStream.readShort();
	ASSERT_EQ(SHORT_ADD, word);
	ASSERT_EQ(previous - 2, byteStream.getSize());
}

TEST(ByteStreamTest, testReadInt) {
	ByteStream byteStream;
	byteStream.addInt(INT_ADD);
	const size_t previous = byteStream.getSize();
	int32_t dword = byteStream.readInt();
	ASSERT_EQ(INT_ADD, dword);
	ASSERT_EQ(previous - 4, byteStream.getSize());
}

TEST(ByteStreamTest, testReadFloat) {
	ByteStream byteStream;
	const float expected = 0.1f;
	byteStream.addFloat(expected);
	const size_t previous = byteStream.getSize();
	const float dword = byteStream.readFloat();
	ASSERT_DOUBLE_EQ(expected, dword);
	ASSERT_EQ(previous - 4, byteStream.getSize());
}

TEST(ByteStreamTest, testReadString) {
	ByteStream byteStream;
	const std::string str = "hello IT!";
	byteStream.addString(str);
	const size_t previous = byteStream.getSize();
	const std::string readstr = byteStream.readString();
	ASSERT_EQ(str, readstr);
	ASSERT_EQ(previous - str.length() - 1, byteStream.getSize());
}

TEST(ByteStreamTest, testReadStrings) {
	ByteStream byteStream;
	byteStream.addString("hello IT!");
	byteStream.addString("some other string");
	byteStream.addString("yet another string");
	byteStream.addString("0");
	byteStream.readString();
	byteStream.readString();
	byteStream.readString();
	ASSERT_EQ("0", byteStream.readString());
}

TEST(ByteStreamTest, testReadWriteVariadic) {
	ByteStream byteStream;
	const uint8_t byte = BYTE_ADD;
	const int16_t word = SHORT_ADD;
	const int32_t dword = INT_ADD;
	int pByte;
	int pShort;
	int pInt;
	byteStream.addFormat("bsi", byte, word, dword);
	byteStream.readFormat("bsi", &pByte, &pShort, &pInt);
	ASSERT_TRUE(byte == pByte);
	ASSERT_TRUE(word == pShort);
	ASSERT_TRUE(dword == pInt);
}

TEST(ByteStreamTest, testReadWriteAll) {
	ByteStream byteStream;
	srandom(SDL_GetTicks());
	uint8_t byte = random() % BYTE_ADD;
	int16_t word = random() % SHORT_ADD;
	int32_t dword = random() % INT_ADD;
	float floatv = floorf((random() % INT_ADD) / float(INT_ADD) * 100.0)
			/ 100.0;
	size_t size = sizeof(byte) + sizeof(word) + sizeof(dword) + sizeof(floatv);
	byteStream.addByte(byte);
	byteStream.addShort(word);
	byteStream.addInt(dword);
	byteStream.addFloat(floatv);
	ASSERT_EQ(byteStream.getSize(), size);
	ASSERT_EQ(byteStream.readByte(), byte);
	ASSERT_EQ(byteStream.getSize(), size -= 1);
	ASSERT_EQ(byteStream.readShort(), word);
	ASSERT_EQ(byteStream.getSize(), size -= 2);
	ASSERT_EQ(byteStream.readInt(), dword);
	ASSERT_EQ(byteStream.getSize(), size -= 4);
	ASSERT_DOUBLE_EQ(byteStream.readFloat(), floatv);
	ASSERT_EQ(byteStream.getSize(), size_t(0));
}

typedef enum DataType {
	e_byte = 0, e_short, e_int, e_float, e_string, count
} DataType;

typedef struct TypeValue {
	DataType type;
	void* pValue;
} TypeValue;

typedef std::vector<TypeValue> TypeValueList;
typedef TypeValueList::iterator TypeValueListIter;

TEST(ByteStreamTest, testRandomReadWrite) {
	ByteStream byteStream;
	srandom(SDL_GetTicks());

	TypeValueList _typeValueList;
	TypeValueListIter _typeValueListIter;

	unsigned int iterations = random() % 20 + 1;
	unsigned int index = 0;
	size_t size = 0;

	//add random types to byte stream
	do {
		DataType dataType = DataType(random() % count);
		TypeValue typeValue;
		typeValue.type = dataType;
		switch (dataType) {
		case e_byte: {
			uint8_t* byte = new uint8_t(random() % BYTE_ADD);
			byteStream.addByte(*byte);
			typeValue.pValue = byte;
			size += 1;
			break;
		}
		case e_short: {
			int16_t* word = new int16_t(random() % SHORT_ADD);
			byteStream.addShort(*word);
			typeValue.pValue = word;
			size += 2;
			break;
		}
		case e_int: {
			int32_t* dword = new int32_t(random() % INT_ADD);
			byteStream.addInt(*dword);
			typeValue.pValue = dword;
			size += 4;
			break;
		}
		case e_float: {
			float* dword = new float(
					floorf((random() % INT_ADD) / float(INT_ADD) * 100.0)
							/ 100.0);
			byteStream.addFloat(*dword);
			typeValue.pValue = dword;
			size += 4;
			break;
		}
		case e_string: {
			std::string* str = new std::string("hello IT!");
			byteStream.addString(*str);
			typeValue.pValue = str;
			size += str->length() + 1; //plus the '\0' char
			break;
		}
		default:
			ASSERT_TRUE(false);
			break;
		}
		_typeValueList.push_back(typeValue);
	} while (index++ < iterations);
	ASSERT_EQ(byteStream.getSize(), size);

	//read and verify added types in byte stream
	index = 0;
	do {
		DataType dataType = _typeValueList.front().type;
		void* value = _typeValueList.front().pValue;
		switch (dataType) {
		case e_byte: {
			uint8_t byte = byteStream.readByte();
			size -= 1;
			ASSERT_EQ(byte, *(uint8_t* ) value);
			delete (uint8_t*) value;
			break;
		}
		case e_short: {
			int16_t word = byteStream.readShort();
			size -= 2;
			ASSERT_EQ(word, *(int16_t* ) value);
			delete (int16_t*) value;
			break;
		}
		case e_int: {
			int32_t dword = byteStream.readInt();
			size -= 4;
			ASSERT_EQ(dword, *(int32_t* ) value);
			delete (int32_t*) value;
			break;
		}
		case e_float: {
			float dword = byteStream.readFloat();
			size -= 4;
			ASSERT_DOUBLE_EQ(dword, *(float* ) value);
			delete (float*) value;
			break;
		}
		case e_string: {
			std::string str = byteStream.readString();
			size -= str.length() + 1; //plus the '\0' char
			ASSERT_EQ(str, *(std::string* ) value);
			delete (std::string*) value;
			break;
		}
		default:
			ASSERT_TRUE(false);
			break;
		}
		_typeValueList.erase(_typeValueList.begin());
		ASSERT_EQ(byteStream.getSize(), size);
	} while (index++ < iterations);
	ASSERT_EQ(byteStream.getSize(), size_t(0));
}
