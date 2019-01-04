#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<algorithm>
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
	int blackCnt = 0;
	int housing = 0;
	int dx[4] = { 1, -1, 0, 0 };	//동 서 남 북
	int dy[4] = { 0, 0, 1, -1 };


	//초기화
	for (i = 0; i < citySize; i++)
	{
		for (j = 0; j < citySize; j++)
		{
			color[i][j] = WHITE;
		}
	}

	//1이 발생하는 구간 찾기
	bool find = false;
	for (j = 0; j < citySize; j++)
	{
		for (i = 0; i < citySize; i++)
		{
			if (cityMap[j][i] == 1) //처음으로 1이 발생하는 구간을 찾는다. (첫 단지의 시작)
			{
				location startLocation(cityMap[j][i], j, i);
				find = true;
				color[j][i] = GRAY;
				pq.push(startLocation);
				break;
			}
			else
			{
				blackCnt++;
				color[j][i] = BLACK;
			}
		}
		if (find == true)
		{
			break;
		}
	}

	int index = 0;

	while (blackCnt < citySize * citySize) //전체를 다 확인할 때까지
	{
		while (!pq.empty())
		{
			location root = pq.top();	//1인 애만 들어있음
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
					if (color[nextY][nextX] == WHITE && cityMap[nextY][nextX] == 1)	//1이고 heap에 들어있지 않은 집만 힙에 넣는다.
					{
						pq.push(next);
						color[nextY][nextX] = GRAY;
					}
				}

			}
			color[root.y][root.x] = BLACK;
			blackCnt++;

			housing++;

		}
		houseResult.push_back(housing);	//주거단지 찾음. 완료.
		housing = 0;


		//다음으로 1이 발생하는 구간을 찾는다. (다음 주거단지의 시작)
		find = false;
		for (j = 0; j < citySize; j++)
		{
			for (i = 0; i < citySize; i++)
			{
				if ((cityMap[j][i] == 1) && (color[j][i] == WHITE))
				{
					location startLocation(cityMap[j][i], j, i);
					find = true;
					color[j][i] = GRAY;
					pq.push(startLocation);
					break;
				}
				else
				{
					if (color[j][i] != BLACK)
					{
						blackCnt++;
						color[j][i] = BLACK;
					}
				}
			}
			if (find == true)
				break;
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

	location start(cityMap[0][0], 0, 0);
	BFS(citySize, start);

	printf("%d\n", houseResult.size());
	sort(houseResult.begin(), houseResult.end());
	for (i = 0; i < houseResult.size(); i++)
	{
		if (houseResult[i] != 0)
			printf("%d\n", houseResult[i]);
	}

	system("pause");

}