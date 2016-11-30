/*
https://www.acmicpc.net/problem/2673
문제
평면상에 있는 원의 둘레에 100개의 점이 일정한 간격으로 시계방향으로 번호가 1, 2, ... 100으로붙여져 있다. 
이 점들을 끝점으로 갖는 N개의 선분(원의 현)이 입력으로 주어질 때, 
이들중에서 서로 교차하지 않는 것들을 최대한 많이 찾아서 그 개수를 출력하는 프로그램을 작성하라.

단, 1≤N≤50이고, 주어진 각 점은 많아야 한 현의 끝점이 될 수 있다.

입력
첫번째 줄은 주어지는 현의 개수 N이고, 다음의 N줄은 각 현의 양끝점의 번호가 주어진다.

출력
구한 현의 개수를 출력한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

int MIN(int a, int b) { return (a > b) ? b : a; };
int MAX(int a, int b) { return (a > b) ? a : b; };

int N;
int lineInfo[101][101];//line 정보
int DPTable[101][101];//

void initTable() {
  for (int i = 0; i < 101; i++) {
    for (int j = 0; j < 101; j++) {
      lineInfo[i][j] = 0;
      DPTable[i][j] = 0;
    }
  }
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%d", &N);

  initTable();

  int Dot1, Dot2;
  for(int i = 0; i < N; i++) {
    scanf("%d %d", &Dot1, &Dot2);
    lineInfo[Dot1][Dot2] = lineInfo[Dot2][Dot1] = 1;
  }

  for (int i = 100; i > 0; i--) {
    for (int j = i + 1; j <= 100; j++) {
      for (int k = i; k <= j - 1; k++) {
        DPTable[i][j] = MAX(DPTable[i][j], DPTable[i][k] + DPTable[k+1][j-1] + lineInfo[i][j]);
      }
    }
  }
  printf("%d", DPTable[1][100]);

  return 0;
}
