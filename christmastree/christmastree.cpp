//https://www.acmicpc.net/problem/1234
/*
문제
오민식은 오늘이 크리스마스라고 생각해서, 크리스마스 트리를 만드려고 한다. 트리는 N개의 레벨로 이루어져 있다. 위에서부터 레벨1, ... 레벨 N이다. 또, 민식이는 빨강, 파랑, 초록색의 장난감을 가지고 있다. 그리고 민식이는 이 장난감을 일정한 규칙에 의해서 장식하려고 한다.

레벨 K에는 딱 K개의 장난감이 있어야 한다. 또, 각 레벨에 놓으려고 선택한 색이 있으면, 그 색의 장난감의 수는 서로 같아야 한다. 예를 들어, 레벨 3에 장난감을 놓으려고 할 때, 빨강 2, 파랑 1과 같이 놓으면, 빨강과 파랑의 수가 다르기 때문에 안된다. 하지만, 레벨 4에 빨강 2, 파랑 2와 같이 놓으면, 가능하다.

N과, 장난감의 수가 주어질 때, 트리를 장식하는 경우의 수를 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 트리의 크기 N, 빨강의 개수, 초록의 개수, 파랑의 개수가 주어진다. N은 10보다 작거나 같다. 빨강, 초록, 파랑의 개수는 0보다 크거나 같고, 100보다 작거나 같다.

출력
첫째 줄에 경우의 수를 출력한다. 이 값은 int범위를 넘어가는 long long범위이고, 만약 주어진 장난감으로 트리를 장식할 수 없으면 0을 출력한다.
*/
#include <stdio.h>
#include <stdlib.h>
#include <functional>

using namespace std;

//중복되는 원소가 있는 배열을 나열하는 경우의 수
//예를 들어 a와 b를 가지고 N배열을 채우는 경우의 수는 a,a,b,b,b 인 경우 a = 2, b = 3, N = 5
//5!/2!*3! 이다.

long long int factorial(int n) {
  if (n == 0 || n == 1) return 1;
  return n*factorial(n - 1);
}

int N, R, G, B;

long long int DPTable[11][101][101][101];
long long int bojoMatrix[4][11];//[개의 색깔을 가지고][개의 칸을 채울수 있는 경우의 수] 단 두 색깔의 사용 횟수는 같아야 한다.

void initTable() {
  //memset(DPTable, -1, sizeof(DPTable));//메모리 초기화
  //memset(bojoTable, -1, sizeof(bojoTable));//메모리 초기화
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 101; j++) {
      for (int k = 0; k < 101; k++) {
        for (int l = 0; l < 101; l++) {
          DPTable[i][j][k][l] = -1;
        }
      }
    }
  }

  for (int k = 0; k < 4; k++) {
    for (int l = 0; l < 11; l++) {
      bojoMatrix[k][l] = -1;
    }
  }
}

void makebojoMatrixTable() {
  for (int section = 1; section <= 10; section++) {
    //if (section % 1 == 0) {
      bojoMatrix[1][section] = 1;
    //}

    if (section % 2 == 0) {
      bojoMatrix[2][section] = factorial(section) / (factorial(section / 2) * factorial(section / 2));
    }

    if (section % 3 == 0) {
      bojoMatrix[3][section] = factorial(section) / (factorial(section / 3) * factorial(section / 3) * factorial(section / 3));
    }
  }
}

long long int DPFunc(int n, int r, int g, int b) {//n개의 레벨을 r,g,b를 가지고 채울수 있는 경우의 수
  //기저사례 처리
  if (r < 0 || g < 0 || b < 0) return 0;//색깔을 초과해서 사용하는 경우는 없는것으로 처리
  if (n == 0) return 1;//1레벨까지 왔으면 하나의 경우가 있게 됨

  long long int &ret = DPTable[n][r][g][b];
  if (ret != -1) return ret;

  ret = 0;

  //N레벨을 하나의 색으로 채우는 경우 
  ret += DPFunc(n - 1, r - n, g, b) * bojoMatrix[1][n];//R
  ret += DPFunc(n - 1, r, g - n, b) * bojoMatrix[1][n];//G
  ret += DPFunc(n - 1, r, g , b - n) * bojoMatrix[1][n];//B

  //N레벨을 두개의 색으로 채우는 경우 
  if (n % 2 == 0) {
    ret += DPFunc(n - 1, r - (n / 2), g - (n / 2), b) * bojoMatrix[2][n];//R,G
    ret += DPFunc(n - 1, r - (n / 2), g, b - (n / 2)) * bojoMatrix[2][n];//R,B
    ret += DPFunc(n - 1, r, g - (n / 2), b - (n / 2)) * bojoMatrix[2][n];//G,B
  }

  //N레벨을 세개의 색으로 채우는 경우
  if (n % 3 == 0) {
    ret += DPFunc(n - 1, r - (n / 3), g - (n / 3), b - (n / 3)) * bojoMatrix[3][n];//R,G,B
  }

  return ret;
}

int main(){
  freopen("sample_input.txt", "r", stdin);
  initTable();

  scanf("%d %d %d %d", &N, &R, &G, &B);

  makebojoMatrixTable();

  printf("%lld", DPFunc(N, R, G, B));
}