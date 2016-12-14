//http://koitp.org/problem/PARTY2/read/
/*
����
�Ｚ����б��� ������ N���� ������ �̷���� �ְ�, �� ����� �濡�� �� ���� �л��� ��� �ִ�. ���ǻ� �� �л��� 1������ N������ ��ȣ�� ���̵��� ����.
�Ϸ�� X�� �л��� ����� �濡�� ��Ƽ�� ����� �Ͽ���. �� �л����� ������ ����� �濡�� X�� �л��� ����� ����� ���ٰ� ��Ƽ�� ��ġ�� ���ƿ��� �Ѵ�.
�� ��, �̵��ϴ� ��δ� �ִ� ��η� �̵��Ѵ�. �ٸ� ������ �� ����縦 �հ� �ִ� M���� ���� �Ϲ������̶�� ���̴�.
�ᱹ, �� ����� ����� ���� ��ο� �� ����� �濡�� ���ƿ��� ��ΰ� �ٸ� �� �ۿ� ����.

�� ���� ������ �־����� ��, ��Ƽ�� �����ߴٰ� ���ƿ��µ� �ҿ�Ǵ� �ð��� ���� �� �л��� �ҿ� �ð��� �˾Ƴ���.

�Է�
ù ��° �ٿ� �л��� �� N, ���� �� M, ��Ƽ�� ���� ����� �濡 �ִ� �л��� ��ȣ X�� �־�����. (1 �� N �� 50,000, 1 �� M �� 500,000)

�� ��° �ٺ��� M���� �ٿ� ���� �� ���� ���� s, e, t�� �־�����. s�� �Ϲ����� ���� ���۵Ǵ� ����� ���� ��ȣ�̰�, e�� ���� ������ ����� ���� ��ȣ�̴�.
t�� �� ���� �������µ� �ɸ��� �ҿ� �ð��̴�. �ҿ� �ð��� 1 �̻� 100 �����̴�.

���
ù ��° �ٿ� ��Ƽ�� �����ߴٰ� ���ƿ��µ� �ҿ�Ǵ� �ð��� ���� �� �л��� �ҿ� �ð��� ����Ѵ�.

��Ʈ
���� �Է�

4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
���� ���

10
*/

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

long N;//�л���
long M;//���Ǽ�
long X;//��Ƽ��

typedef pair<long, long> PAIR;//<�Ÿ�, ������>
vector<PAIR> roomInfo[500001];
long Distance[500001];
bool visited[500001];

priority_queue<PAIR, vector<PAIR>, greater<PAIR>> MINQ;//�� ������ �� ���������� �ִ� ��θ� ������ Queue

long MAX(long a, long b) { return (a > b) ? a : b; }
long MIN(long a, long b) { return (a > b) ? b : a; }

void initTable() {
  for (int i = 1; i <= N; i++) {
    Distance[i] = 99999999;
    visited[i] = false;
  }
}

long findshortPath(long from, long to) {

  Distance[from] = 0;//����������� �Ÿ��� 0
  MINQ.push(PAIR(0, from));

  long current;

  while (MINQ.empty() != true) {//Queue �� ����������� 
    do {
      PAIR info = MINQ.top();
      MINQ.pop();
      current = info.second;
    } while (MINQ.empty() != true && visited[current] == true);//Queue ���� ���� ���� �̹� �湮�� ���̸� �����Ѵ�. 

    if (visited[current] == true) {
      break;
    }

    for (int size = 0; size < roomInfo[current].size(); size++) {//��������� �����ͼ� �Ÿ��� ���� ������ �����Ѵ�.
      if (Distance[roomInfo[current].at(size).second] > Distance[current] + roomInfo[current].at(size).first) {//���� ��ΰ����� �̹� ��ΰ��� ������ ����
        Distance[roomInfo[current].at(size).second] = Distance[current] + roomInfo[current].at(size).first;
        MINQ.push(PAIR(Distance[roomInfo[current].at(size).second], roomInfo[current].at(size).second));
      }
    }
    visited[current] = true;
  }

  return Distance[to];
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%ld %ld %ld", &N, &M, &X);

  long from, to, time;
  for (int i = 0; i < M; i++) {
    scanf("%ld %ld %ld", &from, &to, &time);
    roomInfo[from].push_back(PAIR(time, to));
  }

  long MaxTime = 0;
  long resulttoTo = 0;//���±�
  long resulttoFrom = 0;//���ƿ��±�

  initTable();
  for (int fromRoom = 1; fromRoom <= N; fromRoom++) {
    resulttoTo = findshortPath(fromRoom, X);
    initTable();//����
    resulttoFrom = findshortPath(X, fromRoom);
    initTable();
    MaxTime = MAX(MaxTime, resulttoTo + resulttoFrom);
  }

  printf("%ld", MaxTime);
}