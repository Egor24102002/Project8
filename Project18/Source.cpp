#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define HEADER ("Лабораторная работа №6\nВыполнил:Пантюшов Е.\n\n")
#include <queue>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
using namespace std;
void bfs(int** G, int* DIST, int v, int n)
{
	queue <int> q;
	q.push(v);
	DIST[v] = 0;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		for (int i = 0; i < n; i++)
		{
			if ((G[v][i] > 0) && (DIST[i] > DIST[v] + G[v][i]))
			{
				q.push(i);
				DIST[i] = DIST[v] + G[v][i];
			}
		}
	}
}
void task_1_1(int** G, int n)
{
	for (int i = 0; i < n; i++)
	{
		G[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
		{
			G[i][j] = rand() % 10;
			if (G[i][j] < 5)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = rand() % 5;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = G[j][i];
			}
			printf(" %d ", G[i][j]);
		}
		printf("\n");
	}

}
void task_1_2(int** G, int n, int* r, int* d, int* EX)
{
	int* DIST = (int*)malloc(n * sizeof(int));
	int v;
	for (int i = 0; i < n; i++)
	{
		EX[i] = -1;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			DIST[j] = INT_MAX;
		}
		bfs(G, DIST, i, n);
		for (int k = 0; k < n; k++)
		{
			if ((EX[i] < DIST[k]) && (DIST[k] != INT_MAX))
				EX[i] = DIST[k];
		}
	}
	for (int i = 0; i < n; i++)
		printf("Эксцентриситет %d-ой вершины= %d \n", i, EX[i]);
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		if (*r > EX[i])
			*r = EX[i];
	}
	for (int i = 0; i < n; i++)
	{
		if (*d < EX[i])
			*d = EX[i];
	}
	printf("Диаметр графа=%d\n", *d);
	printf("Радиус графа=%d\n", *r);
	free(DIST);
}
void task_1_3(int** G, int n, int* d, int* r, int* EX)
{
	printf("Множество периферийных вершин:");
	for (int i = 0; i < n; i++)
	{
		if (EX[i] == *d)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
	printf("Множество центральных вершин:");
	for (int i = 0; i < n; i++)
	{
		if (EX[i] == *r)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
}
void task_1_4(int** G, int n)
{
	int* VER = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		VER[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (G[i][j] != 0)
				VER[i] = VER[i] + 1;
	}
	printf(" Изолированные вершины:");
	for (int i = 0; i < n; i++)
	{
		if (VER[i] == 0)
			printf("%d ", i);
	}
	printf("\n");
	printf(" Кольцевые вершины:");
	for (int i = 0; i < n; i++)
	{
		if (VER[i] == 1)
			printf("%d ", i);
	}
	printf("\n");
	printf(" Доминирующие вершины:");
	for (int i = 0; i < n; i++)
	{
		if (VER[i] == n - 1)
			printf("%d ", i);
	}
	printf("\n");
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	printf("Введите размерность матрицы: ");
	int n;
	scanf("%d", &n);
	int** G = (int**)malloc(n * sizeof(int*));
	int* EX = (int*)malloc(n * sizeof(int));
	int r, d;
	r = INT_MAX;
	d = -1;
	task_1_1(G, n);
	task_1_2(G, n, &r, &d, EX);
	task_1_3(G, n, &d, &r, EX);
	task_1_4(G, n);
	system("PAUSE");
	return 0;
}