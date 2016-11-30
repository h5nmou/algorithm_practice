//SDS_PRO_3_6 median
//http://www.koitp.org/problem/SDS_PRO_3_6/read/
//Priority Queue 를 이용한 중앙값 찾기

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

      if (input > median) {//새로 들어오는 값이 median 보다 큰경우 
        MINQueue.push(input);
      }
      else if (input < median) {//새로 들어오는 값이 median 보다 작은경우 
        MAXQueue.push(input);
      }

      if (i % 2 == 1) {//홀수 번째 일때 
        if (MINQueue.size() > MAXQueue.size()) {//기존 median 값을 사이즈 작은 쪽에 넣어준다 사이즈가 큰쪽에서 하나를 빼주고 그값을 Media으로 저장한다 
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