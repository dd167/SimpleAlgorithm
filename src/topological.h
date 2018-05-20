#pragma once
#include "dfs.h"
#include "depth_first_order.h"

/*
 拓扑排序：基于定理：一副有向无环图的拓扑顺序即为所有顶点的逆后序排列。
 由于无环是拓扑排序的前提，所以需要先检测有向图是否无环。

 拓扑排序主要用于解决 “优先级限制下的调度问题”，下面是应用举例：
 应用        顶点   边
 1）任务调度  任务   优先级限制
 2）课程安排  课程   先导课程限制
 3）符号链接  文件名  链接
 4）继承     Java类  extends关系

*/

class Topological
{
private:
	std::list<int> _order; //顶点的拓扑排序

public:
	Topological( const Digraph& g )
	{
		DirectedCycle cyclefinder( g );
		if( !cyclefinder.hasCycle() )
		{
			DepthFirstOrder dfo(g);
			_order = dfo.reversePost();
		}
	}

	Topological( const EdgeWeightedDigraph& g )
	{
		EdgeWeightedCycle cyclefinder( g );
		if( !cyclefinder.hasCycle() )
		{
			DepthFirstOrder dfo(g);
			_order = dfo.reversePost();
		}
	}

	std::list<int>& order()
	{
		return _order;
	}

	bool isDAG()
	{
		return !_order.empty();
	}


};


