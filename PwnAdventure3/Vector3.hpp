#pragma once

struct Vector3
{
	float x;
	float y;
	float z;

public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3& operator+(Vector3 &r);
	Vector3& operator=(Vector3 &r);
	Vector3& operator+=(Vector3 &r);

	float ToDistance(Vector3 *r);
	bool IsZero();
};

struct Rotation
{
	float pitch;
	float yaw;
	float roll;

public:
	Rotation();
	Rotation(float pitch, float yaw, float roll);
	Rotation& operator+(Rotation &r);
};

struct LocationAndRotation
{
	Vector3 location;
	Rotation rotation;

public:
	LocationAndRotation() {} // shared constructor
};