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
#include <queue>
#include <math.h>

using namespace std;

int INF = 9999999;
typedef pair<int, int> PAIR;

int testNum;
int fromPrime;//1,000 �� �Ҽ� �� 9,999
int toPrime;//1,000 �� �Ҽ� �� 9,999

vector<PAIR> primeNumMap[10000];
priority_queue<PAIR, vector<PAIR>, greater<PAIR>> minQ;

bool primeNumCheck[10000];
bool checked[10000];
int minTouchnum[10000];

bool isPrimeNum(int n) {  //�ش� ���� �Ҽ����� �˻�
  if (n <= 1) return false;//1�� �Ҽ��� �ƴϴ�
  if (n == 2) return false;//2�� ¦���� �����ϰ� �Ҽ���
  if (n == 5) return true;//5�� 1�� �ڸ��� 5�� ���� �����ϰ� �Ҽ���

  //2�� ������ ��� ¦���� �Ҽ��� �ƴϴ�
  if (n % 2 == 0) return false;
  if (n % 5 == 0) return false;//5�� �����ϰ� 1�� �ڸ��� 5�� ���� �Ҽ��� �ƴϴ�.

  //2�� ���������� 3�̻��� ��� Ȧ���� ��������.
  int sqrtn = int(sqrt(n));//Ȧ���� �������� ���Ѵ� int �� �Ͽ����� �����ٺ��� ���� ������ ���ð��̴� �� ���ڱ��� �����ϸ鼭 ���������� �Ҽ��� �ƴϴ�. 
  for (int div = 3; div <= sqrtn; div += 2) {
    if (n % div == 0) return false;
  }

  return true;
}

bool checktwoOfPrimeNum(int a, int b) {//�μҼ��� ���ڸ����� ���̰� ������ �˻�
  //���ڸ����� ���̳��� ���� �Ǵ�
  int count = 0;

  if (a / 1000 == b /1000) {//õ�ڸ� ������
    count++;
  }

  if ((a % 1000) / 100 == (b % 1000) / 100) {//���ڸ� ������
    count++;
  }

  if ((a % 100) / 10 == (b % 100) / 10) {//���ڸ� ������
    count++;
  }

  if (a % 10 == b % 10) {//���ڸ� ������
    count++;
  }

  if (count == 3) {
    return true;
  }
  else {
    return false;
  }
}

void initTable() {
  for (int i = 0; i < 10000; i++) {
    checked[i] = false;
    minTouchnum[i] = INF;
  }
}

void initMap() {//������ �Ҽ��� ���� ���ڸ����� ���̰� ���� �ٸ� �Ҽ������ ���ἱ�� ����� �ش� 
  for (int i = 0; i < 10000; i++) {
    if (i < 1000) {
      primeNumCheck[i] = false;
      continue;
    }

    if (isPrimeNum(i)) {//�Ҽ��̸�
      primeNumCheck[i] = true;
    }
    else {
      primeNumCheck[i] = false;
    }
  }

  for (int j = 0; j < 10000; j++) {
    if (primeNumCheck[j] == true) {
      for (int k = 0; k < 10000; k++) {
        if (primeNumCheck[k] == true) {
          if (checktwoOfPrimeNum(j, k)) {//�� �ڸ��� ���̰� ���� �Ҽ��� ���
            primeNumMap[j].push_back(PAIR(1, k));
          }
        }
      }
    }
  }
}

void findAnswer() {//���ͽ�Ʈ�� �˰��� (�� ���������� ��ΰ��� ���� 1)

  minTouchnum[fromPrime] = 0;//������������ �Ÿ��� 0
  minQ.push(PAIR(0, fromPrime));//MINQ�� �������� �ְ� �����Ѵ�

  int curr;
  while (!minQ.empty()) {//Q�� �������� 
    do {
      curr = minQ.top().second;
      minQ.pop();
    } while (!minQ.empty() && checked[curr]);//Queue ���� ���� ���� �̹� �湮�� ���̸� �����Ѵ�

    if (checked[curr] == true) break;//Queue �� empty ���� �������� ����� Ż��
    checked[curr] = true;//���� �湮

    for (int i = 0; i < primeNumMap[curr].size(); i++) {//�ش� ������ ����� ������ ��ȸ�ϸ� ��ΰ��� �������ش�.
      int next = primeNumMap[curr].at(i).second;
      if (minTouchnum[next] > minTouchnum[curr]  + 1) {//���� ���� ���� ���� ������ ������ ����
        minTouchnum[next] = minTouchnum[curr] + 1;
      }
      minQ.push(PAIR(minTouchnum[next], next));//���������� �Ÿ��� ���� ��ȣ�� Pair�� ����� Queue �� �־��ش�. 
    }
  }

  //MINQ ���� ������ ������������ �������� ���ʴ�� �湮������ �ʴ´� �׷��� ��¶�� Queue �� ������� �ȴٴ� ���� �� �̻� ������
  //�������� ������ ���ٴ� ���� �ǹ��ϹǷ� ���� ��� ������ ������ ����.
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  scanf("%d", &testNum);
  initMap();
  for (int i = 0; i < testNum; i++) {
    scanf("%d %d", &fromPrime, &toPrime);
    initTable();
    findAnswer();
    printf("%d\n", minTouchnum[toPrime]);

    printf("\n1 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 1) {
        printf("%d ", i);
      }
    }
    printf("\n2 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 2) {
        printf("%d ", i);
      }
    }
    printf("\n3 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 3) {
        printf("%d ", i);
      }
    }
    printf("\n4 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 4) {
        printf("%d ", i);
      }
    }
    printf("\n5 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 5) {
        printf("%d ", i);
      }
    }
    printf("\n6 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 6) {
        printf("%d ", i);
      }
    }
    printf("\n7 =====================\n");
    for (int i = 0; i < 10000; i++) {
      if (minTouchnum[i] == 7) {
        printf("%d ", i);
      }
    }
  }
}