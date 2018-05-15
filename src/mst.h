#pragma once
#include "graph.h"
#include <list>
#include "pq.h"


/*最小生成树：给定一幅加权无向图，找到它的一颗最小生成树(minimal spanning tree)
算法基本原理：
切分定理：在一幅加权图中，给定任意的切分，他的横切边中权重最小者必然属于图的最小生成树。
切分定理是解决最小生成树问题的所有算法的基础，更确切的说，这些算法都是一种贪心算法的特殊情况：使用切分
定理找到最小生成树的一条边， 不断重复直到找到最小生成树的所有边。

应用场景：在一幅图中，找到访问所有顶点且边的权值之和最小的无环联通子图，即最小生成树，如机场路线设计。
*/

class LazyPrimMST
{
private:
	bool* _marked;						//最小生成树的顶点
	std::list<Edge> mst;				//最小生成树的边
	PQ<Edge, std::less<Edge>> pq;		//横切边（包括失效的边)

public:
	LazyPrimMST( const EdgeWeightedGraph& g )
	{
		_marked = new bool[g.V()];

		//这里简化问题，假设g是连通的

		visit( g,  0 );

		while( !pq.empty() )
		{
			//1) 从pq中得到权重最小的边
			Edge e = pq.top();
			pq.pop();

			int v = e.either();
			int w = e.other(v);

			//之所以算法叫做延迟的Prim算法，是因为无效的边到这里才忽略，即PQ里面并不作删除无效边的操作（即时版本的算法会删除）。
			//因为两个顶点都在树里了，不可能是横切边了。
			if( _marked[v] && _marked[w] )  //跳过失效的边
				continue;

			mst.push_back( e );  //将边添加到树中

			if( !_marked[v] )	
				visit( g, v );

			if( !_marked[w] )
				visit( g, w );

		} 

	}


	~LazyPrimMST()
	{
		delete [] _marked;
	}


	std::list<Edge>& edges()
	{
		return mst;
	}

	double weight()
	{
		double val = 0;
		for( Edge& e : mst )
		{
			val += e.weight();
		}
		return val;
	}


private:
	void visit( const EdgeWeightedGraph& g, int v )
	{
		//标记顶点v并将所有连接v且未被标记顶点的边加入pq
		_marked[v] = true;
		for( Edge e : g.adj(v) )
		{
			if( !_marked[e.other(v)] )
				pq.push( e );
		}
	}

};





