#pragma once

#include "graph.h"
#include "pq.h"
#include <limits>
#include <list>
#include <vector>



/*
	Dijkstra算法能够解决边权重非负的加权有向图的单起点最短路径问题
*/
class DijkstraSP
{
private:
	DirectedEdge* _edgeTo;		
	double* _distTo;
	IndexPQ<double>* _pq;

public:

	DijkstraSP( const EdgeWeightedDigraph& g )
	{
		_edgeTo = new DirectedEdge[ g.V() ];
		_distTo = new double[ g.V() ];
		_pq = new IndexPQ<double, std::less<double>>(g.V());
	}

	bool getPathTo( const EdgeWeightedDigraph& g, int start, int end, std::list<DirectedEdge>& path, double& dist  )
	{

		bool hasPath = search( g, start, end );

		if( !hasPath )
			return false;

		path.clear();
		for( DirectedEdge e = _edgeTo[end]; e.isValid(); e = _edgeTo[e.from()] )
		{
			path.push_front(e);
		}
		dist = _distTo[end];
		return true;
	}

private:
	bool search( const EdgeWeightedDigraph& g, int start, int end ) 
	{
		_pq->clear();
		for( int v = 0; v < g.V(); ++v )
		{
			_distTo[v] = (std::numeric_limits<double>::max)();
			_edgeTo[v].clear();		
		}

		_distTo[start] = 0.0;
		_pq->push( start, 0.0 );

		while( !_pq->empty() )
		{
			int shortestPathVertex = _pq->topIndex();
			_pq->pop();
			if( shortestPathVertex == end )
			{
				return true;
			}	
			relax( g, shortestPathVertex );
		}
		return false;
	}



	void relax( const EdgeWeightedDigraph& g, int v )
	{
		for( DirectedEdge e : g.adj(v) )
		{
			int w = e.to();
			if( _distTo[w] > _distTo[v] + e.weight() )
			{
				_distTo[w] = _distTo[v] + e.weight();
				_edgeTo[w] = e;
				if( _pq->contains(w) )
					_pq->changes(w, _distTo[w] );
				else
					_pq->push(w, _distTo[w]);
			}
		}
	}
};




