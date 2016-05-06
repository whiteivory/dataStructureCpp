#pragma once
#include<memory.h>
#include<iostream>
#include<string>
using namespace std;
class Bitmap
{
public:
	Bitmap(int n = 8){ init(n); avalleng = 0; }
	~Bitmap(){ delete[] M; M = NULL; }
	int getAva() const { return avalleng; }
	Bitmap& set(int k){ 
		expand(k);
		if (avalleng < k) avalleng = k;
		M[k >> 3] |= (0x80 >> (k & 0x07)); return *this; }
	Bitmap& clear(int k){ 
		expand(k);
		if (k > avalleng) avalleng = k;
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
		return *this; }
	bool test(int k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); }
	std::string toString() { return toString(avalleng); }
	std::string toString(int length ){
		char* tmp = new char[length + 1];//'\0'
		for (int i = 0; i < length; i++){
			tmp[i] = test(i) ? '1' : '0';
		}
		tmp[length] = '\0';
		std::string ret(tmp);
		delete tmp;
		return ret;
	}
	void print(int length){ 
		for (int i = 0; i < length; i++){
			test(i) ? std::cout << "1 " : std::cout << "0 ";
		}
	}
	void dump(const string& outFilePath){
		//ofstream ofs(outFilePath.c_str(), ios::trunc);

	}
private:
	void init(int n){
		N = (n + 7) / 8;
		M = new char[N];
		memset(M, 0, N);
	}
	void expand(int k){
		if (8 * N>k) return;
			int oldN = N;
			char* oldM = M;
			init(2 * k);
			memcpy_s(M, N, oldM, oldN);
			delete[] oldM;
	}
	int N;
	char* M;
	int avalleng;
};

