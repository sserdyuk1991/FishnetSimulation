#pragma once

#include "Vector2D.h"

class Node
{
public:
	Node( double );
	void setMass( double );
	void setPosition( Vector2D );
	void setVelocity( Vector2D );
	double getMass();
	Vector2D getPosition();
	Vector2D getVelocity();
	void applyForce( Vector2D );
	void init();
	void simulate( double );
    void fixNode();
    void releaseNode();
    bool nodeIsFixed();
private:
	double mass;
    bool isFixed;
	Vector2D position;
	Vector2D velocity;
	Vector2D force;
};

