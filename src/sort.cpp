#include <iostream>
#include "base.h"
#include "clock.h"


inline void exch( int* a, int i, int j )
{
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}


/*选择排序
算法步骤：在剩余数组中找到最小的数，放到左边有序部分的队尾
性能分析：需要～N*N/2次比较, N次交换， 比较次数恒定， 交换次数恒定
是否稳定：否 ?   
是否是原地排序：是
时间复杂度：N*N
空间复杂度: 1
结论：每次循环只能找出1个最小的元素，成本很高，尤其对于已经有序的数组，还需要做这些固定的无用功。
用途：很少有上场机会
*/
void select_sort( int* a, int size )
{
	for( int i = 0; i < size; ++i )
	{
		int minIndex = i;
		for( int j = i + 1; j < size; ++j )
		{
			if( a[j] < a[minIndex] )
				minIndex = j;
		}
		exch( a, i, minIndex );
	}
}


/*插入排序
算法步骤：每次取一个数，插入左边有序的数组
性能分析：对于随机排列且长度为N且主键不重复的数组：
平均情况: ~N*N/4次比较， ~N*N/4次交换
最好情况（顺序）：N-1次比较, 0次交换
最坏情况（逆序）：~N*N/2次比较， ~N*N/2次交换
是否稳定：是
是否原地排序：是
时间复杂度：介于N~N*N之间
空间复杂度: 1
用途：对于基本有序的数组或小规模数组，插入排序十分高效
*/
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
			a[j] = curValue;
		}
	}
}

/*冒泡排序
算法描述: 在剩余元素中，从一个方向往另一个方向按照顺序两两交换，即每一轮把最大或最小的元素沉到剩余数组尾部
性能分析:比较次数 ~N*N/2, 交换次数过多
是否稳定：否
是否原地：是
时间复杂度：~N*N
空间复杂度：1
用途：冒泡排序在随机情况下可能是最慢的算法，但是由于可以检测出当前已经有序而迅速break，所以在基本有序的情况下有一定的出场机会
*/
void bubble_sort( int* a, int size )
{
	bool changed;
	for( int i = 0; i < size; ++i )
	{
		changed = false;
		for( int j = size-1; j > i; --j )
		{
			if( a[j] < a[j-1] )
			{
				exch(a, j, j-1);
				changed = true;
			}
		}

		if( !changed )
			break;
	}
}





void merge( int* a, int lo, int mid, int hi, int* aux)
{
	//将a[lo, mid]和a[mid+1, hi]归并
	int i = lo, j = mid+1;

	for( int k = lo; k <= hi; k++ )
		aux[k] = a[k];

	for( int k = lo; k <= hi; k++ )
	{
		if( i > mid )   		//左半边用尽， 取右半边元素
			a[k] = aux[j++];
		else if( j > hi )   	//右半边用尽，取左半边元素
			a[k] = aux[i++];
		else if( aux[j] < aux[i] )	
			a[k] = aux[j++];
		else
			a[k] = aux[i++];
	}
}

void merge_sort_internal( int* a, int lo, int hi, int* aux )
{
	if( hi <= lo )
		return;

	int mid = lo + (hi-lo)/2;
	merge_sort_internal( a, lo, mid, aux);
	merge_sort_internal( a, mid+1, hi, aux);
	merge( a, lo, mid, hi, aux);
}


/* 归并排序
算法步骤：先（递归地）将数组分成两半分别排序，然后将结果归并起来。分治思想的运用！
性能分析：可以认为归并排序在最好最坏平均情况下，其所需要的比较次数都是~N*logN(线性对数级别)
是否稳定：是
是否原地排序：否
时间复杂度：N*logN
空间复杂度: N
用途：如果稳定性很重要而空间又不是问题， 归并排序可能是最好的选择。
*/
void merge_sort( int* a, int size )
{
	//创建辅助数组
	int* aux = new int[size];
	merge_sort_internal( a, 0, size-1, aux);
	delete [] aux;
}






void quick_sort2_internal( int* a, int lo, int hi )
{
	if( hi <= lo )
		return;

	int left = lo, right = hi;
	int v = a[lo];


	while( left < right )
	{
		while(left < right && a[right] >= v )
			--right;

		a[left] = a[right]; //将第一个比v小的移到低端

		while( left < right && a[left] <= v )
			++left;

		a[right] = a[left]; //将第一个比v大的移到高端
	}
	a[left] = v;
	quick_sort2_internal( a, lo, left-1 );
	quick_sort2_internal( a, left+1, hi );

}

/*
算法步骤：和归并排序一样，使用分治的算法思想， 将数组分成两部分（递归），独立的排序。当每个子数组都有序时，整个数组也就有序了
性能分析：性能依赖于每次切分是否能正好将数组二等分。
是否稳定：否
是否原地排序：是
时间复杂度: N*logN
空间复杂度: lgN
用途：一般情况下都是最佳选择！
*/
void quick_sort2( int* a, int size )
{
	quick_sort2_internal( a, 0, size-1);
}






void quick_sort3_internal( int* a, int lo, int hi )
{
	if( hi <= lo )
		return;

	int lt = lo, i = lo+1, gt = hi;
	int v = a[lo];

	while( i <= gt )
	{
		if( a[i] < v )
			exch( a, lt++, i++);
		else if( a[i] > v)
			exch( a, i, gt--);
		else
			i++;
	}
	//现在 a[lo..lt+1] < v = a[lt..gt] < a[gt+1..hi]
	quick_sort3_internal( a, lo, lt -1 );
	quick_sort3_internal( a, gt+1, hi );
}

/*三向切分的快速排序：
改进两等分快速排序对于含有大量重复元素的性能损失，因为对于重复的中间元素，它们是不用参与接下来的递归调用。
*/
void quick_sort3( int* a, int size )
{
	quick_sort3_internal( a, 0, size -1 );
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

	int size = 10000;
	if( argc > 1 )
	{
		size = atoi(argv[1]);
	}
	std::cout << "number size=" << size << std::endl;

	int* a = new int[size];
	for( int i = 0; i < size; ++i )
	{
		a[i] = random(0,size/5);
	}
	int* acopy = new int[size];


	{
		memcpy( acopy, a, sizeof(int)*size );
		c.start();
		select_sort( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "select sort cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "insert sort wrong!" << std::endl;
		}		
	}	



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

		c.start();
		insert_sort( acopy, size );
		c.stop();	
		if( check_result(acopy, size) )
		{
			std::cout << "insert sort after sort cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "insert sort after sort wrong!" << std::endl;
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

		c.start();
		bubble_sort( acopy, size );
		c.stop();
		if( check_result(acopy, size) )
		{
			std::cout << "bubble sort after sort cost time: " << c.duration() << "s" << std::endl;
		}
		else
		{
			std::cout << "bubble sort after sort wrong!" << std::endl;
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