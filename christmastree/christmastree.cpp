//https://www.acmicpc.net/problem/1234

#include <stdio.h>
#include <stdlib.h>
#include <functional>

int N, R, G, B;

long long int DPTable[11][101][101][101];
long long int bojoTable[4][11];//[개의 색깔을 가지고][개의 칸을 채울수 있는 경우의 수] 단 두 색깔의 사용 횟수는 같아야 한다.

long long int makebojoTable(int colorNo, int section) {

}

long long int DPFunc(int n, int r, int g, int b) {//n개의 레벨을 r,g,b를 가지고 채울수 있는 경우의 수
  //기저사례 처리
  if (r < 0 || g < 0 || b < 0) return 0;//색깔을 초과해서 사용하는 경우는 없는것으로 처리
  if (n == 0) return 1;//1레벨까지 왔으면 하나의 경우가 있게 됨

  long long int &ret = DPTable[n][r][g][b];
  if (ret != -1) return ret;

  ret = 0;

  //N레벨을 하나의 색으로 채우는 경우 
  ret += DPFunc(n - 1, r - n, g, b);//R
  ret += DPFunc(n - 1, r, g - n, b);//G
  ret += DPFunc(n - 1, r, g , b - n);//B

  //N레벨을 두개의 색으로 채우는 경우 
  if (n % 2 == 0) {
    ret += DPFunc(n - 1, r - (n / 2), g - (n / 2), b);//R,G
    ret += DPFunc(n - 1, r - (n / 2), g, b - (n / 2));//R,B
    ret += DPFunc(n - 1, r, g - (n / 2), b - (n / 2));//G,B
  }

  //N레벨을 세개의 색으로 채우는 경우
  if (n % 3 == 0) {
    ret += DPFunc(n - 1, r - (n / 3), g - (n / 3), b - (n / 3));//R,G,B
  }

  return ret;
}

int main(){
  freopen("sample_input.txt", "r", stdin);
  memset(DPTable, -1, sizeof(DPTable));//메모리 초기화
  memset(bojoTable, -1, sizeof(bojoTable));//메모리 초기화

  scanf("%d %d %d %d", &N, &R, &G, &B);

  makebojoTable();

  printf("%lld", DPFunc(N, R, G, B));
}