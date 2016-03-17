//注意成员变量和函数不能重名
#pragma once
#include"listnode.h"
#include<assert.h>
using namespace std;

template < typename T >
class List{
private:
	int _size; ListNodePosi(T) header;
	ListNodePosi(T) tailer;
protected:
	void copyNodes ( ListNodePosi(T) p ,int n );
	void init ();
	void clear ();
	void merge ( ListNodePosi(T) p, int n, ListNodePosi(T) q, int m);
	void mergeSort ( ListNodePosi(T) p, int n);
	void selectionSort ( ListNodePosi(T) p, int n);
	void insertionSort ( ListNodePosi(T) p, int n);
public: 
	//构造函数
	List () { init(); }
	List (const List& l, int k, int n );   //这样子应该编译不能通过，因为两个int类型是一样的
	List (const List& l, int n ) { int k = 0; List(l,k,n); }
	List (const List& l) { int n = l.size(); List(l,n);}
	T& operator[] (int r) const; //还是不是很清楚这里为什么要声明成const然后返回引用
	//析构函数
	~List();
	//只读
	int size() const { return _size; }
	bool empty() const { return _size == 0; }
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return tailer->pred; }
	ListNodePosi(T) find ( const T& e) const { return find ( e, _size, tailer );}
	ListNodePosi(T) find ( const T& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search ( const T&e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search ( const T&e ) const { return search ( e, _size, tailer);}
	ListNodePosi(T) selectMax (ListNodePosi(T) p, int n) const;
	ListNodePosi(T) selectMax () const { return selectMax(header->succ,_size); }//[fisrt,last) 所以header->succ
	//可写
	ListNodePosi(T) insertAsFirst(const T&e) { return insertAsB(header->succ,e);} //注意 const& T
	ListNodePosi(T) insertAsLast ( const T& e) { return insertAsA ( tailer->pred, e); }
	ListNodePosi(T) insertAsA ( ListNodePosi(T) p, const T& e);
	ListNodePosi(T) insertAsB ( ListNodePosi(T) p, const T& e);
	void sort() { sort ( first(), _size ); }
	void sort ( ListNodePosi(T) p , int n );
	int remove ( ListNodePosi(T) p );
	int deduplicate(); //无序去重复
	int uniquify();//
	void reverse();
	//遍历
	void traverse ( void (*) ( T& ) ); //no const here

	//other
	bool valid ( ListNodePosi(T) p );
};
#include"list_implementaion.h"
