#pragma once

#include "Node.h"

class Constraint
{
public:
	Constraint( Node&, Node&, double, double, double );
	void solve();
private:
	Node& node1;
	Node& node2;
	double springConstant;
	double springLength;
	double frictionConstant;
};