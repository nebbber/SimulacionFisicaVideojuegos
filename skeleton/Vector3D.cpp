#include "Vector3D.h"

Vector3D::Vector3D(int _x, int _y, int _z):x(_x),y(_y),z(_z)
{
}

float Vector3D::getX()
{
    return x;
}

float Vector3D::getY()
{
    return y;
}

float Vector3D::getZ()
{
    return z;
}

void Vector3D::setX(float n)
{
    this->x = n;
}

void Vector3D::setY(float n)
{
    this->y = n;
}

void Vector3D::setZ(float n)
{
    this->z = n;
}

float Vector3D::normaliceAndGetModule()
{
 
    float modulo = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));

    setX(this->x/modulo);
    setY(this->y / modulo);
    setZ(this->z / modulo);

    return modulo;
}

float Vector3D::getEscalar(Vector3D vect)
{
    return this->x * vect.x + this->y * vect.y + this->z * vect.z;
}

Vector3D Vector3D::multiplyEscalar(float n)
{
    
    return Vector3D(this->x * n, this->y * n, this->z * n);
}

Vector3D& Vector3D::operator=(Vector3D& vect)
{
    Vector3D a(this->x = vect.x, this->y = vect.y, this->y = vect.z);
     return a;
}

Vector3D& Vector3D::operator+(Vector3D& vect)
{
    Vector3D a(this->x + vect.x, this->y + vect.y, this->y = + vect.z);
    return a;
}

Vector3D& Vector3D::operator-(Vector3D& vect)
{
    Vector3D a(this->x - vect.x, this->y - vect.y, this->y - vect.z);
    return a;
}

Vector3D& Vector3D::operator*(Vector3D& vect)
{
    Vector3D a(this->x * vect.x, this->y * vect.y, this->y * vect.z);
    return a;
}
