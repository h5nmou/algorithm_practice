//http://koitp.org/problem/MAX_SUBARRAY/read/
/*
문제
크기 N인 정수 배열이 들어왔을 때 연속 부분 수열 중 합이 최대인 것의 합을 구하시오.

입력
첫 번째 줄에 크기 N이 주어진다.(1≤N≤1,000,000)
두 번째 줄에 크기 N인 정수 배열이 주어진다.

출력
연속 부분 수열의 합 중 최대값을 출력하시오. (단, 출력값이 int 범위를 벗어날 수 있다.)

힌트
입력 예제

10
-2 3 4 -5 30 -15 2 4 5 10
출력 예제

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

long long int DPFunc(long long int index) {//ret : 0~index 까지 있을 때의 최대 구간합 
  if (index < 0) {//기저사례 먼저 처리 
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