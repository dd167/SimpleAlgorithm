#pragma once

#include "graph.h"
#include "depth_first_order.h"


/*
	计算强连通分量的Kosaraju算法
	强连通分量是一种非常重要的抽象，它突出了相互关联的几组顶点，例如：强连通分量能够帮助教科书的作者决定哪些话题应该被
	归为一类，或者帮助网络工程师将网络中数量庞大的网页分为多个大小可以接受的子部分分别进行处理。

	Kosaraju算法步骤：
	1） 在给定的一副有向图G中，使用的DepthFirstOrder来计算它的反向图GR的逆后序排列。
	2）在G中进行标准的深度优先搜索， 但是要按照刚才计算得到的顺序。
	3）在第二步中，所有在同一个递归dfs()调用中被访问到的顶点都在同一个强连通分量中。
	证明见Page380.
*/


class KosarajuSCC
{

private:
	bool* _marked;
	int*  _id;			//强连通分量的标识符
	int   _count;		//强连通分量的个数

public:
	KosarajuSCC( const Digraph& g )
	{
		_marked = new bool[ g.V() ];
		_id = new int[ g.V() ];
		_count = 0;

		DepthFirstOrder dfo( g.reverse() );
		for( int s : dfo.reversePost() )
		{
			if( !_marked[s] )
			{
				dfs( g, s );
				++_count;
			}
		}
	}

	~KosarajuSCC()
	{
		delete [] _marked;
		delete [] _id;
	}


	bool stronglyConnected( int v, int w )
	{
		return _id[v] == _id[w];
	}

	int id( int v )
	{
		return _id[v];
	}

	int count()
	{
		return _count;
	}

private:
	void dfs( const Digraph& g, int v )
	{
		_marked[v] = true;
		_id[v] = _count;
		for( int w : g.adj(v) )
		{
			if( _marked[w] )
			{
				dfs( g, w );
			}
		}
	}

};

