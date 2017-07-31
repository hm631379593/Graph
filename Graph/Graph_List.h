#pragma once
#include"head.h"
//边节点的结构体
struct Edge
{
	friend class Graph_List;
	int VerAdj;
	//邻接矩阵定点序号，从o开始进行编号
	int cost;
	//边的权重
	Edge*link;
	//指向下一条边节点的指针

};
//顶点表中节点的结构体
struct Vertex
{
	friend class Graph_List;
	int VerName;
	//节点的名字
	Edge*adjacent;
	//边链表的头指针
};



class Graph_List {
private:
	Vertex*Head;
	int GraphSize;
public:
	Graph_List();
	~Graph_List();
	int GraphEmpty();
	int GraphFull();
	int NuberOfVertices();
	int NuberOfEdge();
	int GetWight(const int &v1, const int &v2);
	int GetNeighbors(int &v);
	int GetFirstNeighbor(const int v);
	void InsertVertex(const int&v);
	void InsertEdge(int v1, int v2);
	void DeleteVertex(int v);
	int  GetNextNeighbor(int v1, int v2);
	void DeleteEdge(int v1, int v2);

	/*
	*
	* 一个给定的图的邻接矩阵表示是唯一的，但对于邻接表来说，如果边的输入
	* 先后的次序不一样，生成的邻接表表示也不一样。因此对于同样的一个图的
	* 给予邻接矩阵表示的遍历所得到的DFS序列或BFS序列是唯一的，基于邻接表
	* 表示的遍历得到的DFS序列或BFS序列可以是不唯一的。
	*
	*
	* 用广度优先搜索算法遍历图与深度优先搜索算法遍历图的唯一的区别是邻接点搜素次序不同，
	* 总的时间复杂度都一样
	*/

	//采用递归的算法从顶点表的第一个顶点开始对图进行深度优先的搜素。
	void DepthFirstSerach();
	//采用迭代的方法从指定的顶点v开始进行图的深度优先搜索
	void DFS(int v);
	//采用递归的方法从指定的顶点v开始进行图的深度优先搜索
	void RDFS(int v, int *visited);
	//从顶点v开始进行图的广度优先遍历
	void BFS(int v);
	//输出图的拓扑结构
	void TopoOrder();
	//输出图的关键路径
	void CriticalPath();
	//在非权图中求指定定点到达其他所有顶点的最短路径
	//无权单源路径
	void ShortestPath(int v);
	//正权单源路径的最短路径的Dijkstra算法
	void DshortestPath(int v);
	//求图中任意两点之间的最短路径使用邻接矩阵实现
	void AllLength();

	/*
	*
	*  连通图的最小生成树通常不是唯一的，但是最小生成树边上的权值之和是唯一的。
	*
	*/
	//构造最小之支撑树的普里姆算法
	void Prim();


};
/*
*
* 采用递归的算法从顶点表的第一个顶点开始对图进行深度优先的搜素。
*
*/
void Graph_List::DepthFirstSerach() {
	int *visited = new int[GraphSize];
	for (int k = 0; k < GraphSize; k++) {
		visited[k] = 0;
	}
	RDFS(0, visited);
	//从序号为0的定点出发，深度优先遍历图
	delete[]visited;
}
/*
*
* 采用递归的方法从指定的顶点v开始进行图的深度优先搜索
*
* 在遍历的时候每个顶点最多调用一次RDFS函数，因为一旦顶点元素被标记为已访问，
* 就不会从他出发进行搜索。因此遍历图的过程的实质上就是对每个顶点查找其邻接点的过程。
* 其耗费的时间则取决与所采取的数据结构。当使用二维数组的表示邻接矩阵的时候，查找每
* 个顶点的时间为0(N^2)，其中N为图的顶点数。而当使用邻接表的时候，找邻接点的所需的时间
* 为O(e)，其中e为无向图中的边数或者有向图中的弧数，由此，当以邻接表作为存储结构的时候
* 深度优先搜索遍历图的时间复杂程度为O(N+e)
*
*/
void Graph_List::RDFS(int v, int*visited) {
	cout << v << " ";
	//说明v已经被访问过
	visited[v] = 1;
	//取得第一个邻接顶点的序号
	int w = GetFirstNeighbor(v);
	//若存在节点w，从w递归访问
	while (w != -1) {
		if (!visited[w])
			RDFS(w, visited);
		//w为v关于w的下一个节点
		w = GetNextNeighbor(v, w);
	}
}


/*
*  
*  采用迭代的方法从指定的顶点v开始进行图的深度优先搜索
*
*/
void Graph_List::DFS(int v) {
	int *visited = new int[GraphSize];
	//数组的初始化
	for (int k = 0; k < GraphSize; k++) {
		visited[k] = 0;
	}
	stack<int> Stack;
	//将起始节点压入栈中，栈不为空的时候进行迭代
	Stack.push(v);
	int w;
	while (!Stack.empty()) {
		//弹出一个定点可以断定该节点没有被访问过
		w = Stack.top();
		Stack.pop();
		//设置该节点被访问过
		visited[w] = 1;
		cout << w << " ";
		//取得该节点的第一个邻接节点
		int k = GetFirstNeighbor(w);
		//当k没有邻接节点的时候k为-1
		while (k != -1)
		{
			//若k没有被访问过则压入栈中
			if (visited[k] == 0) {
				Stack.push(k);
			}
			k = GetNextNeighbor(w, k);
		}
	}
	delete[]visited;
}
/*
*
*  图的广度优先遍历的次序也是不唯一的
*
*  每个顶点最多一次进入队列。遍历图的过程实质就是通过边或弧找邻接点
*  的过程，因此广度优先搜索遍历图的时间和深度优先遍历相同，两者的不同
*  只在于访问顶点的次序不一样。
*/
void Graph_List::BFS(int s) {
	int* visited = new int[GraphSize];
	for (int k = 0; k < GraphSize; k++) {
		visited[k] = 0;
	}
	cout << s << " ";
	queue<int>Queue;
	Queue.push(s);
	while (!Queue.empty()) {
		int v = Queue.front();
		Queue.pop();
		int w = GetFirstNeighbor(v);
		while (w != -1) {
			if (!visited[w])
			{
				visited[w] = 1;
				cout << w << " ";
				Queue.push(w);
			}
			w = GetNextNeighbor(v, w);
		}

	}
	delete[]visited;
}
/*
*  
*  拓扑排序的基本步鄹：
*  1. 从AOV网中选择一个入度为0的顶点并输出该定点。
*  2. 从AOV网中删除该顶点机器所有的出边
*  3. 执行1，2直至所有的顶点都已经输出或者剩下的顶点入度均不为0，这说明网中存在回路，无法继续拓扑排序。
*  因此拓扑排序还可以用来判断有向图中是否存在回路。
*
*
*
*  假设使用邻接表表示有向图事先要准备好两项工作：
*  1. 建立一个数组来表示每个顶点的入度。
*  2. 建立一个堆栈，存放度数为0的顶点。
*
*/
void Graph_List::TopoOrder() {
	int n = GraphSize;
	int*count = new int[n];
	for (int k = 0; k < n; k++)
		count[k] = 0;
	//计算顶点的入度
	for (int i = 0; i < n; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			count[p->VerAdj]++;
			p = p->link;
		}
	}
	//初始化栈指针
	int  top = -1;
	//将度数为0的顶点入栈  这里的AOV网特指只有一个开始节点的情况。
	//如果在AVO网中存在多个开始的节点那么这里使用栈指针来进行表示
	for (int i = 0; i < n; i++)
		if (count[i] == 0) {
			count[i] = top;
			top = i;
		}
	for (int i = 0; i < n; i++) {
		//若循环还没有执行n次top就等于-1表示图中存在环，终止程序
		if (top == -1) {
			cout << "This is a  cycle in network!" << endl;
			return;
		}
		else {
			//从栈中弹出一个顶点j
			int j = top;
			top = count[top];
			//输出该顶点
			cout << j << " ";
			Edge*p = Head[j].adjacent;
			//从图中删除与j相关的边
			while (p != NULL) {
				int k = p->VerAdj;
				//k的入度减一，若入度为0，则k入栈
				if (--count[k] == 0) {
					count[k] = top;
					top = k;
				}
				p = p->link;
			}
		}
	}
	delete[]count;
}

//求AOE网的关键路径
void Graph_List::CriticalPath() {
	int n = GraphSize;
	//事件的最早发生时间
	int *ve = new int[n];
	//事件的最晚发生时间
	int *vl = new int[n];
	//初始化数组
	for (int i = 0; i < n; i++) {
		ve[i] = 0;
	}
	//按拓扑顺序计算各事件允许发生的最早发生时间
	for (int i = 0; i < n; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			int k = p->VerAdj;
			if (ve[i] + p->cost > ve[k])
				ve[k] = ve[i] + p->cost;
			p = p->link;
		}
	}
	//初始化数组
	for (int i = 0; i < n; i++) {
		vl[i] = ve[n - 1];
	}
	//逆序计算是件发生的最迟时间
	for (int i = n - 2; i >= 0; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			int k = p->VerAdj;
			if (vl[k] - p->cost < vl[i])
				vl[i] = vl[k] - p->cost;
			p = p->link;
		}
	}
	//求诸活动的最早开始时间和最迟开始时间,并且计算出关键路径
	for (int i = 0; i < n; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			int k = p->VerAdj;
			int e = ve[i];
			int l = vl[k] - p->cost;
			if (l == e) {
				cout << "<" << i << "," << k << ">" << "is Critical Activity" << endl;
			}
			p = p->link;
		}
	}
	delete[]ve;
	delete[]vl;
}


//无权单源路径的最短路径算法
//在这个算法中的每个顶点入队和出队的次数都为1，而对每个顶点都要对其边进行遍历，其遍历链表的开销为O(e),
//总的时间复杂度为O(n+e)
void Graph_List::ShortestPath(int v) {
	Edge*p;
	int n = GraphSize;
	//path记录从v到i的最短路径上的顶点i的前驱节点
	int *path = new int[n];
	//记录v到i的最短路径
	int *dist = new int[n];
	queue<int>Queue;
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		dist[i] = -1;
	}
	dist[v] = 0;
	Queue.push(v);
	//求从v到其他顶点的最短路径
	while (!Queue.empty()) {
		int u = Queue.front();
		Queue.pop();
		p = Head[u].adjacent;
		//将访问的邻接点入队并修改path和dist的值。
		while (p != NULL) {
			int k = p->VerAdj;
			//如果顶点没有被访问那么入队
			if (dist[k] == -1) {
				Queue.push(k);
				dist[k] = dist[u] + 1;
				path[k] = u;
			}
			p = p->link;
		}
	}
	delete[]path;
	delete[]dist;
}

//最短路径的Dijkstra算法
void Graph_List::DshortestPath(int v) {
	int max = 1000;
	Edge*p;
	int n = GraphSize;
	int*path = new int[n];
	int *dist = new int[n];
	//记录i是否被访问过
	int *s = new int[n];
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		dist[i] = -1;
		s[i] = 0;
	}
	dist[v] = 0;
	s[v] = 1;
	p = Head[v].adjacent;
	//u为即将被访问的节点
	int u = v;
	for (int i = 0; i < n; i++) {
		while (p != NULL) {
			int k = p->VerAdj;
			if (s[k] != 1 && dist[u] + p->cost < dist[k]) {
				dist[k] = dist[u] + p->cost;
				path[k] = u;
			}
			p = p->link;
		}
		//确定即将被访问的节点
		int ldist = max;
		for (int i = 0; i < n; i++)
			if (dist[i] > 0 && dist[i] < ldist&&s[i] == 0) {
				ldist = dist[i];
				u = i;
			}
		s[u] = 1;
		p = Head[u].adjacent;
	}
	delete[]path;
	delete[]dist;
	delete[]s;
}