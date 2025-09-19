#pragma once
#include <math.h>
class Vector3D
{
private:
	int x, y, z;

public:

	//metodos
	
	Vector3D(int _x,int _y, int _z);

	float getX();
	float getY();
	float getZ();
	void setX(float n);
	void setY(float n);
	void setZ(float n);
	float normaliceAndGetModule();
	float getEscalar(Vector3D vect); //le llega un vector, da un num
	Vector3D multiplyEscalar(float n);

	//operadores
	Vector3D& operator=(Vector3D& vect);
	Vector3D& operator+(Vector3D& vect);
	Vector3D& operator-(Vector3D& vect);
	Vector3D& operator*(Vector3D& vect);

};

