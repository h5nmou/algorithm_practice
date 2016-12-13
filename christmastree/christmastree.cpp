//https://www.acmicpc.net/problem/1234
/*
����
���ν��� ������ ũ����������� �����ؼ�, ũ�������� Ʈ���� ������� �Ѵ�. Ʈ���� N���� ������ �̷���� �ִ�. ���������� ����1, ... ���� N�̴�. ��, �ν��̴� ����, �Ķ�, �ʷϻ��� �峭���� ������ �ִ�. �׸��� �ν��̴� �� �峭���� ������ ��Ģ�� ���ؼ� ����Ϸ��� �Ѵ�.

���� K���� �� K���� �峭���� �־�� �Ѵ�. ��, �� ������ �������� ������ ���� ������, �� ���� �峭���� ���� ���� ���ƾ� �Ѵ�. ���� ���, ���� 3�� �峭���� �������� �� ��, ���� 2, �Ķ� 1�� ���� ������, ������ �Ķ��� ���� �ٸ��� ������ �ȵȴ�. ������, ���� 4�� ���� 2, �Ķ� 2�� ���� ������, �����ϴ�.

N��, �峭���� ���� �־��� ��, Ʈ���� ����ϴ� ����� ���� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù° �ٿ� Ʈ���� ũ�� N, ������ ����, �ʷ��� ����, �Ķ��� ������ �־�����. N�� 10���� �۰ų� ����. ����, �ʷ�, �Ķ��� ������ 0���� ũ�ų� ����, 100���� �۰ų� ����.

���
ù° �ٿ� ����� ���� ����Ѵ�. �� ���� int������ �Ѿ�� long long�����̰�, ���� �־��� �峭������ Ʈ���� ����� �� ������ 0�� ����Ѵ�.
*/
#include <stdio.h>
#include <stdlib.h>
#include <functional>

using namespace std;

//�ߺ��Ǵ� ���Ұ� �ִ� �迭�� �����ϴ� ����� ��
//���� ��� a�� b�� ������ N�迭�� ä��� ����� ���� a,a,b,b,b �� ��� a = 2, b = 3, N = 5
//5!/2!*3! �̴�.

long long int factorial(int n) {
  if (n == 0 || n == 1) return 1;
  return n*factorial(n - 1);
}

int N, R, G, B;

long long int DPTable[11][101][101][101];
long long int bojoMatrix[4][11];//[���� ������ ������][���� ĭ�� ä��� �ִ� ����� ��] �� �� ������ ��� Ƚ���� ���ƾ� �Ѵ�.

void initTable() {
  //memset(DPTable, -1, sizeof(DPTable));//�޸� �ʱ�ȭ
  //memset(bojoTable, -1, sizeof(bojoTable));//�޸� �ʱ�ȭ
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

long long int DPFunc(int n, int r, int g, int b) {//n���� ������ r,g,b�� ������ ä��� �ִ� ����� ��
  //������� ó��
  if (r < 0 || g < 0 || b < 0) return 0;//������ �ʰ��ؼ� ����ϴ� ���� ���°����� ó��
  if (n == 0) return 1;//1�������� ������ �ϳ��� ��찡 �ְ� ��

  long long int &ret = DPTable[n][r][g][b];
  if (ret != -1) return ret;

  ret = 0;

  //N������ �ϳ��� ������ ä��� ��� 
  ret += DPFunc(n - 1, r - n, g, b) * bojoMatrix[1][n];//R
  ret += DPFunc(n - 1, r, g - n, b) * bojoMatrix[1][n];//G
  ret += DPFunc(n - 1, r, g , b - n) * bojoMatrix[1][n];//B

  //N������ �ΰ��� ������ ä��� ��� 
  if (n % 2 == 0) {
    ret += DPFunc(n - 1, r - (n / 2), g - (n / 2), b) * bojoMatrix[2][n];//R,G
    ret += DPFunc(n - 1, r - (n / 2), g, b - (n / 2)) * bojoMatrix[2][n];//R,B
    ret += DPFunc(n - 1, r, g - (n / 2), b - (n / 2)) * bojoMatrix[2][n];//G,B
  }

  //N������ ������ ������ ä��� ���
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