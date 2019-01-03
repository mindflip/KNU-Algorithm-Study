#include<stdio.h>
#include<vector>
#include<algorithm>
#include<math.h>
#pragma warning(disable:4996)

using namespace std;

typedef struct location{
	int y;
	int x;
}location;

int main()
{
	int city;
	int m;
	int i, j;

	scanf("%d %d", &city, &m);

	vector<vector<int>> citymap(city, vector<int>(city, 0));
	vector<location> chickenLocation;
	vector<location> houseLocation;

	for (j = 0; j < city; j++)
	{
		for (i = 0; i < city; i++)
		{
			scanf("%d", &citymap[i][j]);
			if (citymap[i][j] == 1)//집위치
			{
				houseLocation.push_back({ j,i });
			}
			if (citymap[i][j] == 2) //치킨집위치
			{
				chickenLocation.push_back({ j,i });
			}
		}
	}
	//가능한 치킨집 중 M개만큼 뽑아, 조합의 형태로 전부 확인해볼 것

	vector<int> combination;
	for (i = 0; i < m; i++)//M개만큼 뽑아야한다.
	{
		combination.push_back(1);
	}
	for (i = 0; i < chickenLocation.size() - m; i++)
	{
		combination.push_back(0);
	}

	sort(combination.begin(), combination.end());
	vector<location> chosenM;
	vector<int> result;
	do {
		for (i = 0; i < combination.size(); i++)
		{
			if (combination[i] == 1)
			{
				chosenM.push_back(chickenLocation[i]);
			}
		}
		//M개 뽑았음
		//각 집에서 M개의 치킨집거리까지를 계산하고, 각각의 최솟값을 구한다.
		int min = 9999;
		int sum = 0;
		for (i = 0; i < houseLocation.size(); i++)
		{
			for (j = 0; j < chosenM.size(); j++)
			{
				if (abs(houseLocation[i].y - chosenM[j].y) + abs(houseLocation[i].x - chosenM[j].x) < min)
					min = abs(houseLocation[i].y - chosenM[j].y) + abs(houseLocation[i].x - chosenM[j].x);
			}
			//i번째 집에서 가장 가까운 치킨집 거리 찾음. 
			sum += min;
			min = 9999;
		}
		//모든 집에서 가까운 치킨집거리 다 찾음
		result.push_back(sum);
		chosenM.clear();

	} while (next_permutation(combination.begin(), combination.end()));

	sort(result.begin(), result.end());

	printf("%d", result[0]);
	system("pause");
}