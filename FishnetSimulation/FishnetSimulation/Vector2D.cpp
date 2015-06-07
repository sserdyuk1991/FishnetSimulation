#include "Vector2D.h"

#include <math.h>

Vector2D::Vector2D() : x( 0 ), y( 0 )
{}

Vector2D::Vector2D( double inX = 0, double inY = 0 ) : x( inX ), y( inY )
{}

void Vector2D::setX( double x )
{
	this->x = x;
}

void Vector2D::setY( double y )
{
	this->y = y;
}

double Vector2D::getX()
{
	return x;
}

double Vector2D::getY()
{
	return y;
}

Vector2D &Vector2D::operator=( Vector2D right )
{
	x = right.x;
	y = right.y;
	return *this;
}

Vector2D Vector2D::operator+( Vector2D right )
{
	return Vector2D( x + right.x, y + right.y );
}

Vector2D Vector2D::operator-( Vector2D right )
{
	return Vector2D( x - right.x, y - right.y );
}

Vector2D Vector2D::operator*( double value )
{
	return Vector2D( x * value, y * value );
}

Vector2D Vector2D::operator/( double value )
{
	return Vector2D( x / value, y / value );
}

Vector2D &Vector2D::operator+=( Vector2D right )
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2D &Vector2D::operator-=( Vector2D right )
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2D &Vector2D::operator*=( double value )
{
	x *= value;
	y *= value;
	return *this;
}

Vector2D &Vector2D::operator/=( double value )
{
	x /= value;
	y /= value;
	return *this;
}

Vector2D Vector2D::operator-()
{
	return Vector2D( -x, -y );
}

double Vector2D::length()
{
	return sqrt( x * x + y * y );
};			   		

void Vector2D::unitize()
{
	double length = this->length();

	if ( length == 0 )
		return;

	x /= length;
	y /= length;
}

Vector2D Vector2D::unit()
{
	double length = this->length();

	if ( length == 0 )
		return *this;
		
	return Vector2D( x / length, y / length );
}