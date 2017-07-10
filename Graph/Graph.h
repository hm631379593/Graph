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
	//���õݹ���㷨�Ӷ����ĵ�һ�����㿪ʼ��ͼ����������ȵ����ء�
	void DepthFirstSerach();
	//���õ����ķ�����ָ���Ķ���v��ʼ����ͼ�������������
	void DFS(int v);
	//�Ӷ���v��ʼ����ͼ�Ĺ�����ȱ���
	void BFS(int v);
	//���ͼ�����˽ṹ
	void TopoOrder();
	//���ͼ�Ĺؼ�·��
	void CriticalPath();
	//�ڷ�Ȩͼ����ָ�����㵽���������ж�������·��
	void ShortestPath(int v);
	//������С֧֮����������ķ�㷨
	void Prim();
	//����������֮�����̾���
	void AllLength();



}; 
//��ͼ����������֮������·��
//����Eage[n][n]�������������ͼ���ڽӾ���A[i][j]�Ƕ���Vi��Vj�����·������
//Path[i][j]����Ӧ·���϶���j��ǰһ���������š�
void Graph::AllLength() {
	int n = GraphSize;
	int **path = new int*[n];
	int **A = new int*[n];
	for (int i = 0; i < n; i++) {
		path[i] = new int[n];
		A[i] = new int[n];
	}
	//��ʼ������A��path
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			A[i][j] = Edge[i][j];
			if (i != j&&A[i][j] < Max)
				path[i][j] = i;
			else
				path[i][j] = -1;

		}
	//��A^-1��ʼ����A^(n-1)
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
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

//��С֧����������ķ�㷨
void Graph::Prim() {
	int n = GraphSize;
	struct LV
	{
		int LowCost;
		int Vex;

	}*clouseEdge = new LV[n];
	struct EdgeCost{
		int head;
		int tail;
		int cost;
	}*TE = new EdgeCost[n];
	//��ʼ���ڽӾ���
	for (int i = 0;i < n; i++)
		for (int j = 0; j < n; j++) {
			if (Edge[i][j] == 0)
				//MaxΪԤ����ĳ���
				Edge[i][j] = Max;
		}
	//�Զ���0Ϊ��ʼ���㣬��ʼ������closeEdge
	for (int i = 0; i < n; i++)
	{
		clouseEdge[i].LowCost = Edge[0][i];
		clouseEdge[i].Vex = 0;
	}
	//����0���뼯��U
	clouseEdge[0].Vex = -1;
    //֧�����ı߼�����count
	int count = 0;
	//ѭ��n-1��
	for (int i = 1; i < n; i++) {
		//������Сֵ
		int min = Max+1;
		int v = 0;
		//��ǰȨֵ��С�ıߺ͸ñߵ��յ�v
		for (int j = 0; j < n; j++) 
			if (clouseEdge[j].Vex != -1 && clouseEdge[j].LowCost < min) {
				v = j;
				min = clouseEdge[j].LowCost;
			}
		//��v==0˵��û���ҵ����������Ķ���
			if (v != 0) {
				//��֧�����еı߼���TE�����һ����
				TE[count].head = clouseEdge[v].Vex;
				TE[count].tail = v;
				TE[count].cost = clouseEdge[v].LowCost;
				//��������һ
				count++;
				//�޸���ֵ
				clouseEdge[v].LowCost = 0;
				//������뼯��U
				clouseEdge[v].Vex = -1;
				//��Ϊv�ļ�����Ҫ�޸�ĳЩֵ
					for(int j=0;i<n;i++)
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
