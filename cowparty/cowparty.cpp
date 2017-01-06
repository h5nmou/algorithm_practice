//http://koitp.org/problem/SDS_PRO_4_5/read/
/*����
N �� ������ (���ǻ� 1 ,2 .. , N) �� ��ǥ �ϼ� �� ������, X ( 1 <= X <= N) ���忡�� ������ ��Ƽ�� �����Ϸ��� �Ѵ�.
������� �ܹ����� ���� ����Ǿ� ������, �� �渶�� �ɾ�µ� �ɸ��� �ð��� �־�����.

��� �ҵ��� ��Ƽ�� �ɾ�� �ϰ� ��Ƽ�� ��ģ �Ŀ��� �ڱⰡ ���� �������� ���ƿ;� �Ѵ�.
��� �ҵ��� �������� ���� �ִܽð����� �ü� �ִ� ������ ���� �����Ϸ��� �Ѵ�.

��� �� �� �߿��� �������� ���ٰ� ���ƿ��� �� ���� ���� �ɸ��� ���� �ð��� ���ΰ�?

�ð����� : 0.5 ��

�Է�
ù ��° �� : ���� N , M , X �� �־�����. (1<=N<=1000)�� ������ ��, (1<=M<=N*(N-1))�� ������ ����, (1<=X<=N)�� ��Ƽ�� ������ �����̴�.
�� ���� �ٿ��� M+1 ��° �� : i+1 ��° ���� �� ���� Ai,Bi,Ci �� �־�����. Ai ���� Bi �� ���µ� Ti �ð��� �ҿ�ȴٴ� ���̴�.
���
��Ƽ�� �����ߴ� ���ƿ��� �� �� �� ���� �� �ð��� ����Ѵ�.

��Ʈ
�Է� ����
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
��� ����
10
4 -> 2 ( 3 )

2 -> 1 -> 3 -> 4 (7)

�� �Ÿ����� 10�̰�, �� ���� ���� �� ����̴�.*/

#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>

using namespace std;
typedef long long int lld;
typedef pair<int, int> PAIR;//�Ÿ�, ����

int N, M, X; // N : ����� M : ���ΰ��� X : ��Ƽ�� ������ ����
vector<PAIR> backFromPartyPathInfo[1001];
vector<PAIR> gotoPartyPathinfo[1001];
bool backFromPartyVisited[1001];
bool gotoPartyVisited[1001];
int backFromPartyShortestPath[1001];
int gotoPartyShortestPath[1001];
priority_queue<PAIR, vector<PAIR>, greater<PAIR>> PQ;
int MAX(int a, int b) { return (a > b) ? a : b; }

void initTable() {
  for (int i = 0; i < 1001; i++) {
    backFromPartyVisited[i] = false;
    gotoPartyVisited[i] = false;
    backFromPartyShortestPath[i] = 9999999;
    gotoPartyShortestPath[i] = 9999999;
  }
}

void searchgopath() {//���� ���� ã�� ���������� ������ ������ X�� �ϸ� ���ͽ�Ʈ�� ���� ���� ���� ã�� �� �ִ� 
  backFromPartyShortestPath[X] = 0;//������������ �Ÿ��� 0
  PQ.push(PAIR(0, X));//�������� ������ �ְ� �����Ѵ�. 

  int current;

  while (!PQ.empty()) {
    do {//�������� ������ �ְ� �����ϴϱ� �ϴ� �ѹ� ���� ó���ϰ� ������ ź��.
      current = PQ.top().second;
      if (current == 3) {
        int a = 0;
      }
      PQ.pop();
    } while (!PQ.empty() && backFromPartyVisited[current] == true);//�̹� �湮�� ������ �����Ѵ�.

    if (backFromPartyVisited[current]) break;

    backFromPartyVisited[current] = true;//�湮ó���Ѵ�.

                                         //�ش� ������ Path ������ �����ͼ� Path�� �̾��� ������� �Ÿ��� �����Ѵ�. 
    for (int i = 0; i < backFromPartyPathInfo[current].size(); i++) {
      //���� from �� ����� length + from ���� to�� ���� length �� ���� to�� ����� length ���� ������ �����Ѵ�.
      int newLength = backFromPartyShortestPath[current] + backFromPartyPathInfo[current].at(i).first;
      int oldLength = backFromPartyShortestPath[backFromPartyPathInfo[current].at(i).second];
      int to = backFromPartyPathInfo[current].at(i).second;
      if (newLength < oldLength) {
        backFromPartyShortestPath[to] = newLength;//����
      }
      PQ.push(PAIR(backFromPartyShortestPath[to], to));
    }
  }
}

void searchbackpath() {//���ƿ��� ���� ã�� ���� �־��� ���������� ������ X�� �ϸ� ���ͽ�Ʈ�� ���� ���±��� ã�� �� �ִ�. 
  gotoPartyShortestPath[X] = 0;//������������ �Ÿ��� 0
  PQ.push(PAIR(0, X));//�������� ������ �ְ� �����Ѵ�. 

  int current;

  while (!PQ.empty()) {
    do {//�������� ������ �ְ� �����ϴϱ� �ϴ� �ѹ� ���� ó���ϰ� ������ ź��.
      current = PQ.top().second;
      PQ.pop();
    } while (!PQ.empty() && gotoPartyVisited[current] == true);//�̹� �湮�� ������ �����Ѵ�.

    if (gotoPartyVisited[current]) break;

    gotoPartyVisited[current] = true;//�湮ó���Ѵ�.

                                     //�ش� ������ Path ������ �����ͼ� Path�� �̾��� ������� �Ÿ��� �����Ѵ�. 
    for (int i = 0; i < gotoPartyPathinfo[current].size(); i++) {
      //���� from �� ����� length + from ���� to�� ���� length �� ���� to�� ����� length ���� ������ �����Ѵ�.
      int newLength = gotoPartyShortestPath[current] + gotoPartyPathinfo[current].at(i).first;
      int oldLength = gotoPartyShortestPath[gotoPartyPathinfo[current].at(i).second];
      int to = gotoPartyPathinfo[current].at(i).second;
      if (newLength < oldLength) {
        gotoPartyShortestPath[to] = newLength;//����
      }
      PQ.push(PAIR(gotoPartyShortestPath[to], to));
    }
  }
}


int main() {
  freopen("sample_input.txt", "r", stdin);

  initTable();

  scanf("%d %d %d", &N, &M, &X);

  for (int i = 0; i < M; i++) {
    int from, to, length;
    scanf("%d %d %d", &from, &to, &length);
    backFromPartyPathInfo[from].push_back(PAIR(length, to));
    gotoPartyPathinfo[to].push_back(PAIR(length, from));
  }

  searchbackpath();
  searchgopath();

  int ret = -1;
  for (int i = 1; i <= N; i++) {
    if (i == X) {
      continue;
    }
    ret = MAX(ret, backFromPartyShortestPath[i] + gotoPartyShortestPath[i]);
  }
  printf("%d", ret);
}