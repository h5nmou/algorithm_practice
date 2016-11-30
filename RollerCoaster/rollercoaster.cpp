//http://www.koitp.org/problem/USACO_2006DEC_ROLLERCOASTER/read/

#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <vector>

using namespace std;

long L; //롤러코스터 길이  1 ≤ L ≤ 1,000
long N; //부품의 갯수      1 ≤ N ≤ 10,000
long B; //소들의 예산      1 ≤ B ≤ 1,000

long MAX(long a, long b) { return (a>b) ? a : b; }

class railInfo {
public:
  long length;
  long Fun;
  long price;
};

vector<railInfo> bupumInfo[1001];//부품을 출발 위치에 의헤 저장해둘 리스트 
long DPTable[1001][1001];//각 위치에 따른 최대 재미도를 저장할 DP Table

void initTable() {
  for (int i = 0; i < 1001; i++) {
    for (int j = 0; j < 1001; j++) {
      DPTable[i][j] = -1;
    }
  }
}

long DPFunc(long p, long b) {//위치, 지금까지 사용한 비용
  if (p >= L) {  //기저사례
    return 0;
  }

  long& ret = DPTable[p][b];//메모이제이션된것 리턴
  if (ret != -1) {
    return ret;
  }

  long retval = -1;
  for (int i = 0; i < bupumInfo[p].size(); i++) {//해당위치에 놓을 수 있는 부품들을 돌아가며 놓아본다.
    if (b + bupumInfo[p].at(i).price <= B) {
      retval = DPFunc(p + bupumInfo[p].at(i).length, b + bupumInfo[p].at(i).price);
      if (retval == -1) {//롤러코스터를 만들수 없는 경우.
        continue;
      }

      ret = MAX(ret, retval + bupumInfo[p].at(i).Fun);
    }      

  }

  return ret;

}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%d %d %d", &L, &N, &B);

  long Xi;
  for (int i = 0; i < N; i++) {
    railInfo ri;
    scanf("%ld %ld %ld %ld", &Xi, &ri.length, &ri.Fun, &ri.price);
    bupumInfo[Xi].push_back(ri);
  }

  initTable();

  printf("%ld", DPFunc(0, 0));

}


/*
소들은 롤러코스터를 짓고있다! 소들은 자신들이 가지고 있는 돈을 활용해서 최대한 재밌는 롤러코스터를 만들고 싶어한다.
롤러코스터는 직선형으로, 길이가 L이다. 소들이 롤러코스터를 지을 때, 롤러코스터는 N개의 교체 가능한 부품들중 일부로 구성되어야 한다.
각 부품 i는 고정된 길이 Wi를 가지고 있다. 그리고 다양한 지형의 굴곡 때문에, i번째 부품은 오직 Xi의 위치를 시작점으로만 놓을 수 있다.
소들은 다양한 롤러코스터를 0부터 L까지 빈틈없이 채우고 싶어한다. 만약 중간에 빈칸이 있으면 롤러코스터를 구성할 수 없다. 또한, 각 부품끼리 겹쳐서 롤러코스터를 건설하는 경우도 없다.
각 i번째 부품은 "재미도" Fi과 짓는데 드는 비용 Ci가 있다. 총 비용은 롤러코스터를 구성하는 부품을의 비용의 합으로 계산된다. 마찬가지로 총 재미도의 합은 롤러코스터를 구성하는 부품들의 재미도의 합으로 계산된다.
소들의 총 예산은 B이다. 소들을 도와 예산내에서 가장 큰 재미도를 가진 롤러코스터를 지을 수 있도록 도와주자!

입력
첫 번재 줄에 세개의 정수 L, N, B가 공백으로 분리되어 주어진다. (1 ≤ L ≤ 1,000, 1 ≤ N ≤ 10,000, 1 ≤ B ≤ 1,000)
두 번째 줄부터 N개의 줄에 걸쳐 각 부품들의 Xi, Wi, Fi, Ci가 공백으로 분리되어 주어진다. (0 ≤ Xi ≤ L-Wi, 1 ≤ Wi ≤ L, 1 ≤ Fi ≤ 1,000,000, 1 ≤ Ci ≤ 1,000)

출력

첫 번째 줄에 소들이 예산안에 각 부품들을 가지고 지을 수 있는 롤러코스터의 최대 재미도의 합을 출력한다. 만약, 롤러코스터를 짓는 방법이 없다면 -1을 출력한다.

힌트

예제 입력
5 6 10
0 2 20 6
2 3 5 6
0 1 2 1
1 1 1 3
1 2 5 4
3 2 10 2


예제 출력
17


예제 설명

3번, 5번, 6번 부품들을 이용하면 롤러코스터는 비용 7을 이용해서 재미도 17의 롤러코스터를 만들 수 있다. 반면, 1번, 2번 부품들을 이용하면 재미도는 25이지만 비용이 12가 되어 예산(10)을 초과하게 된다.

*/