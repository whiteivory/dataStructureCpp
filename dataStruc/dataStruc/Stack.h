#pragma once
#include<vector>
using namespace std;

template<typename T>
class Stack{
private:
	vector<int>* m_v;
public:
	int size()const{ return m_v.size(); }
public:
	Stack<T>(){ m_v = new vector<T>(); }
	~Stack<T>(){ delete m_v; }
	void pop(){ if (!m_v->empty()) m_v->pop_back(); }
	T back()const{ if (!m_v->empty()) return m_v->back(); }
	void push(const T& _value){ m_v->push_back(_value); }
};