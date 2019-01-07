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
int vertex;

vector<int> dfs_result;
stack<int> s;
queue<int> q;

void DFS(int start)
{
	int i;
	vector<int> tmpStack;

	s.push(start);

	while (!s.empty())
	{
		int now = s.top();	s.pop(); dfs_result.push_back(now); 
		node* tmp;
		tmp = &nodeList[now];
		tmp = tmp->next;

		while (1)//�Ǵ¾ֵ� �� �ֱ�. 
		{
			if (tmp == NULL)
				break;

			if (color[tmp->vertex] == WHITE)
			{
				tmpStack.push_back(tmp->vertex);
			}
			tmp = tmp->next;
		}
		for (i = tmpStack.size() - 1; i >= 0; i--)	//�����ͺ��� �湮�ϱ� ���� ���� ������ ���� ���� �Ųٷ� ����
		{
			s.push(tmpStack[i]);
		}
		tmpStack.clear();
		color[now] = BLACK;
	}
}

void BFS(int start)
{
	q.push(start);
	color[start] = GRAY;

	while (!q.empty())
	{
		int now = q.front();	q.pop();

		node* tmp;
		tmp = &nodeList[now];
		tmp = tmp->next;

		while (1)//�ٳֱ�
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

	if (nodeList[ver1].next == NULL) //ù�����̸�
	{
		nodeList[ver1].next = newNode;
	}
	else //ù ������ �ƴϸ�
	{
		while (1)//�����ͺ��� �湮�ؾ��ϹǷ� ����������� �ִ´�.
		{
			if (tmp->next == NULL)
			{
				tmp->next = newNode;
				break;
			}
			if (ver2 == tmp->next->vertex)
			{
				break;
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
	//�ݴ뿬�ᵵ ���ش�.
	node* tmp2;
	tmp2 = &nodeList[ver2];

	node* newNode2;
	newNode2 = (node*)malloc(sizeof(node));
	newNode2->vertex = ver1; newNode2->next = NULL;

	if (nodeList[ver2].next == NULL) //ù�����̸�
	{
		nodeList[ver2].next = newNode2;
	}
	else //ù ������ �ƴϸ�
	{
		while (1)//�����ͺ��� �湮�ؾ��ϹǷ� ����������� �ִ´�.
		{
			if (tmp2->next == NULL)
			{
				tmp2->next = newNode2;
				break;
			}
			if (ver1 == tmp2->next->vertex)
			{
				break;
			}
			if (ver1 > tmp2->next->vertex)
			{
				tmp2 = tmp2->next;
			}
			else
			{
				node* nextNode2 = tmp2->next;
				tmp2->next = newNode2;
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
	
	for (i = 0; i < vertex + 1; i++)
	{
		nodeList[i].vertex = i;
		nodeList[i].next = NULL;
		color[i] = WHITE;
	}

	for (i = 0; i < edge; i++)
	{
		scanf("%d %d", &ver1, &ver2);
		insert(ver1, ver2);
	}

	DFS(start);

	int min = vertex;
	if (dfs_result.size() < vertex)
	{
		min = dfs_result.size();
	}
	for (i = 0; i < min; i++)
	{
		printf("%d ", dfs_result[i]);
	}
	printf("\n");


	for (i = 0; i < vertex + 1; i++)
	{
		color[i] = WHITE;
	}
	BFS(start);


	system("pause");

}