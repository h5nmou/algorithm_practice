//https://www.acmicpc.net/problem/1234

#include <stdio.h>
#include <stdlib.h>
#include <functional>

int N, R, G, B;

long long int DPTable[11][101][101][101];
long long int bojoTable[4][11];//[���� ������ ������][���� ĭ�� ä��� �ִ� ����� ��] �� �� ������ ��� Ƚ���� ���ƾ� �Ѵ�.

long long int makebojoTable(int colorNo, int section) {

}

long long int DPFunc(int n, int r, int g, int b) {//n���� ������ r,g,b�� ������ ä��� �ִ� ����� ��
  //������� ó��
  if (r < 0 || g < 0 || b < 0) return 0;//������ �ʰ��ؼ� ����ϴ� ���� ���°����� ó��
  if (n == 0) return 1;//1�������� ������ �ϳ��� ��찡 �ְ� ��

  long long int &ret = DPTable[n][r][g][b];
  if (ret != -1) return ret;

  ret = 0;

  //N������ �ϳ��� ������ ä��� ��� 
  ret += DPFunc(n - 1, r - n, g, b);//R
  ret += DPFunc(n - 1, r, g - n, b);//G
  ret += DPFunc(n - 1, r, g , b - n);//B

  //N������ �ΰ��� ������ ä��� ��� 
  if (n % 2 == 0) {
    ret += DPFunc(n - 1, r - (n / 2), g - (n / 2), b);//R,G
    ret += DPFunc(n - 1, r - (n / 2), g, b - (n / 2));//R,B
    ret += DPFunc(n - 1, r, g - (n / 2), b - (n / 2));//G,B
  }

  //N������ ������ ������ ä��� ���
  if (n % 3 == 0) {
    ret += DPFunc(n - 1, r - (n / 3), g - (n / 3), b - (n / 3));//R,G,B
  }

  return ret;
}

int main(){
  freopen("sample_input.txt", "r", stdin);
  memset(DPTable, -1, sizeof(DPTable));//�޸� �ʱ�ȭ
  memset(bojoTable, -1, sizeof(bojoTable));//�޸� �ʱ�ȭ

  scanf("%d %d %d %d", &N, &R, &G, &B);

  makebojoTable();

  printf("%lld", DPFunc(N, R, G, B));
}