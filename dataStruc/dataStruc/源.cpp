#include<iostream>
#include"BinTree.h"
#include"Stack.h"
#include<string>
#include"util\Print.h"
#include"Bitmap.h"
#include"Huffman.h"
using namespace std;

void foo(){


}
class B{
public:
	int b;
	B(){ b = 2; }
};
class A{
public:
	A(){
		pb.reset(new B());
	}

	shared_ptr<B> pb;
};
void main(){
	Huffman hmt("train.txt");
	Bitmap bm;
	hmt.encode("a.txt", bm);
	cout << bm.toString(bm.getAva());
}