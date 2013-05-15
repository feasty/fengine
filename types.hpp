#ifndef FENGINE_TYPES_HPP
#define FENGINE_TYPES_HPP

//Unsigned
typedef unsigned char Byte;
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

//Signed
typedef char Int8;
typedef short Int16;
typedef int Int32;

//Vector 4
typedef struct Vec4
{
	Vec4(float x_in, float y_in, float z_in, float a_in)
	{
		x = x_in;
		y = y_in;
		z = z_in;
		a = a_in;
	}

	float	x;
	float	y;
	float	z;
	float	a;
} Vec4;

//Vector 3
typedef struct Vec3
{
	Vec3(float x_in, float y_in, float z_in)
	{
		x = x_in;
		y = y_in;
		z = z_in;
	}

	float	x;
	float	y;
	float	z;
} Vec3;

#endif //FENGINE_TYPES_HPP
