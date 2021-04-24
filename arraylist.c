#include <stdio.h>
#include <stdlib.h>
# define MAX_LIST_SIZE 100
# define MAX_CHAR_SIZE 50

// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

typedef char* element;
// 배열 리스트 구조체
typedef struct {
	char list[MAX_LIST_SIZE][MAX_CHAR_SIZE];
	int length;
} ArrayListType;

// 리스트 초기화
void init(ArrayListType* L)
{
	L->length=0;
}

// 리스트가 비어있는지 확인
int is_empty(ArrayListType* L)
{
	return (L->length == 0);
}

// 리스트가 꽉찼는지 확인
int is_full(ArrayListType* L)
{
	return (L->length == MAX_LIST_SIZE);
}

// 리스트의 모든 요소를 표시
void display(ArrayListType* L)
{
	for (int i = 0; i<L->length; i++)
		printf("%s ", L->list[i]);
	printf("\n");
}

// 리스트의 길이를 구한다
int get_length(ArrayListType* L)
{
	return (L->length);
}

// pos 위치의 요소를 반환한다.
element get_entry(ArrayListType* L, int pos)
{	
	if (pos >= L->length || pos < 0) error("위치오류");
	return (L->list[pos]);
}

// 해당 원소가 리스트 안에 있는지 검사
int is_in_list(ArrayListType* L, element item)
{
	for (int i = 0; i < L->length; i++) {
		if (!strcmp(L->list[i], item))
			return (1);
	}
	return (0);
}

// pos 위치의 요소를 item으로 변경
void replace(ArrayListType* L, int pos, element item)
{
	strcpy(&(L->list[pos]), item);
}

// 리스트의 모든 요소를 제거
void clear(ArrayListType* L)
{
	L->length = 0;
}

// pos 위치의 요소를 제거
element delete_at(ArrayListType* L, int pos)
{	
	element item;
	if (pos < 0 || L->length <= pos)
		error("위치오류");
	item = L->list[pos];
	for (int i = pos; i < (L->length - 1); i++)
	{
		strcpy(&(L->list[i]),L->list[i + 1]);
	}
	(L->length)--;
	return (item);
}

// pos 위치에 요소를 추가
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

// 맨첫번째에 요소를 추가
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

// 맨마지막에 요소를 추가
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
	ArrayListType list; // list를 생성
	init(&list);
	printf("---------------슬라이드6 구현---------------\n");
	add_last(&list, "mayonnaise");
	add_last(&list, "bread");
	add_last(&list, "cheese");
	add_last(&list, "milk");
	n = get_length(&list);
	printf("쇼핑해야할 항목수는 %d입니다.\n", n);

	for (i = 0; i < n; i++)
		printf("%d항목은 %s입니다.\n", i,get_entry(&list, i));
	clear(&list);
	printf("\n");
	printf("---------------모든 연산 테스트---------------\n");
	if (is_empty(&list)) printf("리스트가 비었습니다.\n");
	else printf("리스트가 비어있지 않습니다.\n");
	add_last(&list, "apple");
	display(&list);
	add_first(&list, "banana");
	display(&list);
	add_at(&list, 1, "strawberry");
	display(&list);
	if (is_in_list(&list, "banana")) printf("해당 단어는 있습니다.\n");
	else printf("해당 단어는 없습니다.\n");
	printf("리스트 길이 : %d\n", get_length(&list));
	delete_at(&list, 2);
	if (is_in_list(&list, "apple")) printf("해당 단어는 있습니다.\n");
	else printf("해당 단어는 없습니다.\n");
	replace(&list, 1, "orange");
	display(&list);
	printf("%d번째 요소 : %s\n", 1, get_entry(&list, 1));
	if (is_full(&list)) printf("리스트가 가득찼습니다.\n");
	else printf("리스트가 가득차지 않았습니다.\n");
	clear(&list);
	if (is_empty(&list)) printf("리스트가 비었습니다.\n");
	else printf("리스트가 비어있지 않습니다.\n");

}