/*------------------미완성코드-------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<stack>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#pragma warning(disable:4996)

using namespace std;

typedef struct node {
	int vertex;
	struct node* next;
};

node* nodeList;
int* color;
int* p;
int vertex;

vector<int> dfs_result;
vector<int> bfs_result;
stack<int> s;
queue<int> q;

void DFS(int start)
{
	int i;
	node* tmp;
	tmp = &nodeList[start];
	tmp = tmp->next;

	color[start] = GRAY;
	while (1)
	{
		if (tmp == NULL)
		{
			break;
		}

		if (color[tmp->vertex] == WHITE)
		{
			p[tmp->vertex] = start;
			DFS(tmp->vertex);
		}
		tmp = tmp->next;
	}
	color[start] = BLACK;
	//dfs_result.push_back(start);
}

void BFS(int start)
{
	q.push(start);

	while (!q.empty())
	{
		int now = q.front();	q.pop();

		node* tmp;
		tmp = &nodeList[now];
		tmp = tmp->next;

		while (1)//다넣기
		{

			if (tmp == NULL)
				break;

			if (color[tmp->vertex] == WHITE)
			{
				q.push(tmp->vertex);
				color[tmp->vertex] = GRAY;
			}
			tmp = tmp->next;
		}
		color[now] = BLACK;
		printf("%d ", now);

	}
}

void insert(int ver1, int ver2)
{
	node* tmp;
	tmp = &nodeList[ver1];

	node* newNode;
	newNode = (node*)malloc(sizeof(node));
	newNode->vertex = ver2; newNode->next = NULL;

	if (nodeList[ver1].next == NULL) //첫연결이면
	{
		nodeList[ver1].next = newNode;
	}
	else //첫 연결이 아니면
	{
		while (1)
		{
			if (tmp->next == NULL)
			{
				tmp->next = newNode;
			}
			if (ver2 > tmp->next->vertex)
			{
				tmp = tmp->next;
			}
			else
			{
				node* nextNode = tmp->next;
				tmp->next = newNode;
				newNode->next = nextNode;
				break;
			}
		}
	}
	//반대연결도 해준다.
	node* tmp2;
	tmp2 = &nodeList[ver2];

	node* newNode2;
	newNode2 = (node*)malloc(sizeof(node));
	newNode2->vertex = ver1; newNode2->next = NULL;

	if (nodeList[ver2].next == NULL) //첫연결이면
	{
		nodeList[ver2].next = newNode2;
	}
	else //첫 연결이 아니면
	{
		while (1)
		{
			if (tmp->next == NULL)
			{
				tmp->next = newNode;
			}
			if (ver1 > tmp->next->vertex)
			{
				tmp = tmp->next;
			}
			else
			{
				node* nextNode2 = tmp->next;
				tmp->next = newNode2;
				newNode2->next = nextNode2;
				break;
			}
		}
	}
}

int main()
{
	int edge, start;
	int ver1, ver2;
	int i;

	scanf("%d %d %d", &vertex, &edge, &start);

	nodeList = (struct node*)malloc(sizeof(node)*(vertex + 1));
	color = (int*)malloc(sizeof(int)*(vertex + 1));
	p = (int*)malloc(sizeof(int)*(vertex + 1));

	for (i = 0; i < vertex + 1; i++)
	{
		nodeList[i].vertex = i;
		nodeList[i].next = NULL;
		color[i] = WHITE;
		p[i] = -1;
	}

	for (i = 0; i < edge; i++)
	{
		scanf("%d %d", &ver1, &ver2);
		insert(ver1, ver2);
	}

	DFS(start);

	for (i = dfs_result.size() - 1; i >= 0; i--)
	{
		printf("%d ", dfs_result[i]);
	}

	printf("\n");
	for (i = 0; i < vertex + 1; i++)
	{
		color[i] = WHITE;
		p[i] = -1;
	}

	BFS(start);


	system("pause");

}