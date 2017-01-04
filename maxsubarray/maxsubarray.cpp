//http://koitp.org/problem/MAX_SUBARRAY/read/
/*
����
ũ�� N�� ���� �迭�� ������ �� ���� �κ� ���� �� ���� �ִ��� ���� ���� ���Ͻÿ�.

�Է�
ù ��° �ٿ� ũ�� N�� �־�����.(1��N��1,000,000)
�� ��° �ٿ� ũ�� N�� ���� �迭�� �־�����.

���
���� �κ� ������ �� �� �ִ밪�� ����Ͻÿ�. (��, ��°��� int ������ ��� �� �ִ�.)

��Ʈ
�Է� ����

10
-2 3 4 -5 30 -15 2 4 5 10
��� ����

38
*/
#include <stdlib.h>
#include <stdio.h>
#include <functional>

using namespace std;

long long int N;
long long int ARRAY[1000001];
long long int DPTable[1000001];

long long int MAX(long long int a, long long int b) { return (a > b) ? a : b; }

void initTable() {
  for (long long int i = 0; i < N; i++) {
    DPTable[i] = -1;
  }
}

long long int DPFunc(long long int index) {//ret : 0~index ���� ���� ���� �ִ� ������ 
  if (index < 0) {//������� ���� ó�� 
    return -1;
  }

  long long int &ret = DPTable[index];

  if (ret != -1) {
    return ret;
  }

  return ret = MAX(DPFunc(index - 1) + ARRAY[index], ARRAY[index]);
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%lld", &N);

  initTable();

  for (long long int i = 0; i < N; i++) {
    scanf("%lld", &ARRAY[i]);
  }

  DPTable[0] = ARRAY[0];
  printf("%lld", DPFunc(N - 1));
}