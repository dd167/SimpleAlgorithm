#pragma once
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