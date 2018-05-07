#pragma once
#include "base.h"
#include <vector>

//数组实现的基于堆的优先队列（完全二叉树）
//性能分析：插入操作比较次数不超过lgN+1， 删除顶部元素比较次数不超过2lgN
//用途：适用于一个需要输入N个（非常大）数据，找出其中最大（或最小）的M个数据的场合。



template<class T, class Comp = std::less<T> >
class PQ
{
public:
	PQ() : data(1, T())
	{

	}

	~PQ() = default;

	bool empty()
	{
		return data.size() <= 1;
	}

	int size()
	{
		return data.size() - 1;
	}

	void push(const T& v)
	{
		data.push_back( v );
		swim( data.size() - 1 );
	}

	const T& top()
	{
		return data[1];
	}

	void pop()
	{
		data[1] = data[ data.size() -1 ];
		data.pop_back();
		sink( 1 );
	}


private:
	/*
		由下至上的堆有序化（上浮）
	*/
	void swim( int k )
	{
		while( k > 1 && !compare(k/2, k) )
		{
			exch(k/2, k);
			k = k/2;
		}
	}

	/*
		由上至下的堆有序化（下沉）
	*/
	void sink( int k )
	{
		int N = size();
		while(2*k <= N)
		{
			int j = 2 * k;
			if( j < N && !compare(j,j+1) )
				++j;
			if( compare(k, j))
				break;
			exch( k, j );
			k = j;
		}
	}

	bool compare( int i, int j )
	{
		return Comp()(data[i], data[j]);
	}

	void exch( int i, int j )
	{
		T t = data[i];
		data[i] = data[j];
		data[j] = t;
	}



private:
	std::vector<T> data; //data[0]不用
};


































