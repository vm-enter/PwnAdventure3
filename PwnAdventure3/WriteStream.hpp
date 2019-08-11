#pragma once

#include <string>
#include <vector>

struct Vector3;
struct Rotation;

struct WriteStream
{
	SOCKET m_sock;
	std::vector<BYTE> m_buffer;

public:
	WriteStream();
	~WriteStream();

	void WriteString(std::string *val);
	void WriteVector(Vector3 *val, char _Last);
	void WriteVector16(Vector3 *val);
	void WriteRotation(Rotation *val);
	void Flush();
};