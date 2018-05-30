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

	SubStringSearch_BoyerMoore bm(pat);
	int p3 = bm.search( txt );
	std::cout << "SubStringSearch_BoyerMoore::search = " << p3 << std::endl;


	std::cout << "chinese test:" << std::endl;

	txt = "所看到飞机失控的疯狂的说法";
	pat = "飞机";
	rightPos = txt.find(pat);
	std::cout << "right pos = " << rightPos << std::endl;

	p1 = SubStringSearch_Force::search(txt, pat);
	std::cout << "SubStringSearch_Force::search  = " << p1 << std::endl;

	//下面算法不适用中文
	/*
	SubStringSearch_KMP kmpChinese(pat);
	p2 = kmpChinese.search( txt );
	std::cout << "SubStringSearch_KMP::search  = " << p2 << std::endl;

	SubStringSearch_BoyerMoore bmChinese(pat);
	int p4 = bmChinese.search( txt );
	std::cout << "SubStringSearch_BoyerMoore::search = " << p4 << std::endl;*/

	return 0;
}