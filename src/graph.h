#pragma once
#include "base.h"
#include "bag.h"


//无向图基本数据结构

class Graph
{
private:
	int _V; //顶点数目
	int _E; //边的数目
	Bag<int>* _adj; //邻接表
public:

	Graph( int v )
	{
		_V = v;
		_E = 0;
		_adj = new Bag<int>[v];
	}

	int V() const { return _V; }
	int E() const { return _E; }

	void addEdge( int v, int w )
	{
		_adj[v].add(w);
		_adj[w].add(v);
		_E++;
	}

	const Bag<int>& adj( int v ) const
	{
		return _adj[v];
	}

};



//有向图基本结构
class Digraph
{
private:
	int _V; //顶点数目
	int _E; //边的数目
	Bag<int>* _adj; //邻接表

public:

	Digraph( int v )
	{
		_V = v;
		_E = 0;
		_adj = new Bag<int>[v];
	}

	int V() const { return _V; }
	int E() const { return _E; }

	void addEdge( int v, int w )
	{
		_adj[v].add(w);
		_E++;
	}

	const Bag<int>& adj( int v ) const
	{
		return _adj[v];
	}

	Digraph reverse() const
	{
		Digraph nd(_V);
		for( int v = 0; v < _V; ++v )
		{
			for( int w : adj(v) )
				nd.addEdge( w, v );
		}
		return nd;
	}
};


/*----------------------------------------------------------------------------------------
	加权无向图数据结构
*/
class Edge
{
private:
	int _v;
	int _w;
	double _weight;

public:
	Edge() : _v(-1), _w(-1), _weight(0){}

	Edge( int v, int w, double weight ) : _v(v), _w(w), _weight(weight)
	{}

	double weight()  const { return _weight; } 

	int either() const { return _v; }

	int other (int vertex) const
	{
		if( vertex == _v )
			return _w;
		else if( vertex == _w )
			return _v;
		else
			return -1; //means error
	}

	std::string toString()
	{
		//return format("%d-%d %.2f", _v, _w, _weight);
		char buf[32] = { 0 };
		snprintf( buf, 32, "%d-%d %.2f", _v, _w, _weight );
		return buf;
	}
};


bool operator < ( const Edge& lhs, const Edge& rhs )
{
	return lhs.weight() < rhs.weight();
}


class EdgeWeightedGraph
{
private:
	int _V;		//vertex count
	int _E;		//edge count;
	Bag<Edge>* _adj;//

public:
	EdgeWeightedGraph( int vertexCount )
	{
		_V = vertexCount;
		_E = 0;
		_adj = new Bag<Edge>[vertexCount];
	}


	int V() const { return _V; }
	int E() const { return _E; }

	void addEdge( int v, int w, double weight )
	{
		Edge edg(v, w, weight);
		addEdge(edg);
	}

	void addEdge( const Edge& e )
	{
		int v = e.either();
		int w = e.other(v);
		_adj[v].add( e );
		_adj[w].add( e );
		++_E;
	}

	const Bag<Edge>& adj( int v ) const
	{
		return _adj[v];
	}

};









/*----------------------------------------------------------------------------------------
	加权有向图数据结构
*/
class DirectedEdge
{
private:
	int _v;
	int _w;
	double _weight;

public:
	DirectedEdge( int v, int w, double weight ) : _v(v), _w(w), _weight(weight)
	{

	}

	double weight() const { return _weight; }

	int from() const { return _v; }

	int to() const { return _w; }

	std::string toString()
	{
		char buf[32] = { 0 };
		snprintf( buf, 32, "%d-%d %.2f", _v, _w, _weight);
		return buf;
	}

};

class EdgeWeightedDigraph
{
private:
	int _V;
	int _E;
	Bag<DirectedEdge>* _adj;

public:
	EdgeWeightedDigraph( int vertexCount )
	{
		_V = vertexCount;
		_E = 0;
		_adj = new Bag<DirectedEdge>[ vertexCount ];
	}

	int V() const { return _V; }
	int E() const { return _E; }

	void addEdge( const DirectedEdge& e )
	{
		_adj[e.from()].add(e);
		++_E;
	}

	void addEdge( int from, int to, double weight )
	{
		DirectedEdge e( from, to, weight );
		addEdge( e );
	}

	const Bag<DirectedEdge>& adj( int v ) const
	{
		return _adj[v];
	}

};
















