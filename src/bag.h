#pragma once

template<class N, class V> 
class ListIterator
{
public:
	ListIterator(N* node) : _node(node){}
	bool operator != (const ListIterator& other) const
	{
		return _node != other._node;
	}  

	V operator*() const
	{
		return _node->item;
	}

	const ListIterator& operator++()
	{
		_node = _node->next;
		return *this;
	}

private:
	const N* _node;	
};



template <class T>
class Bag
{
private:
	struct Node
	{
		T item;
		Node* next;
	};

	Node* first;	

public:
	typedef T value_type;
	typedef ListIterator<Node,T> iterator;

	Bag() : first( nullptr )
	{

	}

	~Bag()
	{
		Node* it = first;
		while( it != nullptr )
		{
			Node* t = it;
			it = it->next;
			delete t;
		}
	}

	void add( const T& item )
	{
		Node* oldFirst = first;
		first = new Node();
		first->item = item;
		first->next = oldFirst;	
	}

	ListIterator<Node, T> begin() const
	{
		return ListIterator<Node, T>( first );
	}

	ListIterator<Node, T> end() const
	{
		return ListIterator<Node, T>( nullptr );
	}

};



