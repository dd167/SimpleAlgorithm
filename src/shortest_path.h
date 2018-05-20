#pragma once

#include "graph.h"
#include "pq.h"
#include <limits>
#include <list>
#include <vector>
#include "topological.h"



/*
	最短路径之Dijkstra算法
	算法步骤：
	1）初始化： 初始化每个点到起点的距离为正无穷大，创建一个优先队列，将起点加入优先队列，初始化起点到起点的距离为0
	2）每次从优先队列中弹出一个顶点v（该顶点肯定是当前队列中离起点最近距离的点），释放该点对应的边v->w, 如果s->w的距离
	大于s->v->w的距离，则更新s->w = s->v+v->w, 并且把w加入优先队列或者更新优先队列中w点的距离值。
	3）不断重复第2个步骤，直到优先队列为空。
	适用模型：加权有向图， 不能有负权重边， 可以有环
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

	~DijkstraSP()
	{
		delete [] _edgeTo;
		delete [] _distTo;
		delete _pq;
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



/*
	最短路径算法之AcyclicSP
	适用模型：无环加权有向图， 不能有负权重边
	算法步骤：首先对无环有向图进行拓扑排序，按照排序后的顺序放松每条边，在已知加权图示无环的情况下，他是找出
	最短路径的最好方法
*/
class AcyclicSP
{
private:
	DirectedEdge* _edgeTo;
	double* _distTo;
public:
	AcyclicSP( const EdgeWeightedDigraph& g, int s )
	{
		_edgeTo = new DirectedEdge[ g.V() ];
		_distTo = new double[ g.V() ];
		for( int v = 0; v < g.V(); ++v )
			_distTo[v] = (std::numeric_limits<double>::max)();

		_distTo[s] = 0.0;

		Topological top(g);
		for( int v : top.order() )
		{
			relax( g, v );
		}
	}

	~AcyclicSP()
	{
		delete [] _edgeTo;
		delete [] _distTo;
	}


	double distTo( int v )
	{
		return _distTo[v];
	}

	bool hasPathTo( int v )
	{
		return _distTo[v] < (std::numeric_limits<double>::max)();
	}

	std::list<DirectedEdge> pathTo( int v )
	{
		std::list<DirectedEdge> rets;
		if( hasPathTo(v) )
		{
			for( DirectedEdge e = _edgeTo[v]; e.isValid(); e = _edgeTo[e.from()] )
				rets.push_front(e);
		}
		return rets;
	}

private:
	void relax( const EdgeWeightedDigraph& g, int v )
	{
		for( DirectedEdge e : g.adj(v) )
		{
			int w = e.to();

			//std::cout << _distTo[w] <<";" << _distTo[v];

			if( _distTo[w] > _distTo[v] + e.weight() )
			{
				_distTo[w] = _distTo[v] + e.weight();
				_edgeTo[w] = e;
			}
		}
	}
};



/*
     最短路径算法之Bellman-Ford算法

*/

class BellmanFordSP
{
private:
	double * 					_distTo;
	DirectedEdge* 				_edgeTo;
	bool*  						_onQ;	//该顶点是否存在于_queue中
	std::list<int>      		_queue; //正在被放松的顶点
	int 						_cost;  //relax()的调用次数
	//std::list<DirectedEdge> 	_cycle;	//_edgeTo中是否存在有负权重环
	bool                        _hasNegativeCycle;
public:

	BellmanFordSP( const EdgeWeightedDigraph& g, int s )
	{
		_distTo = new double[ g.V() ];
		_edgeTo = new DirectedEdge[ g.V() ];
		_onQ = new bool[ g.V() ];
		_cost = 0;
		_hasNegativeCycle = false;

		for( int v = 0; v < g.V(); ++v )
			_distTo[v] = (std::numeric_limits<double>::max)();

		_distTo[s] = 0;
		_queue.push_back(s);
		_onQ[s] = true;

		while( !_queue.empty() && !hasNegativeCycle() )
		{
			int v = _queue.front();
			_queue.pop_front();
			_onQ[v] = false;
			relax( g, v );
		}
	}


	~BellmanFordSP()
	{
		delete [] _distTo;
		delete [] _edgeTo;
		delete [] _onQ;
	}

	double distTo( int v )
	{
		return _distTo[v];
	}

	bool hasPathTo( int v )
	{
		return _distTo[v] < (std::numeric_limits<double>::max)();
	}

	std::list<DirectedEdge> pathTo( int v )
	{
		std::list<DirectedEdge> rets;
		if( hasPathTo(v) )
		{
			for( DirectedEdge e = _edgeTo[v]; e.isValid(); e = _edgeTo[e.from()] )
				rets.push_front(e);
		}
		return rets;
	}

	bool hasNegativeCycle()
	{
		return _hasNegativeCycle;
	}

private:

	void relax( const EdgeWeightedDigraph& g, int v )
	{
		for( DirectedEdge e : g.adj(v) )
		{
			int w = e.to();
			if( _distTo[w] > _distTo[v] + e.weight() )
			{
				_distTo[w] =_distTo[v] + e.weight();
				_edgeTo[w] = e;
				if( !_onQ[w] )
				{
					_queue.push_back( w );
					_onQ[w] = true;
				}
			}

			if( _cost++ % g.V() == 0 )
				findNegativeCycle(g.V());
		}
	}

	void findNegativeCycle( int V )
	{
		EdgeWeightedDigraph spt(V);
		for( int i = 0; i < V; ++i )
		{
			if( _edgeTo[i].isValid() )
			{
				spt.addEdge( _edgeTo[i] );
			}
		}

		EdgeWeightedCycle cycleFinder(spt);
		if( cycleFinder.hasCycle() )
		{
			//std::cout << "has cycle " << std::endl;
			for( DirectedEdge e : cycleFinder.cycle() )
			{
				if( _distTo[e.to()] > _distTo[e.from()] + e.weight() )
				{
					_hasNegativeCycle = true;
					break;
				}
			}
		}
	}

};





















