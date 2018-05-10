#pragma once
#include "base.h"
#include <vector>

//数组实现的基于堆的优先队列（完全二叉树）
//性能分析：插入操作比较次数不超过lgN+1， 删除顶部元素比较次数不超过2lgN
//用途：适用于一个需要输入N个（非常大）数据，找出其中最大（或最小）的M个数据的场合。
//用堆实现的优先队列在现代应用程序中越来越重要，因为它能在插入操作和删除最大元素操作的混合
//场合中保证对数级别的运行时间。



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

	T pop()
	{
		T ret = data[1];
		data[1] = data[ data.size() -1 ];
		data.pop_back();
		sink( 1 );
		return ret;
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





/*
	索引优先队列数组实现
*/


template<class T, class Comp = std::less<T> >
class IndexPQ
{
public:
	IndexPQ( int maxN ) 
	{
		_N = 0;
		_items = new T[ maxN + 1  ];
		_pq = new int[ maxN + 1 ];
		_qp = new int[ maxN + 1 ];
		for( int i = 0; i <= maxN; ++i )
			_qp[i] = -1;
	}

	~IndexPQ() = default;

	bool empty()
	{
		return _N == 0;
	}

	int size()
	{
		return _N;
	}

	//插入一个元素，将他和索引k关联
	void push(int k, const T& item)
	{
		_N++;
		_qp[k] = _N;
		_pq[_N] = k;
		_items[k] = item;
		swim(_N);
	}

	//将索引为K的元素设为item
	void changes( int k, const T& item )
	{
		if( !contains(k) )
		{
			//std::cerr << "[IndexPQ.changes] not contain key=" << k << std::endl;
			return;
		}

		_items[k] = item;
		swim(_qp[k]);
		sink(_qp[k]);
	}

	//是否存在索引为k的元素
	bool contains(int k)
	{
		return _qp[k] != -1;
	}

	//返回堆顶元素
	const T& top()
	{
		return _items[_pq[1]];
	}

	//返回堆顶索引
	int topIndex()
	{
		return _pq[1];
	}

	//删除堆顶元素
	T pop()
	{
		int minKey = _pq[1];
		T ret = _items[minKey];
		exch( 1, _N-- );
		sink( 1 );
		
		assert( _pq[_N+1] == minKey );

		_qp[minKey] = -1; //delete
		_items[minKey] = T(); //
		_pq[_N+1] = -1;	 //delete
		return ret;
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
		return Comp()(_items[_pq[i]], _items[_pq[j]]);
	}

	void exch( int i, int j )
	{
		int swap = _pq[i];
		_pq[i] = _pq[j];
		_pq[j] = swap;

		_qp[_pq[i]] = i;
		_qp[_pq[j]] = j;
	}

private:
	int  _N; 		//元素数量
	T*	 _items; 	//元素数组
	int* _pq;       //索引二叉堆，从1开始, 即从数组下标->绑点索引
	int* _qp;		//逆序：_qp[_pq[i]] = _pq[_qp[i]] = i， 即从绑定索引->数组下标
};


























