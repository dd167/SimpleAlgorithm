#pragma once

#include "graph.h"
//#include <string.h>
#include <vector>

/*
	深度优先搜索, 访问节点的顺序可以刚好用递归的方式实现
	深度优先搜索通常用于解决两方面问题：
	1） 连通性： 给定一幅图，回答“两个给定的顶点是否连通？” 或者 “图中有多少个连通子图”？
	2） 单点路径： 给定一幅图和一个起点s, 回答“从s到给定的目的顶点v是否存在一条路径?, 如果有，找出这条路径（注：
	这条路径只是众多可能路径中的一条，取决于邻接表中的先后顺序）“
*/
class DepthFirstSearch
{
public:
	DepthFirstSearch( const Graph& g, int s )
	{
		_marked = new bool[ g.V() ];
		//memset( _marked, 0, sizeof(bool)*g.V() );
		dfs( g, s );
	}

	bool marked( int w )
	{
		return _marked[w];
	}

	int count()
	{
		return _count;
	}

private:
	void dfs( const Graph& g, int v )
	{
		_marked[v] = true;
		_count++;
		for( int w : g.adj(v) )
		{
			if( !_marked[w] )
				dfs( g, w );
		}
	}


private:
	bool* _marked;
	int  _count;
};


class DepthFirstPath
{
public:
	DepthFirstPath( const Graph& g, int s )
	{
		_marked = new bool[ g.V() ];
		//memset( _marked, 0, sizeof(bool)*g.V() );
		_edgeTo = new int[ g.V() ];
		_s = s;
		dfs( g, s );
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
	void dfs( const Graph& g, int v )
	{
		_marked[v] = true;
		for( int w : g.adj(v) )
		{
			if( !_marked[w] )
			{
				_edgeTo[w] = v;
				dfs( g, w );
			} 
		}
	}



private:
	bool* _marked;  //这个顶点上调用过dfs了吗？
	int*  _edgeTo;  //从起点到一个顶点的已知路径上的最后一个顶点
	int   _s;       //起点
};



/*
	G 是无环图吗？（假设不存在自环或平行边）
*/
class Cycle
{
public:
	Cycle( const Graph& g )
	{
		_hasCycle = false;
		_marked = new bool[ g.V() ];
		//memset( _marked, 0, sizeof(bool)*g.V() );
		for( int s = 0; s < g.V(); ++s )
		{
			if( !_marked[s])
				dfs( g, s, s );
		}

	}

	bool hasCycle()
	{
		return _hasCycle;
	}

private:
	void dfs( const Graph& g, int v, int u )
	{
		_marked[v] = true;
		for( int w : g.adj(v) )
		{
			if( !_marked[w] )
				dfs( g, w, v );
			else if( w != u )
			{
				_hasCycle = true;
				return;
			}
		}

	}


private:
	bool* _marked;
	bool  _hasCycle;
};




/*
	G是二分图吗？（双色问题）

*/
#include <iostream>
class TwoColor
{
public:
	TwoColor(const Graph& g)
	{
		_marked = new bool[g.V()]();	
		_color = new bool[g.V()]();
		_isTowColorable = true;
		for( int s = 0; s < g.V(); ++s )
		{
			if( !_marked[s] )
				dfs(g,s);
		}
	}

	bool isBipartite()
	{
		return _isTowColorable;
	}

private:
	void dfs( const Graph& g, int v )
	{
		_marked[v] = true;
		for( int w : g.adj(v) )
		{
			if( !_marked[w] )
			{
				_color[w] = !_color[v];
				dfs( g, w );
			}
			else if( _color[w] == _color[v] )
			{
				_isTowColorable = false;
				return;
			}
		}
	}


private:
	bool* _marked;
	bool* _color;
	bool _isTowColorable;
};









