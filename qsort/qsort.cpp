#include <stdlib.h>
#include <stdio.h>

struct item {
	int number;
	int length;
};

int compare_int(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);//��������
  //return (*(int*)b - *(int*)a);//��������
}

int compare_item_bynumber(const void* item1, const void* item2) {
	int compare = 0;//���ϰ��� 0���� ũ�� �ٲ۴�. �� �迭�ȿ��� ��ġ�� �ٲ��ְ� ���� ���ؿ� �����ϸ� 0���� ū ���� �־��ָ� �ȴ�.
    //���ڸ� �޾��� ������
	item *temp1, *temp2;

	temp1 = (item*)item1;
	temp2 = (item*)item2;

	compare = (temp1->number > temp2->number) ? 1 : -1;//���� ���� ũ�� �ٲ۴� �� �ø����� ������ �ȴ�. 
	return compare;
}

int compare_item_bylength(const void* item1, const void* item2) {
	int compare = 0;//���ϰ��� 0���� ũ�� �ٲ۴�. �� �迭�ȿ��� ��ġ�� �ٲ��ְ� ���� ���ؿ� �����ϸ� 0���� ū ���� �־��ָ� �ȴ�. (����, ����� ����)
  //���ڸ� �޾��� ������
	item *temp1, *temp2;
	temp1 = (item*)item1;
	temp2 = (item*)item2;

	compare = (temp1->length > temp2->length) ? -1 : 1;//���� ���� ũ�� �ٲ��� �ʴ´� �� �������� ������ �ȴ�. 
	return compare;
}

item itemArray[10];

int main() {
	freopen("sample_input.txt", "r", stdin);

	for (int i = 0; i < 10; i++) {
		int num, len;
		scanf("%d %d", &num, &len);
		itemArray[i].number = num;
		itemArray[i].length = len;
	}

	qsort(itemArray, 10, sizeof(item), compare_item_bynumber);
}