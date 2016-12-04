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

using namespace std;

int INF = 9999999;
int MIN(int a, int b) { return (a > b) ? b : a; }
int testNum;
int fromPrime;//1,000 ≤ 소수 ≤ 9,999
int toPrime;//1,000 ≤ 소수 ≤ 9,999

int dpTable[10000][4][10];//[각숫자에서][해당자릿수를][이 숫자로 바꿨을때의] 목표 소수까지의 최소 변환 횟수
int isChecked[10000][4][10][1];//이미 체크가 시작된 숫자인지 여부

bool isPrimeNum(int n) {  
  if (n <= 1) return false;//1은 소수가 아니다
  if (n == 2) return false;//2는 짝수중 유일하게 소수다

  //2를 제외한 모든 짝수는 소수가 아니다
  if (n % 2 == 0) return false;

  //2를 제외했으니 3이상의 모든 홀수로 나눠본다.
  int sqrtn = int(sqrt(n));//홀수의 제곱근을 구한다 int 로 하였으니 제곱근보다 작은 정수가 나올것이다 이 숫자까지 진행하면서 나누어지면 소수가 아니다. 
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

int DPFunc(int previousPrime, int position, int changeNo) {//previousPrime : 이 숫자의 : position 에 해당하는 자릿수의 숫자를 changeNo 로바꿨을때에 ret : 목표 소수에 도달하는 최소 횟수
  isChecked[previousPrime][position][changeNo][0] = 1;

  //기저사례

  //Memoization 된 값 ret
  int &ret = dpTable[previousPrime][position][changeNo];

  if (ret != INF) {
    return ret;
  }

  //해당 자리의 숫자를 바꾸고 DP 를 돌려 본다. //이미 target 소수와 숫자가 같은 자릿수는 바꿀필요가 없다. 
  int nextPrimeNum = 0;

  switch(position) {
    case 0:
      if (changeNo == 0) return ret;//첫번째 자릿수는 0이 될수 없다.//문제 조건 (중간수는 4자리수여야 함)
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

  for (int j = 0; j < 4; j++) {//자릿수를 바꿔본다. 
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

//모든 소수를 가지고 서로 바뀔수 있는 경우를 경로로 나타내고 다익스트라로 풀수도 있을 듯.