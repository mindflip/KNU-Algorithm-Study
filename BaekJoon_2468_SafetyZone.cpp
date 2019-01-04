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
	int y;
	int x;
	location(int coord_y, int coord_x)
	{
		y = coord_y;
		x = coord_x;
	}

}location;

int** cityMap;
int** color;
int citySize;
vector<int> result;
queue<location> Q;

void BFS(int rain)
{
	int i, j;
	int blackCnt = 0;

	//초기화 겸 잠긴지역 설정
	for (j = 0; j < citySize; j++)
	{
		for (i = 0; i < citySize; i++)
		{
			if (cityMap[j][i] <= rain)//높이가 낮으면 잠기게
			{
				color[j][i] = BLACK;
				blackCnt++;
			}
			else
				color[j][i] = WHITE;
		}
	}

	//첫 번째 구역의 시작 찾기
	bool find = false;
	for (j = 0; j < citySize; j++)
	{
		for (i = 0; i < citySize; i++)
		{
			if (color[j][i] == WHITE)
			{
				find = true;
				break;
			}
		}
		if (find == true)
			break;
	}
	if (find == true)
	{
		location start({ j, i });
		Q.push(start);
	}
	else //시작점 없이 다 잠겼으면
	{
		blackCnt = citySize * citySize;
	}

	int district = 0;

	while (blackCnt != citySize * citySize)
	{
		while (!Q.empty())
		{
			location now = Q.front();
			Q.pop();

			int dx[4] = { 1,-1,0,0 };
			int dy[4] = { 0,0,1,-1 };

			for (i = 0; i < 4; i++)
			{
				int nextY = now.y + dy[i];
				int nextX = now.x + dx[i];

				if ((nextY < citySize && nextX < citySize && nextY >= 0 && nextX >= 0) && color[nextY][nextX] == WHITE)
				{
					location next({ nextY,nextX });
					color[nextY][nextX] = GRAY;
					Q.push(next);
				}
			}

			color[now.y][now.x] = BLACK;
			blackCnt++;

		}
		district++; //구역하나 찾음

		if (blackCnt == citySize * citySize)
			break;

		//다음 구역 찾기
		find = false;
		for (j = 0; j < citySize; j++)
		{
			for (i = 0; i < citySize; i++)
			{
				if (color[j][i] == WHITE)
				{
					find = true;
					break;
				}
				
			}
			if (find == true)
				break;
		}
		if (find == true)
		{
			location start({ j, i });
			Q.push(start);
		}
	}

	result.push_back(district);
}

int main()
{
	int highest=0;
	int i, j;

	scanf("%d", &citySize);

	cityMap = (int**)malloc(sizeof(int*)*citySize);
	color = (int**)malloc(sizeof(int*)*citySize);

	for (i = 0; i < citySize; i++)
	{
		cityMap[i] = (int*)malloc(sizeof(int)*citySize);
		color[i] = (int*)malloc(sizeof(int)*citySize);
	}

	for (j = 0; j < citySize; j++)
	{
		for (i = 0; i < citySize; i++)
		{
			scanf("%d",&cityMap[j][i]);
			if (highest < cityMap[j][i])	//제일 높은 위치 구해놓기.
			{
				highest = cityMap[j][i];
			}
		}
	}

	//비가 오지 않는 0부터 highest-1까지.
	//starting point는 항상 0,0이므로 굳이 파라미터로 넘겨주지 않는다.
	int rain;
	for (rain = 0; rain < highest; rain++)
	{
		BFS(rain);
	}
	sort(result.begin(), result.end());
	printf("%d", result[result.size()-1]);

	system("pause");
}