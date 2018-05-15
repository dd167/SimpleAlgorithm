#pragma once
#include <list>
#include "graph.h"


/*
	有向图中基于深度优先搜索的顶点排序， 它的基本思想是：深度优先搜索正好会访问每个顶点一次
*/

class DepthFirstOrder
{
private:
	bool* _marked;	
	std::list<int> _preOrder;	//前序：在递归调用之前将顶点加入队列
	std::list<int> _postOrder;	//后序：在递归调用之后将顶点加入队列
	std::list<int> _reversePostOrder; //逆后序：在递归调用之后将顶点压入堆栈

public:

	DepthFirstOrder( const Digraph& g )
	{
		_marked = new bool[g.V()];
		for( int v = 0; v < g.V(); ++v )
			if( !_marked[v] )	
				dfs( g, v );
	}

	DepthFirstOrder( const EdgeWeightedDigraph& g  )
	{
		_marked = new bool[g.V()];
		for( int v = 0; v < g.V(); ++v )
			if( !_marked[v] )	
				dfs( g, v );
	}

	std::list<int>& pre()
	{
		return _preOrder;
	}

	std::list<int>& post()
	{
		return _postOrder;
	}

	std::list<int>& reversePost()
	{
		return _reversePostOrder;
	}

private:
	void dfs( const Digraph& g, int v )
	{
		_preOrder.push_back( v );

		_marked[v] = true;
		for( int w : g.adj(v) )
			if( !_marked[w] )
				dfs( g, w );

		_postOrder.push_back( v );
		_reversePostOrder.push_front( v );
	}

	void dfs( const EdgeWeightedDigraph& g, int v )
	{
		_preOrder.push_back( v );

		_marked[v] = true;
		for( DirectedEdge e : g.adj(v) )
		{
			int t = e.to();
			if( !_marked[t] )
				dfs( g, t);
		}

		_postOrder.push_back( v );
		_reversePostOrder.push_front( v );
	}

};