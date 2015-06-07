#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D( double, double );
	void setX( double );
	void setY( double );
	double getX();
	double getY();
	Vector2D &operator=( Vector2D );
	Vector2D operator+( Vector2D );
	Vector2D operator-( Vector2D );
	Vector2D operator*( double );
	Vector2D operator/( double );
	Vector2D &operator+=( Vector2D );
	Vector2D &operator-=( Vector2D );
	Vector2D &operator*=( double );
	Vector2D &operator/=( double );
	Vector2D operator-();
	double length();
	void unitize();
	Vector2D unit();
private:
	double x;
	double y;
};

