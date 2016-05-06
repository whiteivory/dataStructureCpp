#pragma once

template<typename T>
class Print{
public:
	 void operator() (T& e){
		cout << e << " ";
	}
};