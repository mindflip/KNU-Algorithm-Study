#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<queue>
#pragma warning(disable:4996)

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

typedef struct location {
	int value;
	int y;
	int x;
	
	location(int v, int coord_y, int coord_x)
	{
		value = v;
		y = coord_y;
		x = coord_x;
	}
	bool operator<(const location &a) const {
		return value < a.value;
	}
	bool operator<=(const location &a) const {
		return value < a.value;
	}
	bool operator>(const location &a) const {
		return value > a.value;
	}
	bool operator>=(const location &a) const {
		return value >= a.value;
	}
	bool operator==(const location &a) const {
		return value == a.value;
	}

}location;


priority_queue<location, vector<location>, less<location>> pq;

vector<int> houseResult(0, 0);
int** cityMap;
int** color;

void BFS(int citySize, location start)
{
	int i, j;
	int housing = 0;
	int dx[4] = {1, -1, 0, 0};	//동 서 남 북
	int dy[4] = {0, 0, 1, -1};


	//초기화
	for (i = 0; i < citySize; i++)
	{
		for (j = 0; j < citySize; j++)
		{
			color[i][j] = WHITE;
		}
	}

	location startLocation(cityMap[start.y][start.x], start.y, start.x);
	color[start.y][start.x] = GRAY;
	pq.push(startLocation);

	while (!pq.empty())
	{
		location root = pq.top();
		pq.pop();

		color[root.y][root.x] = GRAY;

		//cityMap크기벗어나지 않는 한도 내로 움직여보고 Heap에 넣는다.
		for (i = 0; i < 4; i++)
		{
			int nextX = root.x + dx[i];
			int nextY = root.y + dy[i];

			if (nextX < citySize && nextY < citySize && nextX >= 0 && nextY >= 0)
			{
				location next(cityMap[nextY][nextX], nextY, nextX);
				if (color[nextY][nextX] == WHITE)
				{
					pq.push(next);
					color[nextY][nextX] = GRAY;
				}
			}
				
		}
		color[root.y][root.x] = BLACK;

		if (root.value == 1)
		{
			housing++;
		}
		else
		{
			if(housing != 0)
				houseResult.push_back(housing);
			housing = 0;
		}
	}
	
}

int main()
{
	int citySize;
	int tmp;
	int i, j;

	scanf("%d", &citySize);
		
	cityMap = (int**)malloc(sizeof(int*)*citySize);
	color = (int**)malloc(sizeof(int*)*citySize);

	for (i = 0; i < citySize; i++)
	{
		cityMap[i] = (int*)malloc(sizeof(int)*citySize);
		color[i] = (int*)malloc(sizeof(int)*citySize);
	}

	char character;
	scanf("%c", &character);
	for (i = 0; i < citySize; i++)
	{
		for (j = 0; j < citySize; j++)
		{
			scanf("%c", &character);
			cityMap[i][j] = character - '0';
		}
		scanf("%c", &character);
	}
	
	location start(cityMap[0][0],0,0);
	BFS(citySize, start);

	printf("%d\n", houseResult.size());
	for (i = 0; i < houseResult.size(); i++)
	{
		if(houseResult[i] != 0)
			printf("%d\n", houseResult[i]);
	}

	system("pause");
	
}