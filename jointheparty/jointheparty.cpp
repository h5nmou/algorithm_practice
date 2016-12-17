//http://koitp.org/problem/PARTY2/read/
/*
문제
삼성고등학교의 기숙사는 N개의 방으로 이루어져 있고, 각 기숙사 방에는 한 명의 학생이 살고 있다. 편의상 각 학생에 1번부터 N번까지 번호를 붙이도록 하자.
하루는 X번 학생의 기숙사 방에서 파티를 열기로 하였다. 각 학생들은 각자의 기숙사 방에서 X번 학생의 기숙사 방까지 갔다가 파티를 마치고 돌아오려 한다.
이 때, 이동하는 경로는 최단 경로로 이동한다. 다만 문제는 각 기숙사를 잇고 있는 M개의 길이 일방통행이라는 점이다.
결국, 그 기숙사 방까지 가는 경로와 그 기숙사 방에서 돌아오는 경로가 다를 수 밖에 없다.
각 길의 정보가 주어졌을 때, 파티에 참석했다가 돌아오는데 소요되는 시간이 가장 긴 학생의 소요 시간을 알아내자.
입력
첫 번째 줄에 학생의 수 N, 길의 수 M, 파티를 여는 기숙사 방에 있는 학생의 번호 X가 주어진다. (1 ≤ N ≤ 50,000, 1 ≤ M ≤ 500,000)
두 번째 줄부터 M개의 줄에 걸쳐 각 길의 정보 s, e, t가 주어진다. s는 일방통행 길이 시작되는 기숙사 방의 번호이고, e는 길이 끝나는 기숙사 방의 번호이다.
t는 그 길을 지나가는데 걸리는 소요 시간이다. 소요 시간은 1 이상 100 이하이다.
출력
첫 번째 줄에 파티에 참석했다가 돌아오는데 소요되는 시간이 가장 긴 학생의 소요 시간을 출력한다.
힌트
예제 입력
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
예제 출력
10
*/

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

long N;//학생수
long M;//길의수
long X;//파티룸

typedef pair<long, long> PAIR;//<거리, 도착지>
vector<PAIR> roomInfo[500001];//X로 갈때 
vector<PAIR> roomInforeverse[500001];//X로 올때 

                                     //X의 방에서 각자의 방으로 가는 길은 원래 간선 정보를 바탕으로 X를 시작점으로 하여 다익스트라를 돌리면 되고 
                                     //각자의 방에서 X의 방으로 오는 길은 원래 간선 정보를 방향을 바꾸서 X를 시작점으로 하여 다익스트라를 돌린다 

long DistanceFromX[500001];
long DistanceToX[500001];

bool visited[500001];

priority_queue<PAIR, vector<PAIR>, greater<PAIR>> MINQ;//각 지점과 그 지점까지의 최단 경로를 가지는 Queue

long MAX(long a, long b) { return (a > b) ? a : b; }
long MIN(long a, long b) { return (a > b) ? b : a; }

void initTable() {
  for (int i = 1; i <= N; i++) {
    DistanceFromX[i] = 99999999;
    DistanceToX[i] = 99999999;
  }
}

void resetTable() {
  for (int i = 1; i <= N; i++) {
    visited[i] = false;
  }
}

void findshortPathToX(long from, long to) {//X로 가는 길 - 방향 바뀐 간선정보로 X에서 임의의 지점으로 다익스트라 돌림. 

  DistanceToX[from] = 0;//출발지까지의 거리는 0
  MINQ.push(PAIR(0, from));

  long current;

  while (MINQ.empty() != true) {//Queue 가 비워질때까지 
    do {
      PAIR info = MINQ.top();
      MINQ.pop();
      current = info.second;
    } while (MINQ.empty() != true && visited[current] == true);//Queue 에서 꺼낸 값이 이미 방문한 곳이면 무시한다. 

    if (visited[current] == true) {
      break;
    }

    for (int size = 0; size < roomInforeverse[current].size(); size++) {//경로정보를 가져와서 거리가 작은 값으로 갱신한다.
      if (DistanceToX[roomInforeverse[current].at(size).second] > DistanceToX[current] + roomInforeverse[current].at(size).first) {//기존 경로값보다 이번 경로값이 작으면 갱신
        DistanceToX[roomInforeverse[current].at(size).second] = DistanceToX[current] + roomInforeverse[current].at(size).first;
        MINQ.push(PAIR(DistanceToX[roomInforeverse[current].at(size).second], roomInforeverse[current].at(size).second));
      }
    }
    visited[current] = true;
  }
}

void findshortPathFromX(long from, long to) {//X에서 돌아오는 길 - 원래 간선정보로 X에서 임의의 지점으로 다익스트라 돌림. 

  DistanceFromX[from] = 0;//출발지까지의 거리는 0
  MINQ.push(PAIR(0, from));

  long current;

  while (MINQ.empty() != true) {//Queue 가 비워질때까지 
    do {
      PAIR info = MINQ.top();
      MINQ.pop();
      current = info.second;
    } while (MINQ.empty() != true && visited[current] == true);//Queue 에서 꺼낸 값이 이미 방문한 곳이면 무시한다. 

    if (visited[current] == true) {
      break;
    }

    for (int size = 0; size < roomInfo[current].size(); size++) {//경로정보를 가져와서 거리가 작은 값으로 갱신한다.
      if (DistanceFromX[roomInfo[current].at(size).second] > DistanceFromX[current] + roomInfo[current].at(size).first) {//기존 경로값보다 이번 경로값이 작으면 갱신
        DistanceFromX[roomInfo[current].at(size).second] = DistanceFromX[current] + roomInfo[current].at(size).first;
        MINQ.push(PAIR(DistanceFromX[roomInfo[current].at(size).second], roomInfo[current].at(size).second));
      }
    }
    visited[current] = true;
  }
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%ld %ld %ld", &N, &M, &X);

  long from, to, time;
  for (int i = 0; i < M; i++) {
    scanf("%ld %ld %ld", &from, &to, &time);
    roomInfo[from].push_back(PAIR(time, to));
    roomInforeverse[to].push_back(PAIR(time, from));
  }

  long MaxTime = 0;
  initTable();

  int destination = X + 1;

  if (destination > N) {
    destination = X - 1;
  }

  findshortPathFromX(X, destination);//원래 간선정보로 X로부터 돌아오는 시간 구하고 
  resetTable();
  findshortPathToX(X, destination);//방향 바뀐 간선정보로 X까지 가는 시간 구한다. 

  for (int i = 1; i <= N; i++) {
    MaxTime = MAX(MaxTime, DistanceFromX[i] + DistanceToX[i]);
  }

  printf("%ld", MaxTime);
}