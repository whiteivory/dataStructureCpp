#pragma once

template <typename T> void List<T>::init() { //列表初始化，在创建列表对象时统一调用
   header = new ListNode<T>; //创建头哨兵节点
   tailer = new ListNode<T>; //创建尾哨兵节点
   header->succ = tailer; header->pred = NULL;
   tailer->pred = header; tailer->succ = NULL;
   _size = 0; //记录规模
}

template < typename T >
void List<T>::copyNodes ( ListNodePosi(T) p , int n ) {
	assert ( valid(p) && n < p.size() );
	while ( n-- > 0 ) {
		insertAsFirst ( p->data );
		p = p->succ;
	}
}


template < typename T >
List<T>::~List() {
	clear();
	delete header;
	delete tailer;
}
template <typename T> 
List<T>::List ( List<T> const& L, int r, int n ) { copyNodes ( L[r], n ); }

template <typename T> void List<T>::clear() { //清空
   while ( 0 < _size ) remove ( header->succ ); //
}

template <typename T> //xiaolvdi
T& List<T>::operator[] ( int r ) const { //注意p->data并不是自己的成员变量，所以可以声明成const 
	assert( r >= 0 && r < _size );
    ListNodePosi(T) p = first(); 
    while ( 0 < r-- ) p = p->succ; 
    return p->data; 
}





