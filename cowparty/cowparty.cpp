//http://koitp.org/problem/SDS_PRO_4_5/read/
/*문제
N 개 농장의 (편의상 1 ,2 .. , N) 의 대표 암소 한 마리가, X ( 1 <= X <= N) 농장에서 열리는 파티에 참석하려고 한다.
농장들은 단방향의 길들로 연결되어 있으며, 각 길마다 걸어가는데 걸리는 시간이 주어진다.

모든 소들은 파티에 걸어가야 하고 파티가 마친 후에는 자기가 속한 농장으로 돌아와야 한다.
모든 소들은 게을러서 가장 최단시간으로 올수 있는 최적의 길을 선택하려고 한다.

모든 소 들 중에서 농장으로 갔다가 돌아오는 데 가장 많이 걸리는 소의 시간은 얼마인가?

시간제한 : 0.5 초

입력
첫 번째 줄 : 정수 N , M , X 가 주어진다. (1<=N<=1000)는 농장의 수, (1<=M<=N*(N-1))은 도로의 갯수, (1<=X<=N)는 파티가 열리는 농장이다.
두 번재 줄에서 M+1 번째 줄 : i+1 번째 줄은 세 정수 Ai,Bi,Ci 가 주어진다. Ai 에서 Bi 로 가는데 Ti 시간이 소요된다는 것이다.
출력
파티에 참석했다 돌아오는 소 들 중 가장 긴 시간을 출력한다.

힌트
입력 예제
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
출력 예제
10
4 -> 2 ( 3 )

2 -> 1 -> 3 -> 4 (7)

총 거리합은 10이고, 이 때가 가장 긴 경우이다.*/

#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>

using namespace std;
typedef long long int lld;
typedef pair<int, int> PAIR;//거리, 농장

int N, M, X; // N : 농장수 M : 도로갯수 X : 파티가 열리는 농장
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

void searchgopath() {//가는 길을 찾자 간선정보를 뒤집고서 시작을 X로 하면 다익스트라에 의해 가는 길을 찾을 수 있다 
  backFromPartyShortestPath[X] = 0;//시작점까지의 거리는 0
  PQ.push(PAIR(0, X));//시작점의 정보를 넣고 시작한다. 

  int current;

  while (!PQ.empty()) {
    do {//시작점의 정보를 넣고 시작하니까 일단 한번 빼서 처리하고 루프를 탄다.
      current = PQ.top().second;
      if (current == 3) {
        int a = 0;
      }
      PQ.pop();
    } while (!PQ.empty() && backFromPartyVisited[current] == true);//이미 방문한 농장은 무시한다.

    if (backFromPartyVisited[current]) break;

    backFromPartyVisited[current] = true;//방문처리한다.

                                         //해당 농장의 Path 정보를 가져와서 Path로 이어진 농장과의 거리를 갱신한다. 
    for (int i = 0; i < backFromPartyPathInfo[current].size(); i++) {
      //기존 from 에 저장된 length + from 에서 to로 가는 length 가 기존 to에 저장된 length 보다 작으면 갱신한다.
      int newLength = backFromPartyShortestPath[current] + backFromPartyPathInfo[current].at(i).first;
      int oldLength = backFromPartyShortestPath[backFromPartyPathInfo[current].at(i).second];
      int to = backFromPartyPathInfo[current].at(i).second;
      if (newLength < oldLength) {
        backFromPartyShortestPath[to] = newLength;//갱신
      }
      PQ.push(PAIR(backFromPartyShortestPath[to], to));
    }
  }
}

void searchbackpath() {//돌아오는 길을 찾자 원래 주어진 간선정보와 시작을 X로 하면 다익스트라에 의해 오는길을 찾을 수 있다. 
  gotoPartyShortestPath[X] = 0;//시작점까지의 거리는 0
  PQ.push(PAIR(0, X));//시작점의 정보를 넣고 시작한다. 

  int current;

  while (!PQ.empty()) {
    do {//시작점의 정보를 넣고 시작하니까 일단 한번 빼서 처리하고 루프를 탄다.
      current = PQ.top().second;
      PQ.pop();
    } while (!PQ.empty() && gotoPartyVisited[current] == true);//이미 방문한 농장은 무시한다.

    if (gotoPartyVisited[current]) break;

    gotoPartyVisited[current] = true;//방문처리한다.

                                     //해당 농장의 Path 정보를 가져와서 Path로 이어진 농장과의 거리를 갱신한다. 
    for (int i = 0; i < gotoPartyPathinfo[current].size(); i++) {
      //기존 from 에 저장된 length + from 에서 to로 가는 length 가 기존 to에 저장된 length 보다 작으면 갱신한다.
      int newLength = gotoPartyShortestPath[current] + gotoPartyPathinfo[current].at(i).first;
      int oldLength = gotoPartyShortestPath[gotoPartyPathinfo[current].at(i).second];
      int to = gotoPartyPathinfo[current].at(i).second;
      if (newLength < oldLength) {
        gotoPartyShortestPath[to] = newLength;//갱신
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