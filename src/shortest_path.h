#pragma once

#include "graph.h"
#include <map>



/*
	Dijkstra算法能够解决边权重非负的加权有向图的单起点最短路径问题
*/
class DijkstraSP
{
private:
	DirectedEdge* _edgeTo;		
	double* _distTo;
	std::map<int, double> _pq;

public:

	DijkstraSP( const EdgeWeightedDigraph& g, int s )
	{
		_edgeTo = new DirectedEdge[ g.V() ];
		_distTo = new double[ g.V() ];

		for( int v = 0; v < g.V(); ++v )
		{
			_distTo[v] = 0.0;
			_pq.insert( std::map<int,double>::value_type(v, 0.0) );

			while( !_pq.empty() )
			{
				relax( g, pq.)
			}
		}
	}

private:
	void relax( const EdgeWeightedDigraph& g, int v )
	{
		for( DirectedEdge e : g.adj(v) )
		{
			int w = e.to();
			if( _distTo[w] > _distTo[v] + e.weight() )
			{
				_distTo[w] = _distTo[v] + e.weight();
				_edgeTo[w] = e;
				_pq[w] = _distTo[w];
			}
		}
	}
}；




