#include <stdio.h>											// �迭����Ʈ ���α׷�
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

void init_List(ListType* L)		// ����Ʈ �ʱ�ȭ
{
	L->size = 0;		// ����Ʈ �� �׸��� ������ 0���� �ʱ�ȭ
}

int is_emtpy(ListType* L)
{
	return L->size == 0;	// ����Ʈ �� �׸��� ������ ���ٸ� �� ��ȯ
}

int is_full(ListType* L)
{
	return L->size == MAX_LIST_SIZE;	// ����Ʈ �� �׸��� ������ �ִ� ����Ʈ ������� ���ٸ� �� ��ȯ
}

element get_entry(ListType* L, int pos)		// pos ��ġ�� ���(Ư�� ��ġ)�� ��ȯ�Ѵ�
{
	if (pos < 0 || pos >= MAX_LIST_SIZE)	// �� ��ġ�� ���� ������ �� ���� ��ġ�� �ִ� "0���� �۴� �Ǵ� �ִ� ������� ũ�ų� ����"
		error("��ġ ����");					// ���� ��ġ ����
	return L->list[pos];					// ����Ʈ �� Ư�� ��ġ�� �ִ� ��Ҹ� ��ȯ
}

void print_List(ListType* L)		// ����Ʈ ��� �Լ�
{
	for (int i = 0; i < L->size; i++)		// ������ '�׸��� ����'��ŭ �ݺ�
		printf("%d->", L->list[i]);			// �ݺ� Ƚ����ŭ ���
	printf("\n");
}

void insert_last(ListType* L, element item)		// ����Ʈ�� �� ���� ��Ҹ� �߰��ϴ� �Լ�
{
	if (L->size >= MAX_LIST_SIZE) {		// ����� ������ �� á�ٸ�
		error("����Ʈ �����÷ο�");		// ����Ʈ �����÷ο�
	}
	else L->list[L->size++] = item;		// �׷��� �ʴٸ� ����Ʈ �� ����� ������ ���̰� item ������ ����
}

void insert(ListType* L, int pos, element item)		// pos(Ư�� ��ġ)�� ��Ҹ� �߰��ϴ� �Լ�
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {	// ����Ʈ�� ���� ���� �ʾҰų� Ư�� ��ġ�� 0��° ���� ũ�ų�, pos�� ����� �������� �۰ų� ���ٸ� (<- ���� ���� �� �ִ� ����)
		for (int i = L->size; i >= pos; i--)		// i�� �ʱ갪�� ����� ����; pos���� ũ�ų� ���� ������ �ݺ�; i�� ����
			L->list[i] = L->list[i - 1];		// Ư�� ��ġ�� �� �� ��Һ��� �������鼭 ã�´� -> ��Ұ� 2���� �� 1�� ��ġ�� �ְ� �ʹٸ� �� �ݺ� ������ �������� ��
		L->list[pos] = item;	// �ش� ��ġ�� ���� item�� ����
		L->size++;		// ��� ���� ����
	}
}

element delete(ListType* L, int pos)		// Ư�� ��ġ�� ��Ҹ� �����ϴ� ���α׷�
{
	element item;
	if (pos < 0 || pos >= L->size)		// ���� ������ �� ���� ��ġ
		error("��ġ ����");
	item = L->list[pos];		// ���� ��ġ �׸��� �����ϰ�
	for (int i = pos; i < (L->size - 1); i++)		// pos ��ġ�� �������� �� ĭ�� �̵�
		L->list[i] = L->list[i + 1];
	L->size--;		// ��� ���� ����(����)
	return item;		//����� �׸� ��ȯ
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