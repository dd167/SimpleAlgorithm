#pragma once

/*
	基于有序数组的符号表实现，查找使用二分查找效率高(lgN)，插入和删除效率很低(N*N)，
	可适用于对数据按照键值大量查找而无需插入和删除数据的场合。
*/


template<class K, class V>
class binary_search_st
{
public:
	binary_search_st( int capacity )
	{
		keys = new K[capacity];
		vals = new V[capacity];
		N = 0;
	}

	~binary_search_st()
	{
		delete [] keys;
		delete [] vals;
	}

	int size() { return N; }

	bool empty() { return N == 0; }

	V* get(const K& key)
	{
		if(empty()) return nullptr;
		int i = rank(key);
		if( i < N && keys[i] == key )
			return &vals[i];
		return nullptr;
	}

	bool contains(const K& key)
	{
		return get(key) != nullptr;
	}

	void put( const K& k, const V& v )
	{
		int i = rank(k);
		if( i < N && keys[i] == k )
		{
			vals[i] = v;
			return;
		}

		for( int j = N; j > i; --j )
		{
			keys[j] = keys[j-1];
			vals[j] = vals[j-1];
		}
		keys[i] = k;
		vals[i] = v;
		++N;
	}

	/*
		核心代码：使用二分查找，如果表中存在该键，返回该键的位置，也就是表中小于它的键的数量
		如果表中不存在该键，还是应该返回表中小于它的键的数量。
	*/
	int rank( const K& k )
	{
		int lo = 0, hi = N-1;
		while( lo <= hi )
		{
			int mid = lo + ( hi - lo ) / 2;
			if( k < keys[mid])
				hi = mid - 1;
			else if( k > keys[mid] )
				lo = mid + 1;
			else
				return mid;
		}
		return lo;
	}

	const K& min()
	{
		return keys[0];
	}

	const K& max()
	{
		return keys[N-1];
	}

	const K& select( int k )
	{
		return keys[k];
	}

	//找出大于等于该键的最小键
	const K& ceiling( const K& key )
	{
		int i = rank( key );
		return keys[i];
	}

	//找出小于等于该键的最大键
	K* floor( const K& key )
	{
		int i = rank(key);
		if( i < N-1 )
			return &keys[i+1];
		else
			return nullptr;	

	}

	void remove( const K& k )
	{
		int i = rank(k);
		if( i < N && keys[i] == k )
		{
			for( int j = i; j < N-1; ++j )
			{
				keys[j] = keys[j+1];
				vals[j] = vals[j+1];
			}
			--N;
		}		
	}


private:	
	K* keys;
	V* vals;
	int N;
};//end of class