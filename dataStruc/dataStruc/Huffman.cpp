#include "Huffman.h"
#include<stdio.h>
#include<exception>
#include"Bitmap.h"
#include<fstream>
Huffman::Huffman(const string& trainFilePath)
{
	//下面的这些也可以放在初始化列表里面
	m_pqueue.reset(new priority_queue < shared_ptr<BinTree<HuffNode> >, vector<shared_ptr<BinTree<HuffNode> > >, cmp > ());
	m_phufftree.reset(new BinTree<HuffNode>());
	m_pmap.reset(new unordered_map<char, std::string>());

	memset(freq, 0, sizeof(int)*(0x80 - 0x20));
	FILE* fp = fopen(trainFilePath.c_str(), "r");
	char curc;
	while (fscanf(fp, "%c", &curc) != EOF){
		if ((curc - 0x20) > 0){
			freq[curc - 0x20] ++;
		}
	}
	fclose(fp);

	generateTrees();
	generateTree();
	generateTable();
	
}

void Huffman::generateTrees(){
	for (int i = 0; i < (0x80 - 0x20); i++){
		shared_ptr<BinTree<HuffNode> > p(new BinTree<HuffNode>());
		p->insertAsRoot(HuffNode(char(i + 0x20),freq[i]));
		m_pqueue->push(p);
		
	}
}
void Huffman::generateTree(){
	if (m_pqueue->empty()||m_pqueue->size()==1) return;
	while (m_pqueue->size()>1)
	{
		shared_ptr<BinTree<HuffNode> > l = m_pqueue->top();
		m_pqueue->pop();
		shared_ptr<BinTree<HuffNode> > r = m_pqueue->top();
		m_pqueue->pop();
		shared_ptr<BinTree<HuffNode> > n(new BinTree<HuffNode>());
		n->insertAsRoot(HuffNode('^', l->head()->m_value.weight + r->head()->m_value.weight));
		n->attachAsLeft(n->head(), l.get()->head());
		n->attachAsRight(n->head(), r.get()->head());
		m_pqueue->push(n);
	}
	m_phufftree = m_pqueue->top();
	m_pqueue->pop();
}
void Huffman::generateTable(){
	if (m_phufftree.get() == nullptr) return;
	Bitmap bm;
	generateTable(m_phufftree->head(),bm , 0);
}
void Huffman::generateTable(BinNode<HuffNode>* node, Bitmap& bm,int length){
	if (node->isLeaf()){
		m_pmap->insert(make_pair(node->m_value.cdata, bm.toString(length)));
		return;
	}
	//assert(node->plchild != nullptr);
	generateTable(node->plchild, bm.clear(length), length + 1);
	generateTable(node->prchild, bm.set(length), length + 1);
}
Huffman::~Huffman()
{
	//delete[] freq; 这不需要delete，因为不是动态分配的。
}

bool operator< ( shared_ptr<BinTree<HuffNode> > lhs,shared_ptr<BinTree<HuffNode> > rhs){
	return lhs->head()->m_value.weight < rhs->head()->m_value.weight;
}

void Huffman::encode(const string& filePath, Bitmap& bm){
	ifstream ifs(filePath.c_str());
	string line;
	int cur=0;
	while (getline(ifs,line))
	{
		for (int i = 0; i < line.length(); i++){
			string bitmstr = m_pmap->find(line[i])->second;
			for (int j = 0; j < bitmstr.length(); j++){
				if (bitmstr[j] == '0')
					bm.clear(cur);
				else bm.set(cur);
				cur++;
			}
		}
	}
	ifs.close();
}
void  Huffman::decode(Bitmap& bm, const string& outFilePath){
	
}