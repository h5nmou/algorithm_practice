/*
https://www.acmicpc.net/problem/2673
����
���� �ִ� ���� �ѷ��� 100���� ���� ������ �������� �ð�������� ��ȣ�� 1, 2, ... 100���κٿ��� �ִ�. 
�� ������ �������� ���� N���� ����(���� ��)�� �Է����� �־��� ��, 
�̵��߿��� ���� �������� �ʴ� �͵��� �ִ��� ���� ã�Ƽ� �� ������ ����ϴ� ���α׷��� �ۼ��϶�.

��, 1��N��50�̰�, �־��� �� ���� ���ƾ� �� ���� ������ �� �� �ִ�.

�Է�
ù��° ���� �־����� ���� ���� N�̰�, ������ N���� �� ���� �糡���� ��ȣ�� �־�����.

���
���� ���� ������ ����Ѵ�.
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
int lineInfo[101][101];//line ����
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
