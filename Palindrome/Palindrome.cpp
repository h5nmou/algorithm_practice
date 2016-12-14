//http://koitp.org/problem/PALINDROME/read/

/*����
� ���ڿ� S�� �κ� ���ڿ�(Substring)�̶�, ���ڿ� S�� ���ӵ� �κ��� �����Ͽ� ���� �� �ִ� ���ڿ��� �ǹ��Ѵ�. 
��, S="abcd"�� �κ� ���ڿ��� "abcd", "abc", "bcd", "ab", "bc", "cd", "a", "b", "c", "d"�� �����Ѵ�.

����, Palindrome�� �տ��� �о, �ڿ��� �о ���� ���ڿ��� �ǹ��Ѵ�. ���� ���, "abcba", "abba", "aba" ���� Palindrome�̴�. 
������ "abcabc" ���� Palindrome�� �ƴϴ�.

���ڿ� S�� �־��� ��, ���ڿ� S�� �κ� ���ڿ� �� Palindrome�� �Ǵ� ���ڿ��� �ִ� ���̸� �˾Ƴ����.

�Է�
ù ��° �ٿ� ���ڿ� S�� �־�����. ���ڿ� S�� �빮�� ���ĺ����θ� �����Ǹ�, ���̴� 5,000 �����̴�.

���
ù ��° �ٿ� �־��� ���ڿ��� ���� �� Palindrome Substring�� ���̸� ����϶�.

��Ʈ
���� �Է�

ADEEDCCDEEA
���� ���

8
*/

#include <stdio.h>
#include <stdlib.h>

using namespace std;

int MAXLengthPalindromeString = 1;
char stringbuffer[5000];

int MAX(int a, int b) { return (a > b) ? a : b; }

int findPalindrom(int index) {//�ش� �ε����� �������� Ȥ�� �ش��ε����� �����ε��� ���̸� �������� palindrome���� �˻��ϸ鼭 ���̸� ī���� �ϴ� �Լ�
  int ret1 = 0;
  int ret2 = 0;

  //�ش� �ε����� �������� �縰����ΰ�
  for (int i = 1; i < 5000; i++) {
    if (index - i >= 0 && index + i <= 5000) {
      if (stringbuffer[index - i] - stringbuffer[index + i] == 0 && stringbuffer[index - i] != 0 && stringbuffer[index + i] != 0){//�縰����̴�
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

  //�ش��ε��� �����ε��� ���̸� �������� �縰����ΰ�
  int indexLeft = index; int indexRight = index + 1;
  for (int i = 0; i < 5000; i++) {
    if (indexLeft - i >= 0 && indexRight + i <= 5000) {
      if (stringbuffer[indexLeft - i] - stringbuffer[indexRight + i] == 0 && stringbuffer[indexLeft - i] != 0 && stringbuffer[indexRight + i] != 0) {//�縰����̴�
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