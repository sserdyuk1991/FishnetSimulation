#include "Simulation.h"

#include <windows.h>

Simulation::Simulation( int inNumberOfRows,
						int inNumberOfColumns,
					    double mass, 
						double springConstant,
						double springLength,
						double springFrictionConstant, 
						Vector2D inGravitation,
						double inAirFrictionConstant)
	: numberOfRows( inNumberOfRows )
	, numberOfColumns( inNumberOfColumns )
	, nodes( numberOfRows, std::vector< Node >( numberOfColumns, Node( mass ) ) )
	, gravitation( inGravitation )
	, airFrictionConstant( inAirFrictionConstant )
{
	for ( int i = 0; i < numberOfRows; ++i )
		for ( int j = 0; j < numberOfColumns; ++j )
			nodes[ i ][ j ].setPosition( Vector2D( ( j - numberOfColumns / 2 )
				* springLength, ( numberOfRows / 2 - i ) * springLength ) );

	for ( int i = 0; i < numberOfRows; ++i )
		for ( int j = 0; j < numberOfColumns; ++j )
			if ( j != numberOfColumns - 1 && i != numberOfRows - 1 )
			{
				constraints.push_back( Constraint( nodes[ i ][ j ], 
					nodes[ i ][ j + 1 ], springConstant, springLength, 
					springFrictionConstant ) );
				constraints.push_back( Constraint( nodes[ i ][ j ], 
					nodes[ i + 1][ j ], springConstant, springLength,
					springFrictionConstant ) );
			}
			else if ( i == numberOfRows - 1 && j != numberOfColumns - 1 )
			{
				constraints.push_back( Constraint( nodes[ i ][ j ], 
					nodes[ i ][ j + 1 ], springConstant, springLength, 
					springFrictionConstant ) );
			}
			else if ( j == numberOfColumns - 1 && i != numberOfRows - 1 )
			{
				constraints.push_back( Constraint( nodes[ i ][ j ], 
					nodes[ i + 1 ][ j ], springConstant, springLength, 
					springFrictionConstant ) );
			}
}

Node& Simulation::getNode( int i, int j )
{
	if ( i >= 0 && i < numberOfRows )
		if ( j >= 0 && j < numberOfColumns )
			return nodes[ i ][ j ];
}

int Simulation::getNumberOfRows()
{
	return numberOfRows;
}

int Simulation::getNumberOfColumns()
{
	return numberOfColumns;
}

void Simulation::init()
{
	for ( int i = 0; i < numberOfRows; ++i )
		for ( int j = 0; j < numberOfColumns; ++j )
			nodes[ i ][ j ].init();
}

void Simulation::solve()
{
	for ( int i = 0; i < constraints.size(); ++i )
		constraints[ i ].solve();

	for ( int i = 0; i < numberOfRows; ++i )
		for ( int j = 0; j < numberOfColumns; ++j )
		{
			nodes[ i ][ j ].applyForce( gravitation * 
				nodes[ i ][ j ].getMass() );
			nodes[ i ][ j ].applyForce( -nodes[ i ][ j ].getVelocity() * 
				airFrictionConstant );
		}
}

void Simulation::simulate( double dt )
{
	for ( int i = 0; i < numberOfRows; ++i )
		for ( int j = 0; j < numberOfColumns; ++j )
		{
			if ( i == 0 && ( j == 0 || j == numberOfColumns - 1 ) || 
				nodes[ i ][ j ].nodeIsFixed() )
				continue;

			nodes[ i ][ j ].simulate( dt );
		}
}

void Simulation::operate( double dt )
{
	init();
	solve();
	simulate( dt );
}