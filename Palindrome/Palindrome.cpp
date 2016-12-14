//http://koitp.org/problem/PALINDROME/read/

/*문제
어떤 문자열 S의 부분 문자열(Substring)이란, 문자열 S의 연속된 부분을 선택하여 만들 수 있는 문자열을 의미한다. 
즉, S="abcd"의 부분 문자열은 "abcd", "abc", "bcd", "ab", "bc", "cd", "a", "b", "c", "d"가 존재한다.

또한, Palindrome은 앞에서 읽어도, 뒤에서 읽어도 같은 문자열을 의미한다. 예를 들어, "abcba", "abba", "aba" 등이 Palindrome이다. 
하지만 "abcabc" 등은 Palindrome이 아니다.

문자열 S가 주어질 때, 문자열 S의 부분 문자열 중 Palindrome이 되는 문자열의 최대 길이를 알아내어라.

입력
첫 번째 줄에 문자열 S가 주어진다. 문자열 S는 대문자 알파벳으로만 구성되며, 길이는 5,000 이하이다.

출력
첫 번째 줄에 주어진 문자열의 가장 긴 Palindrome Substring의 길이를 출력하라.

힌트
예제 입력

ADEEDCCDEEA
예제 출력

8
*/

#include <stdio.h>
#include <stdlib.h>

using namespace std;

int MAXLengthPalindromeString = 1;
char stringbuffer[5000];

int MAX(int a, int b) { return (a > b) ? a : b; }

int findPalindrom(int index) {//해당 인덱스를 기점으로 혹은 해당인덱스와 다음인덱스 사이를 기점으로 palindrome인지 검사하면서 길이를 카운팅 하는 함수
  int ret1 = 0;
  int ret2 = 0;

  //해당 인덱스를 기점으로 펠린드롬인가
  for (int i = 1; i < 5000; i++) {
    if (index - i >= 0 && index + i <= 5000) {
      if (stringbuffer[index - i] - stringbuffer[index + i] == 0 && stringbuffer[index - i] != 0 && stringbuffer[index + i] != 0){//펠린드롬이다
        if (ret1 == 0) ret1 = 1;
        ret1 += 2;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }

  //해당인덱와 다음인덱스 사이를 기점으로 펠린드롬인가
  int indexLeft = index; int indexRight = index + 1;
  for (int i = 0; i < 5000; i++) {
    if (indexLeft - i >= 0 && indexRight + i <= 5000) {
      if (stringbuffer[indexLeft - i] - stringbuffer[indexRight + i] == 0 && stringbuffer[indexLeft - i] != 0 && stringbuffer[indexRight + i] != 0) {//펠린드롬이다
        ret2 += 2;
      }
      else {
        break;
      }
    }
    else {
      break;
    }
  }

  return MAX(ret1, ret2);
}

int main() {
  freopen("sample_input.txt", "r", stdin);

  scanf("%s", stringbuffer);

  for (int i = 0; i < 5000; i++) {
    MAXLengthPalindromeString = MAX(MAXLengthPalindromeString, findPalindrom(i));
  }

  printf("%d", MAXLengthPalindromeString);
}