#pragma once
#include <string>

/*
	子字符串查找 - 暴力查找
*/
class SubStringSearch_Force
{
public:
	static int search(const std::string& txt, const std::string& pat, int startIndex = 0)
	{
		int M = pat.length();
		int N = txt.length();

		for( int i = startIndex; i <= N - M; ++i )
		{
			int j;
			for( j = 0; j < M; ++j )
				if( txt[i+j] != pat[j] )
					break;

			if( j == M )
				return i;
		}
		return -1;
	}
};



/*
	子字符串查找 - Knuth-Morris-Pratt
	https://kb.cnblogs.com/page/176818/

*/
class SubStringSearch_KMP
{
private:
	std::string _pat;
	int**       _dfa;
public:
	SubStringSearch_KMP( const std::string& pat )
	{
		_pat = pat;
		int M = pat.length();
		int R = 256;
		_dfa = new int*[R];
		for( int i = 0; i < R; ++i )
			_dfa[i] = new int[M]{0};


		 _dfa[ pat[0] ][0] = 1;
		for( int X = 0, j = 1; j < M; ++j )
		{
		 	for( int c = 0; c < R; ++c )
		 	{
		 		_dfa[c][j] = _dfa[c][X]; 	//复制匹配失败情况下的值
		 	}

		 	_dfa[ pat[j] ][j] = j + 1; 		//设置匹配成功情况下的值
		 	X = _dfa[ pat[j] ][X]; 			//更新重启状态

		 	std::cout << "X=" << X << std::endl;
		}
	
	} 

	~SubStringSearch_KMP()
	{
		for( int i = 0; i < 256; ++i )
			delete [] _dfa[i];

		delete [] _dfa;
	}

	int search( const std::string& txt, int startIndex = 0)
	{
		int i, j, N = txt.length(), M = _pat.length();

		for( i = startIndex, j = 0; i < N && j < M; ++i )
			j = _dfa[ txt[i] ][j];

		if( j == M )
			return i - M;
		else
			return -1;
	}
};




