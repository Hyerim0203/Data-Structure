#include <stdio.h>
#include <stdlib.h>
# define MAX_LIST_SIZE 100
# define MAX_CHAR_SIZE 50

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

typedef char* element;
// �迭 ����Ʈ ����ü
typedef struct {
	char list[MAX_LIST_SIZE][MAX_CHAR_SIZE];
	int length;
} ArrayListType;

// ����Ʈ �ʱ�ȭ
void init(ArrayListType* L)
{
	L->length=0;
}

// ����Ʈ�� ����ִ��� Ȯ��
int is_empty(ArrayListType* L)
{
	return (L->length == 0);
}

// ����Ʈ�� ��á���� Ȯ��
int is_full(ArrayListType* L)
{
	return (L->length == MAX_LIST_SIZE);
}

// ����Ʈ�� ��� ��Ҹ� ǥ��
void display(ArrayListType* L)
{
	for (int i = 0; i<L->length; i++)
		printf("%s ", L->list[i]);
	printf("\n");
}

// ����Ʈ�� ���̸� ���Ѵ�
int get_length(ArrayListType* L)
{
	return (L->length);
}

// pos ��ġ�� ��Ҹ� ��ȯ�Ѵ�.
element get_entry(ArrayListType* L, int pos)
{	
	if (pos >= L->length || pos < 0) error("��ġ����");
	return (L->list[pos]);
}

// �ش� ���Ұ� ����Ʈ �ȿ� �ִ��� �˻�
int is_in_list(ArrayListType* L, element item)
{
	for (int i = 0; i < L->length; i++) {
		if (!strcmp(L->list[i], item))
			return (1);
	}
	return (0);
}

// pos ��ġ�� ��Ҹ� item���� ����
void replace(ArrayListType* L, int pos, element item)
{
	strcpy(&(L->list[pos]), item);
}

// ����Ʈ�� ��� ��Ҹ� ����
void clear(ArrayListType* L)
{
	L->length = 0;
}

// pos ��ġ�� ��Ҹ� ����
element delete_at(ArrayListType* L, int pos)
{	
	element item;
	if (pos < 0 || L->length <= pos)
		error("��ġ����");
	item = L->list[pos];
	for (int i = pos; i < (L->length - 1); i++)
	{
		strcpy(&(L->list[i]),L->list[i + 1]);
	}
	(L->length)--;
	return (item);
}

// pos ��ġ�� ��Ҹ� �߰�
void add_at(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && pos >= 0 && pos <= L->length)
	{
		for (int i = pos; i < L->length; i++)
			strcpy(&(L->list[i + 1]),L->list[i]);
		strcpy(&(L->list[pos]),item);
		(L->length)++;
	}
}

// ��ù��°�� ��Ҹ� �߰�
void add_first(ArrayListType* L, element item)
{
	if (!is_full(L))
	{
		for (int i = 0; i < L->length; i++)
			strcpy(&(L -> list[i + 1]),L->list[i]);
		strcpy(&(L->list[0]),item);
		(L->length)++;
	}
}

// �Ǹ������� ��Ҹ� �߰�
void add_last(ArrayListType* L, element item)
{	
	if (!is_full(L))
	{	
		strcpy(&(L->list[L->length]), item);
		(L->length)++;
	}
}

int main(void) {
	int i, n;
	ArrayListType list; // list�� ����
	init(&list);
	printf("---------------�����̵�6 ����---------------\n");
	add_last(&list, "mayonnaise");
	add_last(&list, "bread");
	add_last(&list, "cheese");
	add_last(&list, "milk");
	n = get_length(&list);
	printf("�����ؾ��� �׸���� %d�Դϴ�.\n", n);

	for (i = 0; i < n; i++)
		printf("%d�׸��� %s�Դϴ�.\n", i,get_entry(&list, i));
	clear(&list);
	printf("\n");
	printf("---------------��� ���� �׽�Ʈ---------------\n");
	if (is_empty(&list)) printf("����Ʈ�� ������ϴ�.\n");
	else printf("����Ʈ�� ������� �ʽ��ϴ�.\n");
	add_last(&list, "apple");
	display(&list);
	add_first(&list, "banana");
	display(&list);
	add_at(&list, 1, "strawberry");
	display(&list);
	if (is_in_list(&list, "banana")) printf("�ش� �ܾ�� �ֽ��ϴ�.\n");
	else printf("�ش� �ܾ�� �����ϴ�.\n");
	printf("����Ʈ ���� : %d\n", get_length(&list));
	delete_at(&list, 2);
	if (is_in_list(&list, "apple")) printf("�ش� �ܾ�� �ֽ��ϴ�.\n");
	else printf("�ش� �ܾ�� �����ϴ�.\n");
	replace(&list, 1, "orange");
	display(&list);
	printf("%d��° ��� : %s\n", 1, get_entry(&list, 1));
	if (is_full(&list)) printf("����Ʈ�� ����á���ϴ�.\n");
	else printf("����Ʈ�� �������� �ʾҽ��ϴ�.\n");
	clear(&list);
	if (is_empty(&list)) printf("����Ʈ�� ������ϴ�.\n");
	else printf("����Ʈ�� ������� �ʽ��ϴ�.\n");

}