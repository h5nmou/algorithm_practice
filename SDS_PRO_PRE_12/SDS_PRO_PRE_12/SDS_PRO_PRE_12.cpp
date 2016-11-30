#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int T; int N; // ���ð��� (3 �� N �� 10)
int M; // ���� ��¥ (2 �� M �� N �� 10)
int K; // ���ð� �̵� Ȯ�� ���� (3�� N �� K �� 30)

double citymoveProb[11][11];//[����A][����B] A->B�� �̵��� Ȯ��

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

	if (day == M) {//������ ������ ���� ������ �ȳ�~~~
		return;
	}

	for (int i = 1; i <= N; i++){//
		if (citymoveProb[allyprePos][i] != 0)// ally�� �ִ� ��ġ���� i ���÷� �� Ȯ���� ������
		{
			for (int j = 1; j <= N; j++)//
			{
				if (citymoveProb[noahprePos][j] != 0)// noah�� �ִ� ��ġ���� j ���÷� �� Ȯ���� ������
				{
					personmoveProb[day][i][j] = preDayProb * citymoveProb[allyprePos][i] * citymoveProb[noahprePos][j];//�ش����� Ȯ�� = �� ������ ������ ��ġ�� �־��� Ȯ�� * ������ ��ġ�� �� Ȯ��

					if (i == j)//�׷��� ���ٰ� ������ ��ġ�� ������ Ȯ���� ���� �ش�. 
						pSumRetVal += personmoveProb[day][i][j];
					else//������ ��ġ�� �ٸ��� ��� ���� �Ѵ�.
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

		personmoveProb[0][1][N] = 1;//ù��, ���� ally ��ġ, noah ��ġ�� ���� Ȯ�� 1
		fillTable(1, 1, N);//������, �������� �ٸ���ġ, �������� �����ġ -> ������ ���� ��ġ�� �� Ȯ���� ���ϴ� ����Լ��� �¿��.

		printf("#%d %0.3lf\n", t, pSumRetVal);
	}
}

