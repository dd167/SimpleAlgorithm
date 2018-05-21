#include <iostream>
#include "sub_string_search.h"



int main()
{
	std::string txt = "AABRAACADABRAACAADABRA";
	std::string pat = "AACAA";

	int rightPos = txt.find(pat);
	std::cout << "right pos = " << rightPos << std::endl;

	int p1 = SubStringSearch_Force::search(txt, pat);
	std::cout << "SubStringSearch_Force::search  = " << p1 << std::endl;


	SubStringSearch_KMP kmp(pat);
	int p2 = kmp.search( txt );
	std::cout << "SubStringSearch_KMP::search  = " << p2 << std::endl;

	return 0;
}