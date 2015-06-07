#pragma once

#include "Node.h"
#include "Constraint.h"

#include <vector>
using std::vector;

class Simulation
{
public:
	Simulation( int, int, double, double, double, double, Vector2D, double );
	Node& getNode( int, int );
	int getNumberOfRows();
	int getNumberOfColumns();
	void init();
	void solve();
	void simulate( double );
	void operate( double );
private:
	int numberOfRows;
	int numberOfColumns;
	vector< vector< Node > > nodes;
	vector< Constraint > constraints;
	Vector2D gravitation;
	double airFrictionConstant;
};