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

	return 0;
}