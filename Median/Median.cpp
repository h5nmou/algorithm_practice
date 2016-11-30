//SDS_PRO_3_6 median
//http://www.koitp.org/problem/SDS_PRO_3_6/read/
//Priority Queue �� �̿��� �߾Ӱ� ã��

#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <functional>

using namespace std;
long long N;
long long median;

priority_queue<long long, vector<long long>, less<long long>> MAXQueue;
priority_queue<long long, vector<long long>, greater<long long>> MINQueue;

//MAXQ M MINQ
int main() {
  freopen("sample_input.txt", "r", stdin);
  scanf("%lld", &N);

  long long input;

  for (int i = 1; i <= N; i++) {
    if (i == 1) {
      scanf("%lld", &median);
      printf("%lld\n", median);
    }
    else {
      scanf("%lld", &input);

      if (input > median) {//���� ������ ���� median ���� ū��� 
        MINQueue.push(input);
      }
      else if (input < median) {//���� ������ ���� median ���� ������� 
        MAXQueue.push(input);
      }

      if (i % 2 == 1) {//Ȧ�� ��° �϶� 
        if (MINQueue.size() > MAXQueue.size()) {//���� median ���� ������ ���� �ʿ� �־��ش� ����� ū�ʿ��� �ϳ��� ���ְ� �װ��� Media���� �����Ѵ� 
          MAXQueue.push(median);
          median = MINQueue.top();
          MINQueue.pop();
        }
        else if (MINQueue.size() < MAXQueue.size()) {
          MINQueue.push(median);
          median = MAXQueue.top();
          MAXQueue.pop();
        }

        printf("%lld\n", median);
      }
    }
  }
  return 0;
}