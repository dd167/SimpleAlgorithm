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

	~DepthFirstSearch()
	{
		delete [] _marked;
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

	~DepthFirstPath()
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

	~Cycle()
	{
		delete [] _marked;
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
	有向图寻找环

*/
#include <list>
class DirectedCycle
{
private:
	bool* _marked;
	int * _edgeTo;
	int * _onStack;
	std::list<int> _cycle;
public:

	DirectedCycle( const Digraph& g )
	{
		_marked = new bool[ g.V() ];
		_edgeTo = new int[ g.V() ];
		_onStack = new int[ g.V() ];
		for( int i = 0; i < g.V(); ++i )
			_onStack[i] = 0;

		for( int s = 0; s < g.V(); ++s )
		{
			if( !_marked[s])
				dfs( g, s );
		}
	}

	
	~DirectedCycle()
	{
		delete [] _marked;
		delete [] _edgeTo;
		delete [] _onStack;
	}

	bool hasCycle()
	{
		return !_cycle.empty();
	}

	std::list<int>& cycle()
	{
		return _cycle;
	}

private:
	void dfs( const Digraph& g, int v )
	{
		_onStack[v] = 1;
		_marked[v] = true;

		for( int w : g.adj(v) )
		{
			if( hasCycle() )
				return;
			else if( !_marked[w] )
			{
				_edgeTo[w] = v;
				dfs( g, w );
			}
			else if( _onStack[w] == 1 )
			{
				//found cycle
				 for( int x = v; x != w; x = _edgeTo[x] )
				 	_cycle.push_front(x);

				 _cycle.push_front( w );
				 _cycle.push_front( v );
			}
		}
		_onStack[v] = 0;
	}
};



class EdgeWeightedCycle
{
private:
	bool* _marked;
	DirectedEdge * _edgeTo;
	int * _onStack;
	std::list<DirectedEdge> _cycle;
public:

	EdgeWeightedCycle( const EdgeWeightedDigraph& g )
	{
		_marked = new bool[ g.V() ];
		_edgeTo = new DirectedEdge[ g.V() ];
		_onStack = new int[ g.V() ];
		for( int i = 0; i < g.V(); ++i )
			_onStack[i] = 0;

		for( int s = 0; s < g.V(); ++s )
		{
			if( !_marked[s] )
				dfs( g, s );
		}
	}

	~EdgeWeightedCycle()
	{
		delete [] _marked;
		delete [] _edgeTo;
		delete [] _onStack;
	}

	bool hasCycle()
	{
		return !_cycle.empty();
	}

	std::list<DirectedEdge>& cycle()
	{
		return _cycle;
	}

private:

	/*
	 图中的一个节点，根据其C[N]的值，有三种状态：
     0，此节点没有被访问过
     -1，被访问过至少1次，其后代节点正在被访问中
     1，其后代节点都被访问过。
     按照这样的假设，当按照DFS进行搜索时，碰到一个节点时有三种可能：
     1、如果C[V]=0，这是一个新的节点，不做处理
     2、如果C[V]=-1，说明是在访问该节点的后代的过程中访问到该节点本身，则图中有环。
     3、如果C[V]=1，类似于2的推导，没有环。    在程序中加上一些特殊的处理，即可以找出图中有几个环，并记录每个环的路径
	*/
	void dfs( const EdgeWeightedDigraph& g, int v )
	{
		_onStack[v] = -1;
		_marked[v] = true;

		for( DirectedEdge e : g.adj(v) )
		{
			int w = e.to();

			if( hasCycle() )
				return;
			
			if( !_marked[w] )
			{
				_edgeTo[w] = e;
				dfs( g, w );
			}
			else if( _onStack[w] == -1 )
			{
				//std::cout << "w=" << w << "; v= " << v << std::endl;
				//found cycle
				DirectedEdge f = e;
                while (f.from() != w) 
                {
                    _cycle.push_front(f);
                    f = _edgeTo[f.from()];
                }
                _cycle.push_front(f);
			}
		}

		_onStack[v] = 1;		
	}
};







/*
	G是二分图吗？（双色问题）

*/

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

	~TwoColor()
	{
		delete [] _marked;
		delete [] _color;
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









