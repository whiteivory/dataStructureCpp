#pragma once

template <typename T> ListNodePosi(T) List<T>::insertAsA ( ListNodePosi(T) p, T const& e )
{  _size++; return p->insertAsSucc ( e );  } 

template <typename T> ListNodePosi(T) List<T>::insertAsB ( ListNodePosi(T) p, T const& e )
{  _size++; return p->insertAsPred ( e );  } 

template <typename T> 
ListNodePosi(T) ListNode<T>::insertAsPred ( T const& e ) {
   ListNodePosi(T) x = new ListNode ( e, pred, this ); 
   pred->succ = x; pred = x; 
   return x; 
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc ( const T& e) {
	ListNodePosi(T) x = new ListNode ( e, this, succ );
	succ->pred = x;
	succ = x;
	return x;
}

template < typename T >
void List<T>::insertionSort ( ListNodePosi(T) p, int n ) { //从p开始向后n个
	assert ( valid (p) );
	for (int i = 0; i < n; i++ ) {
		ListNodePosi(T) tmp = search (p->data,i);
		p->insertAsSucc( tmp->data );
		p = p->succ;
		remove(p->p);
	}
}
template < typename T >
int List<T>::remove ( ListNodePosi(T) p ) {
	assert ( valid (p) );
	int oldvalue = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	return oldvalue;
}
