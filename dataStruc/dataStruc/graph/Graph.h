#pragma once
//todo tocheck notconsideredyet note

#include<iostream>
#include<limits>
using namespace std;

typedef enum{DISCOVERED,UNDISCOVERED,VISITED}VStatus;
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD}EStatus;

template<typename Tv>
struct Vertex
{
	Tv data;
	int inDegree, outDegree;
	int parent; //对TSort有用，可以找到遍历路径
	VStatus status;
	int priority;
	int dTime;
	Vertex(const Tv&_data) :data(_data), inDegree(0), outDegree(0), parent(-1),
		status(UNDISCOVERED), priority(-1), dTime(0){}
	
};
template<typename Te>
struct Edge
{
	Te data;
	EStatus status;
	int weight;
	Edge(const Te& _data) : data(_data), status(UNDETERMINED), weight(numeric_limits < int > ::max()){}
};

template<typename Tv,typename Te>
class Graph
{
public:
	Graph();
	virtual ~Graph();
	virtual int firstNbr(int i) = 0;
	virtual int nextNbr(int i, int j) = 0;

	virtual int& dTime(int i) = 0; //@note 之所以这里都要进行一下封装是为了有可能Vertex或者Edge也有可能改变，要以接口来进行控制翻转。
	virtual int& fTime(int i) = 0;
	virtual VStatus& statusV(int i) = 0;
	virtual EStatus& statusE(int i, int j) = 0;
	virtual Tv VertexValue(int i) = 0;


	
	virtual int insertV(const Tv& value) = 0;
	virtual int insertE(int i, int j, const Te& value) = 0;
public:
	template<typename VST> void BFS(int i, VST vst);
	template<typename VST> void DFS(int i, VST vst);

public:
	template<typename VST> void BFS(int i, int& clock,VST vst);
	template<typename VST> void DFS(int i, int& clock,VST vst);

private:
	int n;
};


template<typename Tv, typename Te>
Graph<Tv, Te>::Graph()
{
	
}
template<typename Tv, typename Te>
Graph<Tv, Te>::~Graph()
{
}

template<typename Tv, typename Te>
template<typename VST> void Graph<Tv, Te>::BFS(int i, VST vst){

}

template<typename Tv, typename Te>
template<typename VST> void Graph<Tv,Te>::DFS(int i, VST vst){
	int start = i;
	do{
		if (statusV(i) != UNDISCOVERED){
			DFS(i, 0, vst);
		}
	} while ((i = (++i) % n) != start);
}

template<typename Tv, typename Te>
template<typename VST> void Graph<Tv, Te>::BFS(int i, int& clock, VST vst){
	
}

template<typename Tv, typename Te>
template<typename VST> void Graph<Tv, Te>::DFS(int i, int& clock, VST vst){
	template<typename Tv, typename Te>
	template<typename VST> void Graph<Tv, Te>::DFS(int i, int& clock, VST vst){
		dTime(i) = clock;
		vst(VertexValue(i));

		for (int j = firstNbr(i); j != -1; j = nextNbr(i, j)){  //@NotConsidered j!= -1
			if (statusV(j) == UNDISCOVERED){
				statusV(j) = DISCOVERED;
				DFS(j, ++clock, vst);
			}
			else if (statusV(j) == DISCOVERED){
				statusE(i, j) = BACKWARD;
				return;
			}
			else if (statusV(j) == VISITED){
				if (dTime(i) < dTime(j))
					statusE(i, j) = FORWARD;
				else
					statusE(i, j) = CROSS;
			}
		}
		statusV(i) = VISITED;
		fTime(i) = ++clock;
	}
}
