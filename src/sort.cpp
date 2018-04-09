#include <iostream>
#include "base.h"
#include "clock.h"


//算法步骤：每次取一个数，插入左边有序的数组
//算法时间复杂度：
//最好情况：N (数组基本有序时)
//平均情况: N*N
//最差情况: N*N
void insert_sort( int* a, int size )
{
	for( int i = 1;  i < size; ++i )
	{
		int j = i;
		int curValue = a[i];
		while( j > 0 && curValue < a[j-1] )
			--j;

		if( j != i )
		{
			//性能点：数组后移
 			for( int k = i; k > j; --k )
			{
				a[k] = a[k-1];
			}
			a[j] =curValue;
		}
	}
}

void bubble_sort( int* a, int size )
{

}


void merge_sort( int* a, int size )
{

}


void quick_sort2( int* a, int size )
{

}


void quick_sort3( int* a, int size )
{

}

bool check_result( int*a, int size )
{
	for( int i = 1; i < size; ++i )
	{
		if(a[i] < a[i-1])
			return false;
	}
	return true;
}



int main( int argc, char* argv[])
{
	Clock c;

	int size = 100000;
	if( argc > 1 )
	{
		size = atoi(argv[1]);
	}
	std::cout << "number size=" << size << std::endl;

	int* a = new int[size];
	for( int i = 0; i < size; ++i )
	{
		a[i] = random(0,size);
	}
	int* acopy = new int[size];

	{
		memcpy( acopy, a, sizeof(int)*size );
		c.start();
		insert_sort( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "insert sort cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "insert sort wrong!" << std::endl;
		}		
	}


	{
		memcpy( acopy, a, sizeof(int)*size );
		c.start();
		bubble_sort( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "bubble sort cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "bubble sort wrong!" << std::endl;
		}		
	}	


	{
		memcpy( acopy, a, sizeof(int)*size );
		c.start();
		merge_sort( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "merge sort cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "merge sort wrong!" << std::endl;
		}		
	}	


	{
		memcpy( acopy, a, sizeof(int)*size );
		c.start();
		quick_sort2( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "quick sort2 cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "quick sort2 wrong!" << std::endl;
		}		
	}	


	{
		memcpy( acopy, a, sizeof(int)*size );
		c.start();
		quick_sort3( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "quick sort3 cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "quick sort3 wrong!" << std::endl;
		}		
	}	

	delete [] a;
	delete [] acopy;
	return 0;
}