#include"head.h"
const int MaxGraphSize = 100;
const int MaxWeight = 100;
const int Max = 100000;
class Graph {
private:
	int Edge[MaxGraphSize][MaxGraphSize];
	int path[MaxGraphSize][MaxGraphSize];
	int GraphSize;
public:
	Graph();
	virtual ~Graph();
	int GraphEmpty();
	int GraphFull();
	int NuberOfVertices();
	int NuberOfEdge();
	int GetWight(const int &v1, const int &v2);
	int &GetNeighbors(int &v);
	int GetFirstNeighbor(const int v);
	void InsertVertex(const int&v);
	void InsertEdge(int v1, int v2);
	void DeleteVertex(int v);
	void DeleteEdge(int v1, int v2);
	//采用递归的算法从顶点表的第一个顶点开始对图进行深度优先的搜素。
	void DepthFirstSerach();
	//采用迭代的方法从指定的顶点v开始进行图的深度优先搜索
	void DFS(int v);
	//从顶点v开始进行图的广度优先遍历
	void BFS(int v);
	//输出图的拓扑结构
	void TopoOrder();
	//输出图的关键路径
	void CriticalPath();
	//在非权图中求指定定点到达其他所有顶点的最短路径
	void ShortestPath(int v);

	/*
	*
	*  连通图的最小生成树通常不是唯一的，但是最小生成树边上的权值之和是唯一的。
	*  最小生成树的构造方法有Prim算法和Kruskal算法
	*
	*/
	//构造最小之支撑树的普里姆算法
	void Prim();

	/*
	*
	*  最短路径的问题分为两种：
	*              1. 求从某一个顶点出发到其余各点的最短距离  Dijkstra算法
	*              2. 求图中每对顶点之间的最短距离       Floyd算法
	*
	*/
	//求任意两点之间的最短距离
	void  Floyd();



};
/*
*
*  求图中任意两点之间的最短路径
*  其中Eage[n][n]是有两个顶点的图的邻接矩阵；A[i][j]是顶点Vi到Vj的最短路径长度
*  Path[i][j]是相应路径上顶点j的前一个顶点的序号。
*
*/
void Graph::Floyd() {
	int n = GraphSize;
	int **path = new int*[n];
	int **A = new int*[n];
	for (int i = 0; i < n; i++) {
		path[i] = new int[n];
		A[i] = new int[n];
	}
	//初始化矩阵A和path
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			A[i][j] = Edge[i][j];
			if (i != j&&A[i][j] < Max)
				path[i][j] = i;
			else
				path[i][j] = -1;

		}
	//从A^-1开始构造A^(n-1)
	for (int k = 0; k<n; k++)
		for (int i = 0; i<n; i++)
			for (int j = 0; j < n; j++)
				if (j != k&&j != i&&A[i][k] < Max&&A[i][k] + A[k][j] < A[i][j]) {
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[k][j];
				}
	for (int i = 0; i < n; i++) {
		delete[]path[i];
		delete[]A[i];
	}
	delete[]path;
	delete[]A;
}

//最小支撑树的普里姆算法
void Graph::Prim() {
	int n = GraphSize;
	struct LV
	{
		int LowCost;
		int Vex;

	}*clouseEdge = new LV[n];
	struct EdgeCost {
		int head;
		int tail;
		int cost;
	}*TE = new EdgeCost[n];
	//初始化邻接矩阵
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (Edge[i][j] == 0)
				//Max为预定义的常数
				Edge[i][j] = Max;
		}
	//以顶点0为初始顶点，初始化数组closeEdge
	for (int i = 0; i < n; i++)
	{
		clouseEdge[i].LowCost = Edge[0][i];
		clouseEdge[i].Vex = 0;
	}
	//顶点0进入集合U
	clouseEdge[0].Vex = -1;
	//支撑树的边计算器count
	int count = 0;
	//循环n-1次
	for (int i = 1; i < n; i++) {
		//设置最小值
		int min = Max + 1;
		int v = 0;
		//求当前权值最小的边和该边的终点v
		for (int j = 0; j < n; j++)
			if (clouseEdge[j].Vex != -1 && clouseEdge[j].LowCost < min) {
				v = j;
				min = clouseEdge[j].LowCost;
			}
		//若v==0说明没有找到符合条件的顶点
		if (v != 0) {
			//向支撑树中的边集合TE中添加一条边
			TE[count].head = clouseEdge[v].Vex;
			TE[count].tail = v;
			TE[count].cost = clouseEdge[v].LowCost;
			//计数器加一
			count++;
			//修改域值
			clouseEdge[v].LowCost = 0;
			//顶点进入集合U
			clouseEdge[v].Vex = -1;
			//因为v的计入需要修改某些值
			for (int j = 0; i<n; i++)
				if (clouseEdge[j].Vex != -1 && Edge[v][j] < clouseEdge[j].LowCost) {
					clouseEdge[j].LowCost = Edge[v][j];
					clouseEdge[j].Vex = v;
				}
		}
	}
	for (int i = 0; i < n; i++)
		cout << "(" << TE[i].head << "," << TE[i].tail << "," << TE[i].cost << ")" << endl;
	delete[]clouseEdge;
	delete[]TE;
}