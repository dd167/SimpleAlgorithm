#pragma once

#include "graph.h"
#include <queue>

/*
无向图广度优先搜索基本实现：
广度优先搜索一般用于解决下列问题：

1） 单点最短路径： 给定一幅图和一个起点s, 回答"从s到给定目的顶点v是否存在一条路径？"， 如果有， 找出其中最短的那条。

*/



class BreadFirstPaths
{
public:
	BreadFirstPaths( const Graph& g, int s )
	{
		_marked = new bool[ g.V() ];
		_edgeTo = new int[ g.V() ];
		_s = s;
		bfs( g, s );
	}

	~BreadFirstPaths()
	{
		delete [] _marked;
		delete [] _edgeTo;
	}

	bool hasPathTo( int v )
	{
		return _marked[v];
	}

	std::vector<int> pathTo( int v )
	{
		std::vector<int> path;
		if( hasPathTo(v) )
		{
			for( int x = v; x != _s; x = _edgeTo[x] )
			{
				path.insert( path.begin(), x );
			}
			path.insert( path.begin(), _s );
		}
		return path;
	}

private:
	void bfs( const Graph& g, int s )
	{
		std::queue<int> fifo;
		_marked[s] = true;
		fifo.push( s );

		while( !fifo.empty() )
		{
			int v = fifo.front();
			fifo.pop();

			for( int w : g.adj(v) )
			{
				if( !_marked[w] )
				{
					_edgeTo[w] = v;
					_marked[w] = true;
					fifo.push( w );
				} 
			}
		}
	}

private:
	bool* _marked;
	int*  _edgeTo;
	int   _s;
};