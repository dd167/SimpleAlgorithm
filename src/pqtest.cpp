#include "base.h"
#include "pq.h"
#include <random>
#include <iostream>

int main()
{	
	
	std::default_random_engine e;
	std::uniform_int_distribution<int> u(0,100);

	std::cout << "pq test:" << std::endl;
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


	std::cout << std::endl << "index pq test:" << std::endl;

	IndexPQ<double, std::less<double>> idxPq(10);
	idxPq.push(1, 1000);
	idxPq.push(2, 900);
	idxPq.push(3, 1100);

	while( !idxPq.empty() )
	{
		std::cout <<  idxPq.topIndex() << "=" << idxPq.pop() << ",";
	}
	std::cout << std::endl;


	idxPq.push(1, 1000);
	idxPq.push(2, 900);
	idxPq.push(3, 1100);	
	idxPq.changes(1, 500);
	while( !idxPq.empty() )
	{
		std::cout << idxPq.topIndex() << "=" << idxPq.pop() << ",";
	}
	std::cout << std::endl;

	idxPq.push(1, 1000);
	idxPq.push(2, 900);
	idxPq.push(3, 1100);		
	idxPq.remove(2);
	while( !idxPq.empty() )
	{
		std::cout << idxPq.topIndex() << "=" << idxPq.pop() << ",";
	}	


	return 0;
}