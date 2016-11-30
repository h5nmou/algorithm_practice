//SDS_PRO_1_2 ADJACENTBIT
//http://www.koitp.org/problem/ICPC_2009GNY_ADJACENTBIT/read/
//동적 계획법을 이용한 인접한 비트수를 K 개 가진 수열 S의 갯수 구하기 

#include <stdio.h>
#include <memory>

int testCase = 0;//1 ≤ T ≤ 1,000
int testNum = 0;
int N = 0;//수열의 크기 
int K = 0;//인접한 비트의 수
int dpTable[101][101][2];//[수열크기][인접비트수][0,1]

void initTable() {
  //memset(dpTable, -1, sizeof(dpTable));//-1로 초기화 한다. 
  for (int i = 0; i < 101; i++) {
    for (int j = 0; j < 101; j++) {
      if (i == 1 || i == j) {
        dpTable[i][j][0] = 0;
        dpTable[i][j][1] = 0;
      }
      else {
        dpTable[i][j][0] = -1;
        dpTable[i][j][1] = -1;
      }
    }
  }
}

void printTable() {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= K; j++) {
      printf("dpTable[%d][%d][0] = %d dpTable[%d][%d][1] = %d\n", i, j, dpTable[i][j][0], i, j, dpTable[i][j][1]);
    }
  }
}

int DPFunc(int remainSpace, int remainK, int startBit) {//자릿수, 인접비트수, 시작 비트 //시작 비트가 bit일때에 자릿수크기의 수열에서 인접비트수를 가지는 수열의 갯수

  if (remainSpace == 2 && remainK == 0 && startBit == 1) {
    int a = 0;
  }
  //기저사례
  if (remainSpace == 0 || remainSpace == remainK) {
    return 0;
  }

  //저장된것 리턴 
  int& retVal = dpTable[remainSpace][remainK][startBit];
  if (retVal != -1) {
    return retVal;
  }

  //자릿수는 항상 줄어들고 
  //시작비트가 0인경우 remainSpace -1 자릿수의 0인 경우 
  if (startBit == 0) {
    retVal = DPFunc(remainSpace - 1, remainK, 0) + DPFunc(remainSpace - 1, remainK, 1);
  }

  //시작비트가 1인경우 
  if (startBit == 1) {
    retVal = DPFunc(remainSpace - 1, remainK, 0) + DPFunc(remainSpace - 1, remainK - 1, 1);
  }

  return retVal;
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%d", &testCase);
  for (int i = 1; i <= testCase; i++) {
    scanf("%d %d %d", &testNum, &N, &K);

    initTable();

    //초기값 넣어주기
    //수열크기가 1이라면 모두 0 -> initTable()
    dpTable[2][0][0] = 2;
    dpTable[2][0][1] = 1;
    dpTable[2][1][0] = 0;
    dpTable[2][1][1] = 1;

    //do
    printf("%d %d\n", testNum, DPFunc(N, K, 0) + DPFunc(N, K, 1));

    //printTable();
  }
}