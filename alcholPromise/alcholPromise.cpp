//http://koitp.org/problem/SDS_PRO_6_6/read/
/*
문제
동현이는 술을 좋아한다.그런데, 동현이는 멍청하게도 같은 날에 여러개의 술 약속을 잡았다.약속을 잡은 모든 사람들은 다들 동현이에게 술을 먹이고 싶어 한다.
각 약속에서 만나는 사람들은 동현이가 1분 늦을 때마다 동현이에게 술을 Di 병씩 마시게 할 것이다.각 약속은 동현이 집에서 Ti 분 거리여서, 
동현이는 약속 장소에 가고 오는데 총 2 * Ti분이 걸리게 된다. (약속 장소에 갈 때는 항상 동현이 집에서 출발한다.) 다행히도, 
오늘의 사정을 아는 사람들은 사람들은 조금의 자비를 베풀어 동현이가 집에서 약속 장소까지 오는데 걸리는 시간 정도는 빼주기로 했다.
동현이는 당연히 잡아놓은 약속들을 반드시 가야만 한다.여러분이 동현이가 술을 적게 마실 수 있도록 가야할 약속 순서를 정해주자.
이 때, 동현이가 가서 벌주를 마시는 시간은 0분이라고 가정하자.그는 술을 엄청 빨리 마시니깐!

입력
첫 번째 줄에 술 약속의 개수 N이 주어진다. (1 ≤ N ≤ 100, 000)
두 번째 줄부터 N개의 줄에 걸쳐 각 약속의 Ti와 Di가 주어진다. (1 ≤ Ti ≤ 2, 000, 000, 1 ≤ Di ≤ 100)

출력
첫 번째 줄에 동현이가 마셔야 할 최소 술병의 수를 출력한다.

입력 예제

6
3 1
2 5
2 3
3 2
4 1
1 6
출력 예제

86
*/

#include <stdio.h>
#include <functional>
#include <vector>
#include <stdlib.h>
#include <queue>

using namespace std;

class PAIR {
public:
  long time;
  long bottle;
  PAIR(long t, long b) : time(t), bottle(b) {};
};

struct PAIRCompare {
  bool operator()(const PAIR &a, const PAIR &b) const{
    //순서를 바꾸고 싶을때 false를 리턴한다.
    //여기서는 뒤에 들어온놈을 먼저 방문했을때가 유리하면 바꿔줘야 한다. 그래야 정렬된 순서대로 방문했을때에 유리하니까....
    //즉 a를 방문했을때에 마셔야 하는 술병의 값이 b를 먼저 방문했을때에 마셔야 하는 술병보다 많으면 바꿔줘야 한다.
    return ((2 * b.time) * a.bottle) < ((2 * a.time) * b.bottle);
  }
};

priority_queue<PAIR, vector<PAIR>, PAIRCompare> promiseQ;

long N = 0;//술약속의 갯수
long totalBottle = 0;
long pastTime = 0;//지금까지 걸린 시간을 저장하는 변수

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%ld", &N);

  for (long i = 0; i < N; i++) {
    long time;
    long bottle;
    scanf("%ld %ld", &time, &bottle);
    PAIR p(time, bottle);
    promiseQ.push(p); 
  }

  while (!promiseQ.empty()) {
    long promiseBottle = promiseQ.top().bottle;
    totalBottle += pastTime * promiseBottle;
    pastTime += 2 * promiseQ.top().time;
    promiseQ.pop();
  }

  printf("%ld", totalBottle);
  return 0;
}