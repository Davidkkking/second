#include<stdio.h>
#include<string>
#include<algorithm>
using namespace std;
typedef struct StackNode {
	long long data;
	StackNode* next;
}StackNode,*LinkStackPtr;//Á´Õ»½Úµã

struct LinkStack {
	LinkStackPtr top;
	int count;
}LinkStack;//Á´Õ»½á¹¹

void Push(StackNode** head)
{
	StackNode* newNode=0;
	newNode->data = 0;
	newNode->next = *head;
	*head = newNode;//Á´Õ»ÈëÕ»
}

int pop(StackNode** head) {
	if (*head == NULL) {
		printf("Stack Underflow\n");
		return -1;
	}
	StackNode* temp = *head;
	int popped = temp->data;
	*head = (*head)->next;
	free(temp);
	return popped;//Á´Õ»³öÕ»
}

int main()
{
	StackNode* head = NULL;
	Push(&head);
	Push(&head);
	Push(&head);

	printf("popped:%d\n", pop(&head));
	printf("popped:%d\n", pop(&head));
	printf("popped:%d\n", pop(&head));
	return 0;

}