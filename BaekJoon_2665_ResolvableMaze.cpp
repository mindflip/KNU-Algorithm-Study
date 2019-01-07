#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define D 'D'
#define U 'U'
#define R 'R'
#define L 'L'
#define INFINITE 10000000
#define INT_MAX  10000000
#define ARR_MAX 1000

//void MazeSetting(char*fname);
void Init_Maze();
void print_path(FILE*f_out, int row, int col);

int maze_size;
char**maze;
char**T;
int**length;

int path_x[ARR_MAX];
int path_y[ARR_MAX];


int main()
{
	//FILE*f_in;
	//f_in = fopen(fname, "rb");

	/*if (f_in == NULL)
	{
		printf("파일명 오류 입니다\n");
		return;
	}*/

	scanf("%d\n", &maze_size);
	maze = (char**)malloc(sizeof(char*)*maze_size);
	for (int i = 0; i < maze_size; i++)
	{
		maze[i] = (char*)malloc(sizeof(char)*maze_size);
	}
	T = (char**)malloc(sizeof(char*)*maze_size);
	for (int i = 0; i < maze_size; i++)
	{
		T[i] = (char*)malloc(sizeof(char)*maze_size);
	}
	length = (int**)malloc(sizeof(int*)*maze_size);
	for (int i = 0; i < maze_size; i++)
	{
		length[i] = (int*)malloc(sizeof(int)*maze_size);
		for (int j = 0; j < maze_size; j++)
			length[i][j] = INFINITE;
	}



	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			scanf("%c ", &maze[i][j]);
		}
	}
	//fclose(f_in);
	length[0][0] = 0; //출발 지점 설정

	Init_Maze();
}
void Init_Maze()
{
	FILE*f_out;
	int i, j;
	int near;
	int row, col;

	while (1)
	{
		near = INT_MAX;
		for (i = 0; i<maze_size; i++)
		{
			for (j = 0; j<maze_size; j++)
			{
				if (length[i][j] >= 0 && length[i][j] <= near)
				{
					near = length[i][j];
					row = i;
					col = j;
				}
			}
		}

		if (row == maze_size - 1 && col == maze_size - 1)
			break;

		if ((row - 1 >= 0 && row - 1 < maze_size) && (col >= 0 && col < maze_size) && length[row - 1][col] == INT_MAX)
		{
			if (maze[row - 1][col] == '0')
				length[row - 1][col] = length[row][col] + 1;
			else
				length[row - 1][col] = length[row][col];
			T[row - 1][col] = 'D';
		}

		if ((row + 1 >= 0 && row + 1 < maze_size) && (col >= 0 && col < maze_size) && length[row + 1][col] == INT_MAX)
		{
			if (maze[row + 1][col] == '0')
				length[row + 1][col] = length[row][col] + 1;
			else
				length[row + 1][col] = length[row][col];
			T[row + 1][col] = 'U';
		}

		if ((row >= 0 && row < maze_size) && (col - 1 >= 0 && col - 1 < maze_size) && length[row][col - 1] == INT_MAX)
		{
			if (maze[row][col - 1] == '0')
				length[row][col - 1] = length[row][col] + 1;
			else
				length[row][col - 1] = length[row][col];
			T[row][col - 1] = 'R';
		}

		if ((row >= 0 && row < maze_size) && (col + 1 >= 0 && col + 1 < maze_size) && length[row][col + 1] == INT_MAX)
		{
			if (maze[row][col + 1] == '0')
				length[row][col + 1] = length[row][col] + 1;
			else
				length[row][col + 1] = length[row][col];
			T[row][col + 1] = 'L';
		}

		length[row][col] = -1;
	}

	//f_out = fopen("output.txt", "wt");
	printf("%d\n", length[maze_size - 1][maze_size - 1]);
	//print_path(f_out, row, col);
}
/*void print_path(FILE*f_out, int row, int col)
{
	int i, j;

	for (i = 0; row <= maze_size - 1 && col <= maze_size - 1; i++)
	{
		if (row == 0 && col == 0)
			break;
		switch (T[row][col])
		{
		case U:
			row--;
			break;
		case D:
			row++;
			break;
		case R:
			col++;
			break;
		case L:
			col--;
			break;
		default:
			break;
		}
		path_x[i] = row;
		path_y[i] = col;
	}

	//for (j = i - 1; j >= 0; j--)
	//{
		//fprintf(f_out, "%d %d\n", path_x[j] + 1, path_y[j] + 1);
	//}
	//fprintf(f_out, "%d %d\n", maze_size, maze_size);

	//fclose(f_out);
}*/


