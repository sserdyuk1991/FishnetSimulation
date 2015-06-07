#include "Constraint.h"

Constraint::Constraint( Node& inNode1, 
					    Node& inNode2,
					    double inSpringConstant, 
					    double inSpringLength, 
					    double inFrictionConstant ) 
	: node1( inNode1 )
	, node2( inNode2 )
	, springConstant( inSpringConstant )
	, springLength( inSpringLength )
	, frictionConstant( inFrictionConstant )
{
}

void Constraint::solve()
{
	Vector2D springVector = node1.getPosition() - node2.getPosition();
   
	double r = springVector.length();
 
	Vector2D force;
   
	if ( r != 0 )
		force += -( springVector / r ) * ( r - springLength ) * springConstant;

	force += -( node1.getVelocity() - node2.getVelocity() ) * frictionConstant;

	node1.applyForce( force );
	node2.applyForce( -force );
}