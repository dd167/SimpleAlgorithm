#include <iostream>
#include "bag.h"
#include "graph.h"


int main()
{
	Bag<int> bag;
	bag.add( 1 );
	bag.add( 2 );


	std::cout << "iterator bag mode c++1:" << std::endl;
	for( auto v : bag )
	{
		std::cout << v << std::endl;
	}

	std::cout << "iteartor bag mode legacy:" << std::endl;
	Bag<int>::iterator it = bag.begin();
	for( ; it != bag.end(); ++it )
	{
		std::cout << *it << std::endl;
	}


	std::cout << "graph test" << std::endl;
	Graph g(3);
	g.addEdge( 0, 1 );
	g.addEdge( 0, 2 );
	g.addEdge( 1, 2 );


	for( auto i : g.adj(0) )
	{
		std::cout << i << std::endl;
	}

	for( auto i : g.adj(1) )
	{
		std::cout << i << std::endl;
	}





	return 0;
}