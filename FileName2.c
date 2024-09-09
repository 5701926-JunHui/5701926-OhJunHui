#include <stdio.h>											// 배열리스트 프로그램
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int element;
typedef struct
{
	element list[MAX_LIST_SIZE];
	int size;
}ListType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_List(ListType* L)		// 리스트 초기화
{
	L->size = 0;		// 리스트 내 항목의 갯수가 0개로 초기화
}

int is_emtpy(ListType* L)
{
	return L->size == 0;	// 리스트 내 항목의 갯수가 없다면 값 반환
}

int is_full(ListType* L)
{
	return L->size == MAX_LIST_SIZE;	// 리스트 내 항목의 갯수가 최대 리스트 사이즈와 같다면 값 반환
}

element get_entry(ListType* L, int pos)		// pos 위치의 요소(특정 위치)를 반환한다
{
	if (pos < 0 || pos >= MAX_LIST_SIZE)	// 이 위치는 값이 존재할 수 없는 위치에 있다 "0보다 작다 또는 최대 사이즈보다 크거나 같다"
		error("위치 오류");					// 따라서 위치 오류
	return L->list[pos];					// 리스트 내 특정 위치에 있는 요소를 반환
}

void print_List(ListType* L)		// 리스트 출력 함수
{
	for (int i = 0; i < L->size; i++)		// 삽입한 '항목의 갯수'만큼 반복
		printf("%d->", L->list[i]);			// 반복 횟수만큼 출력
	printf("\n");
}

void insert_last(ListType* L, element item)		// 리스트의 맨 끝에 요소를 추가하는 함수
{
	if (L->size >= MAX_LIST_SIZE) {		// 요소의 갯수가 꽉 찼다면
		error("리스트 오버플로우");		// 리스트 오버플로우
	}
	else L->list[L->size++] = item;		// 그렇지 않다면 리스트 내 요소의 갯수를 늘이고 item 변수에 대입
}

void insert(ListType* L, int pos, element item)		// pos(특정 위치)에 요소를 추가하는 함수
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {	// 리스트가 가득 차지 않았거나 특정 위치가 0번째 보다 크거나, pos가 요소의 갯수보다 작거나 같다면 (<- 값을 넣을 수 있는 조건)
		for (int i = L->size; i >= pos; i--)		// i의 초깃값은 요소의 갯수; pos보다 크거나 같을 때까지 반복; i는 감소
			L->list[i] = L->list[i - 1];		// 특정 위치를 맨 끝 요소부터 내려오면서 찾는다 -> 요소가 2개일 때 1번 위치에 넣고 싶다면 위 반복 조건을 만족했을 때
		L->list[pos] = item;	// 해당 위치에 값을 item에 대입
		L->size++;		// 요소 개수 증가
	}
}

element delete(ListType* L, int pos)		// 특정 위치의 요소를 삭제하는 프로그램
{
	element item;
	if (pos < 0 || pos >= L->size)		// 값이 존재할 수 없는 위치
		error("위치 오류");
	item = L->list[pos];		// 현재 위치 항목을 저장하고
	for (int i = pos; i < (L->size - 1); i++)		// pos 위치를 기준으로 한 칸씩 이동
		L->list[i] = L->list[i + 1];
	L->size--;		// 요소 개수 감소(제거)
	return item;		//저장된 항목 반환
}


int main(void)
{
	ListType list;

	init_List(&list);

	insert(&list, 0, 10); print_List(&list);
	insert(&list, 0, 20); print_List(&list);
	insert(&list, 1, 30); print_List(&list);
	insert_last(&list, 40); print_List(&list);
	delete(&list, 0); print_List(&list);

	return 0;
}