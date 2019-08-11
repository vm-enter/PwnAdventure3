#include "stdafx.h"

#include "Vector3.hpp"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3 & Vector3::operator+(Vector3 & r)
{
	return Vector3(
		r.x + this->x,
		r.y + this->y, 
		r.z + this->z);
}

Vector3 & Vector3::operator=(Vector3 & r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
	return *this;
}

Vector3 & Vector3::operator+=(Vector3 & r)
{
	this->x += r.x;
	this->y += r.y;
	this->z += r.z;
	return *this;
}

float Vector3::ToDistance(Vector3 * r)
{
	return ((this->x - r->x) * (this->x - r->x)) +
		   ((this->y - r->y) * (this->y - r->y)) +
		   ((this->z - r->z) * (this->z - r->z));
}

bool Vector3::IsZero()
{
	return (this->x == 0 && this->y == 0 && this->z == 0);
}

Rotation::Rotation()
{
	this->pitch = 0;
	this->yaw = 0;
	this->roll = 0;

}
Rotation::Rotation(float pitch, float yaw, float roll)
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;
}
Rotation& Rotation::operator+(Rotation &r)
{
	return Rotation(
		r.pitch + this->pitch,
		r.yaw + this->yaw,
		r.roll + this->roll);
}