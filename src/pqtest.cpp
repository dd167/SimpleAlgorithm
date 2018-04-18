#include "pq.h"
#include <random>
#include <iostream>

int main()
{	
	
	std::default_random_engine e;
	std::uniform_int_distribution<int> u(0,100);


	PQ<int> minPQ;
	PQ<int, std::greater<int>> maxPQ;
	for( int i = 0; i < 20; ++i )
	{
		int rnd = u(e);
		minPQ.push( rnd );
		maxPQ.push( rnd );
	}

	while( !minPQ.empty() )
	{
		std::cout << minPQ.top() << ",";
		minPQ.pop();
	}
	std::cout << std::endl;

	while( !maxPQ.empty() )
	{
		std::cout << maxPQ.top() << ",";
		maxPQ.pop();
	}
	return 0;
}