//http://koitp.org/problem/PRIMEPATH/read/

/*
�����̴� ������ SDS�� ���Ǹ� �Ϸ� ����. ������ ��ħ�� ���� �Ͼ�� �Ѵٴ� �δ㰨�� ��� �˶� �ð踦 �غ��Ͽ���. �ֱٿ� ȭ��� �������, �� ������, ���� �Ѹ��� ���� �˶� �ð谡 ������ ������, �����̴� ���Ǹ� ���� �Ӹ��� ��� �� �� �ִ� �˶��� �غ��Ͽ���.

�� �ð��� �ð��� ���� ����, �� �ð��� �Ǿ� �︮�� �����ϸ�, 4�ڸ��� �Ҽ� 2���� ��� �˶� �ð迡 ǥ�õȴ�. ù ��° ���� �ִ� ���� ���ڸ� ������ �� �ְ� �Ǿ��ִ�. �׷� ���� �˶��� ���� ����� �����ϴ�. ù ��° ���� �ִ� �Ҽ��� �� ��° ���� �ִ� �Ҽ��� �����ϸ� �ȴ�. �̶�, �ѹ��� ���ڸ��� ������ �� �ְ�, ���ڸ��� �����Ͽ��� ��, ����� ���� �Ҽ��̾�� �Ѵ�. ���� 4�ڸ� �Ҽ��̱� ������, ��� �߰����� 4�ڸ��� �����ؾ��Ѵ�. (��, 1000�̻��� �Ҽ�) �����̴� �˶��� ��� �︮�� ���� �ȱ� ������, �ִ��� ������ �˶��� ���� �;��Ѵ�. �����̸� ���� ��� �ϸ� �ּ����� �ܰ�� ù ��° �Ҽ��� �� ��° �Ҽ��� ������ �� �ִ��� ���Ͻÿ�.

���� �� 1033�̶�� ���� 8179�� �����Ѵٸ�, 1033 1733 3733 3739 3779 8779 8179�� ������ ������ �����ϴ�.

�Է�
ù ��° �ٿ� �׽�Ʈ ���̽��� �� T�� �־�����.

�� �׽�Ʈ ���̽��� ù ��° �ٿ� ��� �˶� �ð迡 ���� �ִ� �� ���� �Ҽ��� �������� �и��Ǿ� �־�����. (1,000 �� �Ҽ� �� 9,999)

���
�� �׽�Ʈ ���̽����� ù ��° �ٿ� ù ��° �Ҽ��� �� ��° �Ҽ��� �����ϴ� �ּ����� �ܰ���� ����Ѵ�.

��Ʈ
���� �Է�

3
1033 8179
1373 8017
1033 1033
���� ���

6
7
0
*/

#include <stdio.h>
#include <functional>
#include <vector>

using namespace std;

int INF = 9999999;
int MIN(int a, int b) { return (a > b) ? b : a; }
int testNum;
int fromPrime;//1,000 �� �Ҽ� �� 9,999
int toPrime;//1,000 �� �Ҽ� �� 9,999

int dpTable[10000][4][10];//[�����ڿ���][�ش��ڸ�����][�� ���ڷ� �ٲ�������] ��ǥ �Ҽ������� �ּ� ��ȯ Ƚ��
int isChecked[10000][4][10][1];//�̹� üũ�� ���۵� �������� ����

bool isPrimeNum(int n) {  
  if (n <= 1) return false;//1�� �Ҽ��� �ƴϴ�
  if (n == 2) return false;//2�� ¦���� �����ϰ� �Ҽ���

  //2�� ������ ��� ¦���� �Ҽ��� �ƴϴ�
  if (n % 2 == 0) return false;

  //2�� ���������� 3�̻��� ��� Ȧ���� ��������.
  int sqrtn = int(sqrt(n));//Ȧ���� �������� ���Ѵ� int �� �Ͽ����� �����ٺ��� ���� ������ ���ð��̴� �� ���ڱ��� �����ϸ鼭 ���������� �Ҽ��� �ƴϴ�. 
  for (int div = 3; div <= sqrtn; div += 2) {
    if (n % div == 0) return false;
  }

  return true;
}

void initTable() {
  for (int i = 0; i < 10000; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 10; k++) {
        dpTable[i][j][k] = INF;
        isChecked[i][j][k][0] = 0;
      }
    }
  }
}

int DPFunc(int previousPrime, int position, int changeNo) {//previousPrime : �� ������ : position �� �ش��ϴ� �ڸ����� ���ڸ� changeNo �ιٲ������� ret : ��ǥ �Ҽ��� �����ϴ� �ּ� Ƚ��
  isChecked[previousPrime][position][changeNo][0] = 1;

  //�������

  //Memoization �� �� ret
  int &ret = dpTable[previousPrime][position][changeNo];

  if (ret != INF) {
    return ret;
  }

  //�ش� �ڸ��� ���ڸ� �ٲٰ� DP �� ���� ����. //�̹� target �Ҽ��� ���ڰ� ���� �ڸ����� �ٲ��ʿ䰡 ����. 
  int nextPrimeNum = 0;

  switch(position) {
    case 0:
      if (changeNo == 0) return ret;//ù��° �ڸ����� 0�� �ɼ� ����.//���� ���� (�߰����� 4�ڸ������� ��)
      nextPrimeNum = previousPrime % 1000 + changeNo * 1000;
      if (toPrime / 1000 == previousPrime / 1000) return ret = INF;
      break;
    case 1:
      nextPrimeNum = (previousPrime / 1000) * 1000 + (previousPrime % 100) + changeNo * 100;
      if ((toPrime % 1000) / 100 == (previousPrime / 1000) / 100) return ret = INF;
      break;
    case 2:
      nextPrimeNum = (previousPrime / 100) * 100 + previousPrime  % 10 + changeNo * 10;
      if ((toPrime % 100) / 10 == (previousPrime / 100) / 10) return ret = INF;
      break;
    case 3:
      nextPrimeNum = (previousPrime / 10) * 10 + changeNo;
      if (toPrime % 10 == previousPrime % 10) return ret = INF;
      break;
  }

  for (int j = 0; j < 4; j++) {//�ڸ����� �ٲ㺻��. 
    if (position == j) continue;

    for (int k = 0; k < 10; k++) {
      if (isChecked[nextPrimeNum][j][k][0] == 1) {
        continue;
      }

      if (!isPrimeNum(previousPrime)) {
        continue;
      }

      ret = MIN(ret, DPFunc(nextPrimeNum, j, k));
    }
  }

  return ret += 1;
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  scanf("%d", &testNum);

  for (int i = 0; i < testNum; i++) {
    initTable();
    scanf("%d %d", &fromPrime, &toPrime);

    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 10; k++) {
        dpTable[toPrime][j][k] = 0;
      }
    }

    int retVal = INF;

    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 10; k++) {
        retVal = MIN(retVal, DPFunc(fromPrime, j, k));
      }
    }

    printf("%d\n", retVal);
  }
}

//��� �Ҽ��� ������ ���� �ٲ�� �ִ� ��츦 ��η� ��Ÿ���� ���ͽ�Ʈ��� Ǯ���� ���� ��.