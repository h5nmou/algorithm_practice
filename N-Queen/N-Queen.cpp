//http://koitp.org/problem/NQUEEN/read/

/*
N �� N�� ü���� ���� N���� ���� ���� ������ �� ���� ���� �����̴�.

N�� �־����� ��, ���� ���� ����� ���� ���Ͻÿ�.

�Է�
ù ��° �ٿ� �ڿ��� N�� �־�����. (1 �� N �� 12)

���
ù ��° �ٿ� �� N���� ���� ������ �� ���� ���� ����� ���� ����Ѵ�.
*/
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>

using namespace std;

int N;//1 �� N �� 12
int answer = 0;
int positionedQueenCount = 0;

pair<int, int>* QueenList[12];

bool possibleposition(int x, int y) {
  for (int i = 0; i < positionedQueenCount; i++) {
    if (x == QueenList[i]->first || y == QueenList[i]->second || abs(x - QueenList[i]->first) == abs(y - QueenList[i]->second)){//�̷��� ��ġ�� ��ġ�� �ִ°��̴�
      return false;
    }
  }
  return true;
}

void iterativeFunc(int x, int y) {
  for (int i = x; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (possibleposition(i, j)) {//���� ���� ���� �ִ� ��ġ�̸�
        QueenList[positionedQueenCount]->first = i;
        QueenList[positionedQueenCount]->second = j;
        positionedQueenCount++;

        if (positionedQueenCount  == N) {//������ queen �� ����������.
          answer++;
          positionedQueenCount--;
          continue;
        }else {
          iterativeFunc(i + 1, 0);
        }
      }
    }
  }

  //ü������ ������ ��������
  if (positionedQueenCount > 0) {
    positionedQueenCount--;
  }
}


int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    pair<int, int>* queen = (pair<int, int>*)malloc(sizeof(pair<int, int>*));
    QueenList[i] = queen;
  }

  iterativeFunc(0, 0);

  printf("%d", answer);

  return 0;
}

/*
2
10
4
40
92
352
724
2680
14200
*/
