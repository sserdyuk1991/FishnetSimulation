#include "Node.h"

Node::Node( double inMass ) : mass( inMass ), isFixed( false )
{}

void Node::setMass( double mass )
{
	this->mass = mass;
}

void Node::setPosition( Vector2D position )
{
	this->position = position;
}

void Node::setVelocity( Vector2D velocity )
{
	this->velocity = velocity;
}

double Node::getMass()
{
	return mass;
}

Vector2D Node::getPosition()
{
	return position;
}

Vector2D Node::getVelocity()
{
	return velocity;
}

void Node::applyForce( Vector2D force )
{
	this->force += force;
}

void Node::init()
{
	force.setX( 0 );
	force.setY( 0 );
}

void Node::simulate( double dt )
{
	velocity += ( force / mass ) * dt;
	position += velocity * dt;
}

void Node::fixNode()
{
    isFixed = true;
}

void Node::releaseNode()
{
    isFixed = false;
}

bool Node::nodeIsFixed()
{
    return isFixed;
}