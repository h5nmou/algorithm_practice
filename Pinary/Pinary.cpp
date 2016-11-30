//SDS_PRO_1_1 PINARY
//http://www.koitp.org/problem/PINARY/read/
//������ȹ���� �̿��� ��ģ�� ���� ã��

#include <stdio.h>

int N;
long long dpTable[91];

void initTable() {
  for (int i = 0; i < 91; i++) {
    dpTable[i] = -1;
  }
}

long dpFunc(int n) {//n:�ڸ��� //�ڸ��� n�� ���� ��ģ�� ����
  //���� ��� ���� ó�� 

  //memorization �Ȱ� ������ ����
  long long& dpVal = dpTable[n];
  if (dpVal != -1) {
    return dpVal;
  }

  return dpVal = dpFunc(n - 2) + dpFunc(n - 1);
}
int main() {
  freopen("sample_input.txt", "r", stdin);
  scanf("%d", &N);
  initTable();//�ʿ信 ���� DPTable �ʱ�ȭ
  dpTable[1] = 1;
  dpTable[2] = 1;
  printf("%lld", dpFunc(N));
  return 0;
}