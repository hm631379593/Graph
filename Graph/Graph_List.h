#pragma once
#include"head.h"
//�߽ڵ�Ľṹ��
struct Edge
{
	friend class Graph_List;
	int VerAdj; 
	//�ڽӾ��󶨵���ţ���o��ʼ���б��
	int cost;  
	//�ߵ�Ȩ��
	Edge*link;
	//ָ����һ���߽ڵ��ָ��

};
//������нڵ�Ľṹ��
struct Vertex
{
	friend class Graph_List;
	int VerName;  
	//�ڵ������
	Edge*adjacent; 
	//�������ͷָ��
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
	//���õݹ���㷨�Ӷ����ĵ�һ�����㿪ʼ��ͼ����������ȵ����ء�
	void DepthFirstSerach();
	//���õ����ķ�����ָ���Ķ���v��ʼ����ͼ�������������
	void DFS(int v);
	//���õݹ�ķ�����ָ���Ķ���v��ʼ����ͼ�������������
	void RDFS(int v, int *visited);
	//�Ӷ���v��ʼ����ͼ�Ĺ�����ȱ���
	void BFS(int v);
	//���ͼ�����˽ṹ
	void TopoOrder();
	//���ͼ�Ĺؼ�·��
	void CriticalPath();
	//�ڷ�Ȩͼ����ָ�����㵽���������ж�������·��
	//��Ȩ��Դ·��
	void ShortestPath(int v);
	//��Ȩ��Դ·�������·����Dijkstra�㷨
	void DshortestPath(int v);
	//��ͼ����������֮������·��ʹ���ڽӾ���ʵ��
	void AllLength();
	//������С֧֮����������ķ�㷨
	void Prim();
	

};
void Graph_List::DepthFirstSerach() {
	int *visited = new int[GraphSize];
	for (int k=0; k < GraphSize; k++) {
		visited[k] = 0;
	}
	RDFS(0, visited);
	//�����Ϊ0�Ķ��������������ȱ���ͼ
	delete[]visited;
}
void Graph_List::RDFS(int v, int*visited) {
	cout << v << " ";
	//˵��v�Ѿ������ʹ�
	visited[v] = 1; 
	//ȡ�õ�һ���ڽӶ�������
	int w = GetFirstNeighbor(v);
	//�����ڽڵ�w����w�ݹ����
	while (w != -1) {
		if (!visited[w])
			RDFS(w,visited);
		//wΪv����w����һ���ڵ�
		w = GetNextNeighbor(v, w);
	}
}
void Graph_List::DFS(int v) {
	int *visited = new int[GraphSize];
	//����ĳ�ʼ��
	for (int k = 0; k < GraphSize; k++) {
		visited[k] = 0;
	}
	stack<int> Stack;
	//����ʼ�ڵ�ѹ��ջ�У�ջ��Ϊ�յ�ʱ����е���
	Stack.push(v);
	int w;
	while (!Stack.empty()) {
		//����һ��������Զ϶��ýڵ�û�б����ʹ�
		w = Stack.top();
		Stack.pop();
		//���øýڵ㱻���ʹ�
		visited[w] = 1;
		cout << w << " ";
		//ȡ�øýڵ�ĵ�һ���ڽӽڵ�
		int k = GetFirstNeighbor(w);
		//��kû���ڽӽڵ��ʱ��kΪ-1
		while (k!=-1)
		{ 
			//��kû�б����ʹ���ѹ��ջ��
			if (visited[k] == 0) {
				Stack.push(k);
			}
			k = GetNextNeighbor(w, k);
		}
	}
	delete[]visited;
}
//ͼ�Ĺ�����ȱ����Ĵ���Ҳ�ǲ�Ψһ��
void Graph_List::BFS(int s) {
	int* visited = new int[GraphSize];
	for (int k = 0; k < GraphSize; k++) {
		visited[k] = 0;
	}
	cout << s << " ";
	queue<int>Queue;
	Queue.push(s);
	while(!Queue.empty()) {
		int v = Queue.front();
		Queue.pop();
		int w = GetFirstNeighbor(v);
		while (w != -1) {
			if(!visited[w])
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
//��������Ļ�����۸��
//1. ��AOV����ѡ��һ�����Ϊ0�Ķ��㲢����ö��㡣
//2. ��AOV����ɾ���ö���������еĳ���
//3. ִ��1��2ֱ�����еĶ��㶼�Ѿ��������ʣ�µĶ�����Ⱦ���Ϊ0����˵�����д��ڻ�·���޷�������������
//����������򻹿��������ж�����ͼ���Ƿ���ڻ�·��



//����ʹ���ڽӱ��ʾ����ͼ����Ҫ׼�����������
//1. ����һ����������ʾÿ���������ȡ�
//2. ����һ����ջ����Ŷ���Ϊ0�Ķ��㡣
void Graph_List::TopoOrder() {
	int n = GraphSize;
	int*count = new int[n];
	for (int k = 0; k < n; k++)
		count[k] = 0;
	//���㶥������
	for (int i = 0; i < n; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			count[p->VerAdj]++;
			p = p->link;
		}
	}
	//��ʼ��ջָ��
	int  top = -1;
	//������Ϊ0�Ķ�����ջ  �����AOV����ָֻ��һ����ʼ�ڵ�������
	//�����AVO���д��ڶ����ʼ�Ľڵ���ô����ʹ��ջָ�������б�ʾ
	for (int i = 0; i < n; i++) 
		if (count[i] == 0) {
			count[i] = top;
			top = i;
		}
		for (int i = 0; i < n; i++) {
			//��ѭ����û��ִ��n��top�͵���-1��ʾͼ�д��ڻ�����ֹ����
			if (top == -1) {
				cout << "This is a  cycle in network!" << endl;
				return;
			}
			else {
				//��ջ�е���һ������j
				int j = top;
				top = count[top];
				//����ö���
				cout << j << " ";
				Edge*p = Head[j].adjacent;
				//��ͼ��ɾ����j��صı�
				while (p != NULL) {
					int k = p->VerAdj;
					//k����ȼ�һ�������Ϊ0����k��ջ
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

//��AOE���Ĺؼ�·��
void Graph_List::CriticalPath() {
	int n = GraphSize;
	//�¼������緢��ʱ��
	int *ve = new int[n];
	//�¼���������ʱ��
	int *vl = new int[n];
	//��ʼ������
	for (int i = 0; i < n; i++) {
		ve[i] = 0;
	}
	//������˳�������¼������������緢��ʱ��
	for (int i = 0; i < n; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			int k = p->VerAdj;
			if (ve[i] + p->cost > ve[k])
				ve[k] = ve[i] + p->cost;
			p = p->link;
		}
	}
	//��ʼ������
	for (int i = 0; i < n; i++) {
		vl[i] = ve[n - 1];
	}
	//��������Ǽ����������ʱ��
	for (int i = n - 2; i >= 0; i++) {
		Edge*p = Head[i].adjacent;
		while (p != NULL) {
			int k = p->VerAdj;
			if (vl[k] - p->cost < vl[i])
				vl[i] = vl[k] - p->cost;
			p = p->link;
		}
	}
	//���������翪ʼʱ�����ٿ�ʼʱ��,���Ҽ�����ؼ�·��
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


//��Ȩ��Դ·�������·���㷨
//������㷨�е�ÿ��������Ӻͳ��ӵĴ�����Ϊ1������ÿ�����㶼Ҫ����߽��б��������������Ŀ���ΪO(e),
//�ܵ�ʱ�临�Ӷ�ΪO(n+e)
void Graph_List::ShortestPath(int v) {
	Edge*p;
	int n = GraphSize;
	//path��¼��v��i�����·���ϵĶ���i��ǰ���ڵ�
	int *path = new int[n];
	//��¼v��i�����·��
	int *dist = new int[n];
	queue<int>Queue;
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		dist[i] = -1;
	}
	dist[v] = 0;
	Queue.push(v);
	//���v��������������·��
	while (!Queue.empty()) {
		int u = Queue.front();
		Queue.pop();
		p = Head[u].adjacent;
		//�����ʵ��ڽӵ���Ӳ��޸�path��dist��ֵ��
		while (p != NULL) {
			int k = p->VerAdj;
			//�������û�б�������ô���
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

//���·����Dijkstra�㷨
void Graph_List:: DshortestPath(int v) {
	int max = 1000;
	Edge*p;
	int n = GraphSize;
	int*path = new int[n];
	int *dist = new int[n];
	//��¼i�Ƿ񱻷��ʹ�
	int *s = new int[n];
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		dist[i] = -1;
		s[i] = 0;
	}
	dist[v] = 0;
	s[v] = 1;
	p = Head[v].adjacent;
	//uΪ���������ʵĽڵ�
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
		//ȷ�����������ʵĽڵ�
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
