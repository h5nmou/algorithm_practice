#include <stdlib.h>
#include <stdio.h>

struct item {
	int number;
	int length;
};

int compare_int(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);//오름차순
  //return (*(int*)b - *(int*)a);//내림차순
}

int compare_item_bynumber(const void* item1, const void* item2) {
	int compare = 0;//리턴값이 0보다 크면 바꾼다. 즉 배열안에서 위치를 바꿔주고 싶은 기준에 부합하면 0보다 큰 값을 넣어주면 된다.
    //인자를 받아줄 포인터
	item *temp1, *temp2;

	temp1 = (item*)item1;
	temp2 = (item*)item2;

	compare = (temp1->number > temp2->number) ? 1 : -1;//앞의 값이 크면 바꾼다 즉 올림차순 정렬이 된다. 
	return compare;
}

int compare_item_bylength(const void* item1, const void* item2) {
	int compare = 0;//리턴값이 0보다 크면 바꾼다. 즉 배열안에서 위치를 바꿔주고 싶은 기준에 부합하면 0보다 큰 값을 넣어주면 된다. (음수, 양수로 하자)
  //인자를 받아줄 포인터
	item *temp1, *temp2;
	temp1 = (item*)item1;
	temp2 = (item*)item2;

	compare = (temp1->length > temp2->length) ? -1 : 1;//앞의 값이 크면 바꾸지 않는다 즉 내림차순 정렬이 된다. 
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