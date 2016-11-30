#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int T; int N; // 도시갯수 (3 ≤ N ≤ 10)
int M; // 여행 날짜 (2 ≤ M ≤ N ≤ 10)
int K; // 도시간 이동 확률 갯수 (3≤ N ≤ K ≤ 30)

double citymoveProb[11][11];//[도시A][도시B] A->B로 이동할 확률

double personmoveProb[11][11][11];//[day][A][B]

double pSumRetVal;

void initTable() {
	pSumRetVal = 0;

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			citymoveProb[i][j] = 0;
			for (int k = 0; k < 11; k++) {
				personmoveProb[i][j][k] = 0;
			}
		}
	}
}

void fillTable(int day, int allyprePos, int noahprePos)
{
	float preDayProb = personmoveProb[day-1][allyprePos][noahprePos];

	if (day == M) {//마지막 날까지 여행 했으면 안녕~~~
		return;
	}

	for (int i = 1; i <= N; i++){//
		if (citymoveProb[allyprePos][i] != 0)// ally가 있는 위치에서 i 도시로 갈 확률이 있을때
		{
			for (int j = 1; j <= N; j++)//
			{
				if (citymoveProb[noahprePos][j] != 0)// noah가 있는 위치에서 j 도시로 갈 확률이 있을때
				{
					personmoveProb[day][i][j] = preDayProb * citymoveProb[allyprePos][i] * citymoveProb[noahprePos][j];//해당일의 확률 = 그 전날에 각각의 위치에 있었을 확률 * 각각의 위치로 갈 확률

					if (i == j)//그렇게 돌다가 서로의 위치가 같으면 확률을 더해 준다. 
						pSumRetVal += personmoveProb[day][i][j];
					else//서로의 위치가 다르면 계속 여행 한다.
						fillTable(day + 1, i, j);
				}
			}
		}
	}
}

int main(){
	freopen("sample_input.txt", "r", stdin);

	scanf("%d", &T);

	for (int t = 1; t <= T; t++){
		scanf("%d %d %d", &N, &M, &K);

		initTable();

		for (int i = 0; i < K; i++){
			double prob;
			int from, to;

			scanf("%d %d %lf", &from, &to, &prob);
			citymoveProb[from][to] = prob;
		}

		personmoveProb[0][1][N] = 1;//첫날, 각각 ally 위치, noah 위치에 있을 확률 1
		fillTable(1, 1, N);//다음날, 이전날의 앨리위치, 이전날의 노아위치 -> 각각이 다음 위치로 갈 확률을 구하는 재귀함수를 태운다.

		printf("#%d %0.3lf\n", t, pSumRetVal);
	}
}

