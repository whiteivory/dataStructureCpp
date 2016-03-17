#pragma once
template <typename T>
bool List<T>::valid( ListNodePosi(T) p ){
	return p&&p!=header&&p!=tailer;
}
