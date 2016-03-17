
#pragma once

#define ListNodePosi(T) ListNode<T>*
typedef int Rank;

template <typename T>
struct ListNode {
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;
	T data;
	ListNode(T e = 0, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) 
		: data(e), pred(p), succ(s) {};
	ListNodePosi(T) insertAsPred ( const T& e ); //注意const &
	ListNodePosi(T) insertAsSucc ( const T& e ); 

};
