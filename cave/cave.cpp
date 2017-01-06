//http://koitp.org/problem/COCI_2007_FIREFLY/read/
/*벌레 한 마리가 동굴을 지나려고 한다. 모두가 알다시피 동굴은 석순과 종유석이 굉장히 많은 공간이다.
이 벌레는 이렇게 장애물이 많은 동굴을 지나갈 것이다. 동굴의 길이는 N미터이고, 높이는 H미터이다. N은 항상 짝수이고,
장애물은 석순과 종유석이 번갈아 가면서 등장하고, 첫 장애물을 항상 석순이다.

아래 예제는 N=14, H =5의 예이다.
남자다운 이 벌레는 장애물을 굳이 피하지 않는다. 즉, 처음 정한 높이에서 일직선으로 장애물을 부수면서 지나간다. 
벌레가 아래에서 4번째 구간으로 지나가면, 아래 그림과 같이 8개의 장애물을 부수게 된다.


하지만, 첫 번째나 다섯 번째 구간으로 날아간다면 벌레는 7개의 장애물만 부시면 된다.

벌레는 아픔을 느끼는 남자이기 때문에, 최소한의 장애물만 부시고 싶어한다. 여러분은 이 벌레가 최소 몇 개의 장애물만 부수고도 통과할 수 있는지 구하고, 
그러한 구간이 총 몇 개 있는지 구하는 프로그램을 작성하시오.

입력
첫 번째 줄에 N과 H가 주어진다. N은 항상 짝수이다. (2 ≤ N ≤ 200,000, 2 ≤ H ≤ 500,000)

두 번째 줄부터 N개의 줄에 걸쳐 장애물의 크기가 순서대로 주어진다. 장애물의 크기는 H보다 작은 양수이다.

출력
첫 번째 줄에 개똥벌레가 파괴해야 하는 장애물의 최소값과 그러한 구간의 수를 공백으로 구분하여 출력하시오.

힌트
예제 입력

14 5
1
3
4
2
2
4
3
4
3
3
3
2
3
3
예제 출력

7 2
*/

//종유석과 석순을 따로 리스트로 저장한후에 내림차순 정렬하고 
//동굴길이 N 만큼 진행하며 최소로 벽을 지나야하는 경우와 그 갯수를 판단한다.

//아래 코드는 시간 초과임

#include <stdio.h>
#include <stdlib.h>
#include <functional>

using namespace std;

int N, H;

int countRock[500000];

void initTable() {
  for (int i = 0; i < 500000; i++) {
    countRock[i] = 9999999;
  }
}

int compare(const void* pAfter, const void* pPrevious) {
  int* after = (int*)pAfter;
  int* previous = (int*)pPrevious;

  return (*previous < *after) ? +1 : -1;//배열에서 뒤에 들어온 값이 큰 경우 순서를 바꿔준다 그러면 오름차순 정렬, 음수값이 리턴되면 순서를 바꾼다. 
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%d %d", &N, &H);

  int rock;
  for (int i = 0; i < N; i++) {
    scanf("%d", &rock);
    if (i % 2 == 0) {//2로 나누어 떨어지면 석순이다.
      for (int j = H - 1; j > H - rock - 1; j--) {
        countRock[j] += 1;
      }
    }
    else {
      for (int k = 0; k < rock; k++) {
        countRock[k] += 1;
      }
    }
  }

  qsort(countRock, H, sizeof(int), compare);

  int value = 0;
  int count = 0;

  value = countRock[0];
  for (int i = 0; i < H; i++) {
    if (countRock[i] == value) {
      count++;
    }
    else {
      break;
    }
  }

  printf("%d %d", value, count);
}