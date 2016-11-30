//SDS_PRO_1_2 ADJACENTBIT
//http://www.koitp.org/problem/ICPC_2009GNY_ADJACENTBIT/read/
//���� ��ȹ���� �̿��� ������ ��Ʈ���� K �� ���� ���� S�� ���� ���ϱ� 

#include <stdio.h>
#include <memory>

int testCase = 0;//1 �� T �� 1,000
int testNum = 0;
int N = 0;//������ ũ�� 
int K = 0;//������ ��Ʈ�� ��
int dpTable[101][101][2];//[����ũ��][������Ʈ��][0,1]

void initTable() {
  //memset(dpTable, -1, sizeof(dpTable));//-1�� �ʱ�ȭ �Ѵ�. 
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

int DPFunc(int remainSpace, int remainK, int startBit) {//�ڸ���, ������Ʈ��, ���� ��Ʈ //���� ��Ʈ�� bit�϶��� �ڸ���ũ���� �������� ������Ʈ���� ������ ������ ����

  if (remainSpace == 2 && remainK == 0 && startBit == 1) {
    int a = 0;
  }
  //�������
  if (remainSpace == 0 || remainSpace == remainK) {
    return 0;
  }

  //����Ȱ� ���� 
  int& retVal = dpTable[remainSpace][remainK][startBit];
  if (retVal != -1) {
    return retVal;
  }

  //�ڸ����� �׻� �پ��� 
  //���ۺ�Ʈ�� 0�ΰ�� remainSpace -1 �ڸ����� 0�� ��� 
  if (startBit == 0) {
    retVal = DPFunc(remainSpace - 1, remainK, 0) + DPFunc(remainSpace - 1, remainK, 1);
  }

  //���ۺ�Ʈ�� 1�ΰ�� 
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

    //�ʱⰪ �־��ֱ�
    //����ũ�Ⱑ 1�̶�� ��� 0 -> initTable()
    dpTable[2][0][0] = 2;
    dpTable[2][0][1] = 1;
    dpTable[2][1][0] = 0;
    dpTable[2][1][1] = 1;

    //do
    printf("%d %d\n", testNum, DPFunc(N, K, 0) + DPFunc(N, K, 1));

    //printTable();
  }
}