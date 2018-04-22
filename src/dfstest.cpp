#include "dfs.h"
#include <iostream>


int main()
{
	//algorth 4th , pages340
	int edge[][2] = {
		{0,5},{2,4},{2,3},{1,2},{0,1},{3,4},{3,5},{0,2}
	};

	std::cout << "sizeof(edge)=" << sizeof(edge) << ", sizeof(edge[0])=" << sizeof(edge[0]) << std::endl;

	Graph g(6);
	for( int i = 0; i < sizeof(edge)/sizeof(edge[0]); ++i )
	{
		g.addEdge( edge[i][0], edge[i][1] );
		//std::cout << i << std::endl;
	}

	DepthFirstPath dfp(g, 0);

	std::vector<int> pathTo4 = dfp.pathTo(4);
	if( pathTo4.empty() )
	{
		std::cout << "there is no way from 0 to 4" << std::endl;
	}
	else
	{
		for( auto i : pathTo4 )
		{
			std::cout << i << "->";
		}
		std::cout << std::endl;
	}

	Cycle cy(g);
	if( cy.hasCycle() )
	{
		std::cout << "g has cycle!" << std::endl;
	}
	else
	{
		std::cout << "g dosen't have cycle!" << std::endl;
	}

	TwoColor tc(g);
	if( tc.isBipartite() )
	{
		std::cout << "g can bipartitie! " << std::endl;
	}
	else
	{
		std::cout << "g can't bipartite!" << std::endl;
	}

	return 0;
}