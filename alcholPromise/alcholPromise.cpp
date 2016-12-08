//http://koitp.org/problem/SDS_PRO_6_6/read/
/*
����
�����̴� ���� �����Ѵ�.�׷���, �����̴� ��û�ϰԵ� ���� ���� �������� �� ����� ��Ҵ�.����� ���� ��� ������� �ٵ� �����̿��� ���� ���̰� �;� �Ѵ�.
�� ��ӿ��� ������ ������� �����̰� 1�� ���� ������ �����̿��� ���� Di ���� ���ð� �� ���̴�.�� ����� ������ ������ Ti �� �Ÿ�����, 
�����̴� ��� ��ҿ� ���� ���µ� �� 2 * Ti���� �ɸ��� �ȴ�. (��� ��ҿ� �� ���� �׻� ������ ������ ����Ѵ�.) ��������, 
������ ������ �ƴ� ������� ������� ������ �ں� ��Ǯ�� �����̰� ������ ��� ��ұ��� ���µ� �ɸ��� �ð� ������ ���ֱ�� �ߴ�.
�����̴� �翬�� ��Ƴ��� ��ӵ��� �ݵ�� ���߸� �Ѵ�.�������� �����̰� ���� ���� ���� �� �ֵ��� ������ ��� ������ ��������.
�� ��, �����̰� ���� ���ָ� ���ô� �ð��� 0���̶�� ��������.�״� ���� ��û ���� ���ôϱ�!

�Է�
ù ��° �ٿ� �� ����� ���� N�� �־�����. (1 �� N �� 100, 000)
�� ��° �ٺ��� N���� �ٿ� ���� �� ����� Ti�� Di�� �־�����. (1 �� Ti �� 2, 000, 000, 1 �� Di �� 100)

���
ù ��° �ٿ� �����̰� ���ž� �� �ּ� ������ ���� ����Ѵ�.

�Է� ����

6
3 1
2 5
2 3
3 2
4 1
1 6
��� ����

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
    //������ �ٲٰ� ������ false�� �����Ѵ�.
    //���⼭�� �ڿ� ���³��� ���� �湮�������� �����ϸ� �ٲ���� �Ѵ�. �׷��� ���ĵ� ������� �湮�������� �����ϴϱ�....
    //�� a�� �湮�������� ���ž� �ϴ� ������ ���� b�� ���� �湮�������� ���ž� �ϴ� �������� ������ �ٲ���� �Ѵ�.
    return ((2 * b.time) * a.bottle) < ((2 * a.time) * b.bottle);
  }
};

priority_queue<PAIR, vector<PAIR>, PAIRCompare> promiseQ;

long N = 0;//������� ����
long totalBottle = 0;
long pastTime = 0;//���ݱ��� �ɸ� �ð��� �����ϴ� ����

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