#pragma once
//todo:attach函数

#include<assert.h>
#include<iostream>
#include"Stack.h"
#include<queue>
#include"util\Print.h"
#include<string>
#include<sstream>
#include<vector>
using namespace std;
template<typename T>
struct BinNode
{
	int m_height;
	T m_value;
	BinNode<T>* plchild;
	BinNode<T>* prchild;
	BinNode<T>* pparent;
	BinNode(T _value, BinNode* _plchild=nullptr, BinNode* _prchild=nullptr,BinNode* _pparrent=nullptr,int _height = 1) :m_value(_value), plchild(_plchild), prchild(_prchild),pparent(_pparrent),m_height(_height){}
	void print(ostream&os)const{ os << m_value << " "; }
	bool isLeaf(){ return plchild == nullptr&& prchild == nullptr; }
};
template<typename T>
ostream& operator << (ostream& os, const BinNode<T>& bi){
	bi.print(os);
	return os;
}

template <typename T>
class BinTree
{
private:
	BinNode<T>* m_head;
	template<typename VST> void PreOrderTrav(BinNode<T>* pnode, VST& vst);
	//void PreOrderTrav(BinNode* pnode,(template<typename T> void (*pfunc)(T value)))const; 不能这么写typename不能加template
	void MidOrderTrav(BinNode<T>* pnode)const;
public:
	BinTree(){m_head = nullptr; }

	BinTree(const string& _str);
	BinNode<T>* head()const{ assert(m_head != nullptr); return m_head; }
	int height()const { return m_head->m_height; }
	template <typename VST> void PreOrderTrav(VST& vst) { PreOrderTrav(head(),vst ); }
	void PreOrderTrav_2()const;
	void MidOrderTrav()const{ MidOrderTrav(head()); }
	BinNode<T>* insertAsRoot(const T& _value){ m_head = new BinNode<T>(_value); return m_head; }
	BinNode<T>* insertAsLeft(const T& _value, BinNode<T>* _pnode);
	BinNode<T>* insertAsRight(const T& _value,BinNode<T>* _pnode);

	void attachAsLeft(BinNode<T>* hook, BinNode<T>* hanger);
	void attachAsRight(BinNode<T>* hook, BinNode<T>* hanger);

};

//1 2 ^ 3 ^ ^
//要求重载stringstream >>
template<typename T>
BinTree<T>::BinTree(const string& _str){
}

template<typename T>
struct BTQueueNode
{
	BTQueueNode(BinNode<T>* _bi, int _n) :bi(_bi), n(_n){};
	BinNode<T>* bi;
	int n;
};

template<typename T>
ostream& operator << (ostream& os, const BinTree<T>& bi){
	BinNode<T>** v=new BinNode<T>*[pow(2, (bi.height()+1)) - 1];
	for (int i = 0; i < pow(2, (bi.height() + 1)) - 1; i++) v[i] = nullptr;
	queue<BTQueueNode<T>* > qu;
	BTQueueNode<T>* qnode = new BTQueueNode<T>(bi.head(), 0);
	qu.push(qnode);
	v[0] = qnode->bi;

	while (!qu.empty())
	{
		BTQueueNode<T>* curQnode = qu.front();
		qu.pop();
		v[curQnode->n * 2 + 1] = curQnode->bi->plchild;
		v[curQnode->n * 2 + 2] = curQnode->bi->prchild;
		if (curQnode->bi->plchild != nullptr)
			qu.push(new BTQueueNode<T>(curQnode->bi->plchild, curQnode->n * 2 + 1));
		if (curQnode->bi->prchild != nullptr)
			qu.push(new BTQueueNode<T>(curQnode->bi->prchild, curQnode->n * 2 + 2));
		delete curQnode;
	}

	for (int j = 0; j < pow(2, (bi.height())) - 1; j++)
	{
		if (v[j] != nullptr){
			cout << *v[j] << " ";
		}
		else
			cout << "^ ";
	}

	delete[] v;
	return os;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsLeft(const T& _value,BinNode<T>* _pnode){
	assert(_pnode->plchild == nullptr);
	_pnode->plchild = new BinNode<T>(_value, nullptr, nullptr, _pnode);
	BinNode<T>* p = _pnode;
	while (p!= nullptr)
	{
		p->m_height++;
		p = p->pparent;
	}
	return _pnode->plchild;
}
template <typename T>
BinNode<T>* BinTree<T>::insertAsRight(const T& _value,BinNode<T>* _pnode){
	assert(_pnode->prchild == nullptr);
	_pnode->prchild = new BinNode<T>(_value,nullptr,nullptr,_pnode);
	BinNode<T>* p = _pnode;
	while (p != nullptr)
	{
		p->m_height++;
		p = p->pparent;
	}
	return _pnode->prchild;
}

template<typename T>  //注意：这里的双template
template<typename VST>
void BinTree<T>::PreOrderTrav(BinNode<T>* pnode, VST& vst){
	if (pnode != nullptr){
		vst(pnode->m_value);
		PreOrderTrav(pnode->plchild,vst);
		PreOrderTrav(pnode->prchild,vst);
	}
}
template<typename T>
void  BinTree<T>::attachAsLeft(BinNode<T>* hook, BinNode<T>* hanger){
	assert(hook != nullptr&&hanger != nullptr);
	hook->plchild = hanger;
}
template<typename T>
void  BinTree<T>::attachAsRight(BinNode<T>* hook, BinNode<T>* hanger){
	assert(hook != nullptr&&hanger != nullptr);
	hook->prchild = hanger;
}