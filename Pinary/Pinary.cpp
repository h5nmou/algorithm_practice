//SDS_PRO_1_1 PINARY
//http://www.koitp.org/problem/PINARY/read/
//동적계획법을 이용한 이친수 갯수 찾기

#include <stdio.h>

int N;
long long dpTable[91];

void initTable() {
  for (int i = 0; i < 91; i++) {
    dpTable[i] = -1;
  }
}

long dpFunc(int n) {//n:자릿수 //자릿수 n일 때의 이친수 갯수
  //기저 사례 먼저 처리 

  //memorization 된것 있으면 리턴
  long long& dpVal = dpTable[n];
  if (dpVal != -1) {
    return dpVal;
  }

  return dpVal = dpFunc(n - 2) + dpFunc(n - 1);
}
int main() {
  freopen("sample_input.txt", "r", stdin);
  scanf("%d", &N);
  initTable();//필요에 따른 DPTable 초기화
  dpTable[1] = 1;
  dpTable[2] = 1;
  printf("%lld", dpFunc(N));
  return 0;
}