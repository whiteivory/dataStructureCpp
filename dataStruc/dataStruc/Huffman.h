#pragma once

//@Todo:table改成bitmap，更有效率，这要求bitmap实现operator+,数据量更大时可以考虑存文件。
#include"BinTree.h"
#include"Bitmap.h"
#include<unordered_map>
#include<queue>
#include<memory>
using namespace std;
struct HuffNode
{
	char cdata;
	int weight;
	HuffNode(char _cdata, int _weight) : cdata(_cdata), weight(_weight){};
};
//重载
bool operator< (const shared_ptr<BinTree<HuffNode> > lhs, const shared_ptr<BinTree<HuffNode> >  rhs);
//因为shared_ptr并没有定义这个operator，所以不能像下面这么写
//bool shared_ptr<shared_ptr<BinTree<HuffNode> >::operator<

class cmp{
public:
	bool operator()(const shared_ptr<BinTree<HuffNode> > &lhs, const shared_ptr<BinTree<HuffNode> > &rhs){
		//return !(lhs < rhs); 这么写是不对的
		//if (lhs->head()->m_value.weight == lhs->head()->m_value.weight) return false;
		//if (lhs->head()->m_value.weight < lhs->head()->m_value.weight) return true;
		//return false;
		if (lhs->head()->m_value.weight == rhs->head()->m_value.weight) return false;
		return !(lhs < rhs);
	}
};

class Huffman
{
public:
	Huffman(const string& trainFilePath);
	~Huffman();
	void encode(const string& filePath,Bitmap& bm);
	void decode(Bitmap& bm,const string& outFilePath);
private:

	void generateTrees();
	void generateTree();
	void generateTable();

private:
	void generateTable(BinNode<HuffNode>* node, Bitmap& bm,int length);

private:
	shared_ptr<BinTree<HuffNode> > m_phufftree;
	shared_ptr<priority_queue<shared_ptr<BinTree<HuffNode> >,vector<shared_ptr<BinTree<HuffNode> > >,cmp > > m_pqueue;
	shared_ptr<unordered_map<char, std::string> > m_pmap;
	int freq[0x80 - 0x20];
};


void test{
	Huffman hmt("train.txt");
	Bitmap bm;
	hmt.encode("a.txt", bm);
	cout << bm.toString(bm.getAva());
}