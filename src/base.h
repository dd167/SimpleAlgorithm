#pragma once

#include <stdio.h>
#include <random>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <functional>
#include <assert.h>

typedef int int32;
typedef unsigned int uint32;
typedef short int16;
typedef unsigned short uint16;
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned char byte;


template<class T1, class T2>
inline void swap(T1& a, T2& b)
{
	T1 c(a);
	a = b;
	b = c;
}

template <class T>
inline const T& min( const T& a, const T& b )
{
	return a < b ? a : b;
}

template <class T>
inline const T& max( const T& a, const T& b )
{
	return a < b ? b : a;
}

template <class T>
inline T abs( const T& a )
{
	return a < (T)0 ? -a  : a;
}

template <class T>
inline const T clamp( const T& value, const T& low, const T& high )
{
	return min( max( value, low ), high );
}


inline int random(int min, int max)
{
	//int range = abs(max-min);
	//return (rand()*rand())%(range+1) + (min > max ? max : min);
	std::default_random_engine e;
	std::uniform_int_distribution<int> u(min,max);
	return u(e); 
}


template< class T>
class Comparable
{
public:
	virtual int compareTo(const T& that) = 0;
	virtual ~Comparable() = default;
};



std::string format(const char* _format, ...)
{
	va_list argptr;
	va_start( argptr, _format );
	int count = snprintf(NULL, 0, _format, argptr );
	va_end( argptr );

	va_start(argptr, _format);
	char* buf = (char*)malloc(count* sizeof(char));
	snprintf( buf,  count, _format, argptr);
	va_end( argptr );

	std::string str( buf, count );
	free( buf );
	return str;
}




