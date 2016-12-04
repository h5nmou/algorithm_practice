//http://koitp.org/problem/NQUEEN/read/ 

/*
N × N인 체스판 위에 N개의 퀸을 서로 공격할 수 없게 놓는 문제이다.

N이 주어졌을 때, 퀸을 놓는 방법의 수를 구하시오.

입력
첫 번째 줄에 자연수 N이 주어진다. (1 ≤ N ≤ 12)

출력
첫 번째 줄에 퀸 N개를 서로 공격할 수 없게 놓는 경우의 수를 출력한다.
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <functional> 
#include <vector> 

using namespace std;

int N;//1 ≤ N ≤ 12 
int answer = 0;
int positionedQueenCount = 0;

pair<int, int>* QueenList[12];

bool possibleposition(int x, int y) {
  for (int i = 0; i < positionedQueenCount; i++) {
    if (y == QueenList[i]->second || abs(x - QueenList[i]->first) == abs(y - QueenList[i]->second)) {//이러면 겹치는 위치에 있는것이다 
      return false;
    }
  }
  return true;
}

void iterativeFunc(int x) {
  //for (int i = x; i < N; i++) { 
  for (int j = 0; j < N; j++) {
    if (possibleposition(x, j)) {//말이 놓아 질수 있는 위치이면 
      QueenList[positionedQueenCount]->first = x;
      QueenList[positionedQueenCount]->second = j;
      positionedQueenCount++;

      if (positionedQueenCount == N) {//마지막 queen 이 놓아졌으면. 
        answer++;
        positionedQueenCount--;
        continue;
      }
      else {
        iterativeFunc(x + 1);
      }
    }
  }
  //} 

  //체스판의 끝까지 돌았으면 
  if (positionedQueenCount > 0) {
    positionedQueenCount--;
  }
}

int main() {
  freopen("sample_input.txt", "r", stdin); 
  scanf("%d", &N);
  //for(int tt = 4; tt <= 12; tt++){
  //  N = tt;
  answer = 0;

  for (int i = 0; i < N; i++) {
    pair<int, int>* queen = (pair<int, int>*)malloc(sizeof(pair<int, int>*));
    QueenList[i] = queen;
  }
  iterativeFunc(0);
  printf("%d\n", answer);
  //}
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