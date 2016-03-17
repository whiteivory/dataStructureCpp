#pragma once

template <typename T> 
ListNodePosi(T) List<T>::find ( T const& e, int n, ListNodePosi(T) p ) const {
   while ( 0 < n-- ) 
      if ( e == ( p = p->pred )->data ) return p; 
   return NULL; 
} 

template <typename T>
ListNodePosi(T) List<T>::search ( const T& e, int n, ListNodePosi(T) p ) const { //从后往前
	assert( n <= size && valid(p) );
	while ( n-- > 0 ){
		if (( p = p->pred )->value <= e ) {
		return p;}
	}
	return p;//当 n==0 或者 查找到最前的时候
}
