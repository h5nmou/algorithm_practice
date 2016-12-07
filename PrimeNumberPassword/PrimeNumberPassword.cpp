//http://koitp.org/problem/PRIMEPATH/read/

/*
형석이는 다음날 SDS에 강의를 하러 간다. 하지만 아침에 일찍 일어나야 한다는 부담감에 고급 알람 시계를 준비하였다. 최근에 화장실 사진찍기, 뺨 때리기, 냄새 뿌리기 등의 알람 시계가 나오고 있지만, 형석이는 강의를 위해 머리를 써야 끌 수 있는 알람을 준비하였다.

이 시계의 시간을 맞춰 놓고, 그 시간이 되어 울리기 시작하면, 4자리의 소수 2개가 고급 알람 시계에 표시된다. 첫 번째 적혀 있는 수는 숫자를 변경할 수 있게 되어있다. 그럼 이제 알람을 끄는 방법은 간단하다. 첫 번째 적혀 있는 소수를 두 번째 적혀 있는 소수로 변경하면 된다. 이때, 한번에 한자리만 변경할 수 있고, 한자리를 변경하였을 때, 변경된 수는 소수이어야 한다. 또한 4자리 소수이기 때문에, 경로 중간에도 4자리를 유지해야한다. (즉, 1000이상의 소수) 형석이는 알람이 계속 울리는 것이 싫기 때문에, 최대한 빠르게 알람을 끄고 싶어한다. 형석이를 도와 어떻게 하면 최소한의 단계로 첫 번째 소수를 두 번째 소수로 변경할 수 있는지 구하시오.

예를 들어서 1033이라는 수를 8179로 변경한다면, 1033 1733 3733 3739 3779 8779 8179의 순서로 변경이 가능하다.

입력
첫 번째 줄에 테스트 케이스의 수 T가 주어진다.

각 테스트 케이스의 첫 번째 줄에 고급 알람 시계에 적혀 있는 두 개의 소수가 공백으로 분리되어 주어진다. (1,000 ≤ 소수 ≤ 9,999)

출력
각 테스트 케이스마다 첫 번째 줄에 첫 번째 소수를 두 번째 소수로 변경하는 최소한의 단계수를 출력한다.

힌트
예제 입력

3
1033 8179
1373 8017
1033 1033
예제 출력

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
int fromPrime;//1,000 ≤ 소수 ≤ 9,999
int toPrime;//1,000 ≤ 소수 ≤ 9,999

vector<PAIR> primeNumMap[10000];
priority_queue<PAIR, vector<PAIR>, greater<PAIR>> minQ;

bool primeNumCheck[10000];
bool checked[10000];
int minTouchnum[10000];

bool isPrimeNum(int n) {  //해당 수가 소수인지 검사
  if (n <= 1) return false;//1은 소수가 아니다
  if (n == 2) return false;//2는 짝수중 유일하게 소수다
  if (n == 5) return true;//5는 1의 자리가 5인 수중 유일하게 소수다

  //2를 제외한 모든 짝수는 소수가 아니다
  if (n % 2 == 0) return false;
  if (n % 5 == 0) return false;//5를 제외하고 1의 자리가 5인 수는 소수가 아니다.

  //2를 제외했으니 3이상의 모든 홀수로 나눠본다.
  int sqrtn = int(sqrt(n));//홀수의 제곱근을 구한다 int 로 하였으니 제곱근보다 작은 정수가 나올것이다 이 숫자까지 진행하면서 나누어지면 소수가 아니다. 
  for (int div = 3; div <= sqrtn; div += 2) {
    if (n % div == 0) return false;
  }

  return true;
}

bool checktwoOfPrimeNum(int a, int b) {//두소수가 한자릿수만 차이가 나는지 검사
  //한자리수만 차이나는 것을 판단
  int count = 0;

  if (a / 1000 == b /1000) {//천자리 같으면
    count++;
  }

  if ((a % 1000) / 100 == (b % 1000) / 100) {//백자리 같으면
    count++;
  }

  if ((a % 100) / 10 == (b % 100) / 10) {//십자리 같으면
    count++;
  }

  if (a % 10 == b % 10) {//일자리 같으면
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

void initMap() {//각각의 소수에 대해 한자리수만 차이가 나는 다른 소수들과의 연결선을 만들어 준다 
  for (int i = 0; i < 10000; i++) {
    if (i < 1000) {
      primeNumCheck[i] = false;
      continue;
    }

    if (isPrimeNum(i)) {//소수이면
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
          if (checktwoOfPrimeNum(j, k)) {//한 자리만 차이가 나는 소수인 경우
            primeNumMap[j].push_back(PAIR(1, k));
          }
        }
      }
    }
  }
}

void findAnswer() {//다익스트라 알고리즘 (이 문제에서는 경로값이 전부 1)

  minTouchnum[fromPrime] = 0;//시작점으로의 거리는 0
  minQ.push(PAIR(0, fromPrime));//MINQ에 시작점을 넣고 시작한다

  int curr;
  while (!minQ.empty()) {//Q가 빌때까지 
    do {
      curr = minQ.top().second;
      minQ.pop();
    } while (!minQ.empty() && checked[curr]);//Queue 에서 꺼낸 곳을 이미 방문한 곳이면 무시한다

    if (checked[curr] == true) break;//Queue 가 empty 여서 빠져나온 경우라면 탈출
    checked[curr] = true;//정점 방문

    for (int i = 0; i < primeNumMap[curr].size(); i++) {//해당 정점과 연결된 곳들을 순회하며 경로값을 갱신해준다.
      int next = primeNumMap[curr].at(i).second;
      if (minTouchnum[next] > minTouchnum[curr]  + 1) {//새로 계산된 값이 기존 값보다 작으면 갱신
        minTouchnum[next] = minTouchnum[curr] + 1;
      }
      minQ.push(PAIR(minTouchnum[next], next));//정점까지의 거리와 점점 번호로 Pair를 만들어 Queue 에 넣어준다. 
    }
  }

  //MINQ 에서 나오는 정점정보들은 정점들을 차례대로 방문하지는 않는다 그러나 어쨋든 Queue 가 비어지게 된다는 것은 더 이상 갱신할
  //정점간의 정보가 없다는 것을 의미하므로 값을 얻는 데에는 문제가 없다.
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