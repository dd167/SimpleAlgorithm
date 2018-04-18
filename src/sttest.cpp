#include "binary_search_st.h"
#include <iostream>
#include <string>

int main()
{


	binary_search_st<std::string, int> st1(100);
	
	st1.put("tom", 100);
	st1.put("jack", 99);
	st1.put("jack", 80);

	int r1 = st1.rank("tom");
	int r2 = st1.rank("jack");
	int r3 = st1.rank("jason");

	std::cout << "tom's rank=" << r1 << std::endl;
	std::cout << "jack's rank=" << r2 << std::endl;
	std::cout << "jason's rank=" << r3 << std::endl;


	int* v = st1.get("jack");
	if( v != nullptr )
	{
		std::cout << "jack=" << *v << std::endl;
	}

	st1.remove("jack");
	v = st1.get("jack");
	if( v == nullptr )
	{
		std::cout << "jack not found after remove!" << std::endl;
	}
	else
	{
		std::cout << "error: jack exist after remove: " << *v << std::endl;
	}





	return 0;
}