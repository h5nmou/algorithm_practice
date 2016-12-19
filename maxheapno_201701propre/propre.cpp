#include <stdio.h>
#include <stdlib.h>

using namespace std;
int T;
int N;

long long dpTable[12];
long long MOD = 100000123;

void initTable() {
  for (int i = 0; i < 12; i++) {
    dpTable[i] = -1;
  }
}

long long factorial(int a) {
  if (a == 1) return 1;
  return ((a % MOD) * (factorial(a - 1) % MOD)) % MOD;
}

long long POW(long long a, long long b) {
  if (b == 1) return a;
  if (b == 0) return 1;

  long long  tmp = POW(a, b / 2);
  if (b % 2) return (long long)((long long)((tmp*tmp) % MOD)*a) % MOD;
  else return (long long)(tmp*tmp) % MOD;
}

long long dpFunc(int n) {

  long long &ret = dpTable[n];
  if (ret != -1) {
    return ret;
  }

  long long a = factorial(POW(2, n) + POW(2, n - 1));
  long long b = factorial(3) * factorial(POW(2, n) + POW(2, n - 1) - 3);
  long long c = POW(2, POW(2, n - 1));

  ret = (a * POW(b, MOD - 2)) % MOD;// (a / b) % MOD;
  ret = ((ret % MOD) * (c % MOD)) % MOD; //  (a * b) % MOD

  return ((dpFunc(n - 2) % MOD) * (ret % MOD)) % MOD;
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%d", &T);

  initTable();
  dpTable[0] = 1;
  dpTable[1] = 2;

  for (int t = 1; t <= T; t++) {
    scanf("%d", &N);
    printf("#%d %lld\n", t, dpFunc(N));
  }
}