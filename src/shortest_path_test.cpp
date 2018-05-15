#include "shortest_path.h"



int main()
{
	EdgeWeightedDigraph g(8);
	g.addEdge(4, 5, 0.35);
	g.addEdge(5, 4, 0.35);

	g.addEdge(4, 7, 0.37);
	g.addEdge(5, 7, 0.28);
	g.addEdge(7, 5, 0.28);
	g.addEdge(5, 1, 0.32);
	g.addEdge(0, 4, 0.38);
	g.addEdge(0, 2, 0.26);
	g.addEdge(7, 3, 0.39);
	g.addEdge(1, 3, 0.29);
	g.addEdge(2, 7, 0.34);
	g.addEdge(6, 2, 0.40);
	g.addEdge(3, 6, 0.52);
	g.addEdge(6, 0, 0.58);
	g.addEdge(6, 4, 0.93);


	std::cout << "DijkstraSP Test:" << std::endl;

	DijkstraSP dsp(g);
	std::list<DirectedEdge> path;
	double dist;
	for( int x = 0; x < 8; ++ x)
	{
		bool hasPath = dsp.getPathTo( g, 0, x, path, dist);
		std::cout << "0 to " << x << "(" << dist  << "):";
		if(hasPath)
		{
			for( auto e : path )
			{
				std::cout << e.toString() << " ";
			}			
		}
		else
		{
			std::cout << "no path!";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "AcyclicSP Test:" << std::endl;
	{
		EdgeWeightedDigraph g2(8);
		g2.addEdge(5, 4, 0.35);
		g2.addEdge(4, 7, 0.37);
		g2.addEdge(5, 7, 0.28);
		g2.addEdge(5, 1, 0.32);
		g2.addEdge(4, 0, 0.38);
		g2.addEdge(0, 2, 0.26);
		g2.addEdge(3, 7, 0.39);
		g2.addEdge(1, 3, 0.29);
		g2.addEdge(7, 2, 0.34);
		g2.addEdge(6, 2, 0.40);
		g2.addEdge(3, 6, 0.52);
		g2.addEdge(6, 0, 0.58);
		g2.addEdge(6, 4, 0.93);


		DirectedCycle cycleFinder(g2);
		if( cycleFinder.hasCycle() )
		{
			std::cout << "g2 has Cycle!" << std::endl;
		}
		else
		{
			const int start = 5;
			AcyclicSP asp(g2, start);
			for( int x = 0; x < 8; ++x )
			{
				bool hasPath = asp.hasPathTo(x);
				double dist = asp.distTo(x);
				std::cout << start << " to " << x << "(" << dist  << "):";
				if( hasPath )
				{
					path = asp.pathTo(x);
					for( auto e : path )
					{
						std::cout << e.toString() << " ";
					}	
				}
				else
				{
					std::cout << "no path!";
				}
				std::cout << std::endl;
			}
		}
	}
	
	return 0;
}