#include <stdio.h>
#include <stdlib.h>

int i, j, s;

typedef struct
{
	int** arc;   //邻接矩阵 可看作边表   
	int numVertexes, numEdges;
}MGraph;

//图的邻接链表存储结构
//边表节点结构，一个adjvex用来存储邻接点的位置，一个next指针用来指向下一个节点
typedef struct EdgeNode
{
	int adjvex;  //存储顶点下标信息
	struct EdgeNode* next;
} EdgeNode;

//顶点表节点结构
typedef struct
{
	int Vexs;  //用来存储顶点信息
	EdgeNode* firstedge;  //用来存储当前顶点的下一个顶点
} VexList;

//这里用动态数组存储顶点表，然后numVertex,numEdge是一个图的顶点数和边数
typedef struct
{
	VexList* q;
	int Vertexs, Edges;
} LGraph;

//参数n为结点个数，m为边条数，e为所有边，out为输出序列。1 <= n <= 3000, 1 <= m <= 100000, 0 <= e[i][j] < n。
void solveA(int n, int m, int e[][2], int out[]);//邻接矩阵
void create(MGraph* G, int e[][2]);
void DFS(MGraph* G, int i, int* visited, int outA[]);
void solveB(int n, int m, int e[][2], int out[]);//邻接链表
void Lcreate(LGraph* G, int e[][2]);
void LDFS(LGraph* G, int i, int* visited, int outB[]);

int main() {
	int N = 0, M = 0;
	printf_s("请输入顶点数:\n");
	scanf_s("%d", &N);
	printf_s("请输入连边数:\n");
	scanf_s("%d", &M);
	if (N < 1 || N > 3000 || M < 1 || M > 100000)
	{
		return -1;
	}
	int(*E)[2] = NULL;
	E = (int(*)[2])malloc(sizeof(int) * M * 2);
	int* OUT = (int*)malloc(sizeof(int) * N);
	if (E == NULL ||OUT==NULL)
	{
		return -2;
	}
	printf_s("请输入所有连边:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			scanf_s("%d", &E[i][j]);
		}
	}
	solveA(N, M, E, OUT);
	for (i = 0; i < N; i++)
	{
		printf("%d ", OUT[i]);
	}
	printf("\n");
	solveB(N, M, E, OUT);
	for (i = 0; i < N; i++)
	{
		printf("%d ", OUT[i]);
	}
	system("pause");
	return 0;
}

void solveA(int n, int m, int e[][2], int out[])
{
	s = 0;
	MGraph* G = (MGraph*)malloc(sizeof(MGraph));
	G->numVertexes = n;
	G->numEdges = m;
	create(G, e);
	int* visited;
	visited = (int*)calloc(G->numVertexes, sizeof(int));
	for (i = 0; i < G->numVertexes; i++)
		if (visited[i] == 0)
			DFS(G, i, visited, out);
}

void create(MGraph* G, int e[][2])
{
	G->arc = (int**)malloc(sizeof(int*) * G->numVertexes);
	for (i = 0; i < G->numVertexes; i++)
	{
		G->arc[i] = (int*)calloc(G->numVertexes, sizeof(int));
	}
	for (j = 0; j < G->numEdges; j++)
	{
		G->arc[e[j][0]][e[j][1]] = 1;
		G->arc[e[j][1]][e[j][0]] = 1;
	}
}

void DFS(MGraph* G, int i, int* visited, int outA[])
{
	outA[s++] = i;
	visited[i] = 1;   //被访问的标记 
	for (int k = 0; k < G->numVertexes; k++)
	{
		if (G->arc[i][k] == 1 && visited[k] == 0)   //边(i,j)存在且j顶点未被访问，递归 
			DFS(G, k, visited, outA);
	}
}

void solveB(int n, int m, int e[][2], int out[])
{
	s = 0;
	LGraph* G = (LGraph*)malloc(sizeof(LGraph));
	G->Vertexs = n;
	G->Edges = m;
	Lcreate(G, e);
	int* visited;
	visited = (int*)calloc(G->Vertexs, sizeof(int));
	for (i = 0; i < G->Vertexs; i++)
		if (visited[i] == 0)
			LDFS(G, i, visited, out);
}

void Lcreate(LGraph* G, int e[][2])
{
	G->q = (VexList*)malloc(sizeof(VexList) * G->Vertexs);
	for (i = 0; i < G->Vertexs; i++)
	{
		G->q[i].Vexs = i;
		G->q[i].firstedge = NULL;
	}
	for (j = 0; j < G->Edges; j++)
	{
		EdgeNode* node1 = (EdgeNode*)malloc(sizeof(EdgeNode));
		node1->adjvex = e[j][1];
		node1->next = NULL;
		if (G->q[e[j][0]].firstedge == NULL)
		{
			G->q[e[j][0]].firstedge = node1;
		}
		else
		{
			EdgeNode* w = G->q[e[j][0]].firstedge;
			while (w->next != NULL)
			{
				w = w->next;
			}
			w->next = node1;
		}
		EdgeNode* node2 = (EdgeNode*)malloc(sizeof(EdgeNode));
		node2->adjvex = e[j][0];
		node2->next = NULL;
		if (G->q[e[j][1]].firstedge == NULL)
		{
			G->q[e[j][1]].firstedge = node2;
		}
		else
		{
			EdgeNode* w = G->q[e[j][1]].firstedge;
			while (w->next != NULL)
			{
				w = w->next;
			}
			w->next = node2;
		}
	}
}

void LDFS(LGraph* G, int i, int* visited, int outB[])
{
	outB[s++] = i;
	visited[i] = 1;   //被访问的标记 
	if (G->q[i].firstedge != NULL)
	{
		EdgeNode* t = (G->q[i].firstedge);
		while (visited[t->adjvex] == 1 && t->next != NULL)
		{
			t = t->next;
		}
		if (visited[t->adjvex] == 1 && t->next == NULL)
		{
			return;
		}
		LDFS(G, t->adjvex, visited, outB);
	}
}