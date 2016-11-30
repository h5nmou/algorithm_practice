#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

#if 0//A simple priority queue of integers
int main() {
  //priority_queue<int> pq;//�⺻ �������� ������ �����Ѵ�.
  //priority_queue<int, vector<int>, less<int>> pq;//MAX queue (ū���� ���� ������ queue)
  priority_queue<int, vector<int>, greater<int>> pq;//MIN queue (���� ���� ���� ������ queue)
  pq.push(300); pq.push(200); pq.push(400); pq.push(100);

  while (!pq.empty()) {
    printf("%d\n", pq.top());
    pq.pop();
  }
}
#elif 1//A priority queue with a custom class
class Toast
{
public:
  int price;
  Toast(int price) : price(price) {}
};

struct ToastCompare {
  bool operator ()(const Toast &t1, const Toast &t2) const {
    //return t1.price > t2.price;////��������
    return t1.price < t2.price;////��������
  }
};

int main()
{
  Toast toast1(200);
  Toast toast2(30);
  Toast toast3(300);
  Toast toast4(1);

  //priority_queue<Toast> queue;
  priority_queue<Toast, vector<Toast>, ToastCompare> queue;

  queue.push(toast1);
  queue.push(toast2);
  queue.push(toast3);
  queue.push(toast4);

  while (!queue.empty())
  {
    Toast t = queue.top();
    printf("%d\n", t.price);
    queue.pop();
  }

  system("pause");

  return 0;
}

#endif