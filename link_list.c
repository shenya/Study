#include <stdio.h>
#include <stdlib.h>
#include "link_list.h"

#define RED_CNT 6
LINK_LIST *link_head;

LINK_LIST *link_init(LINK_LIST **head)
{
	LINK_LIST *link_temp;

	link_temp = (LINK_LIST *)malloc(sizeof(LINK_LIST));
	if(link_temp == NULL)
	{
		perror("fail to malloc");
		exit(1);
	}
	link_temp->next = NULL;
	*head = link_temp;

	return link_temp;
}

LINK_LIST *link_insert(LINK_LIST *head, int *red, int blue)
{
	LINK_LIST *link_temp;
	LINK_LIST *head_temp = head;
	LINK_LIST *p, *q;
	int i;

	if(head_temp == NULL)
	{
		printf("link head is NULL\n");
		return NULL;
	}

	link_temp = (LINK_LIST *)malloc(sizeof(LINK_LIST));
	if(link_temp == NULL)
	{
			perror("fail to malloc");
			exit(1);
	}
	link_temp->next = NULL;
	
	for(i=0; i<RED_CNT; i++)
	{
		link_temp->red_card[i] = red[i];
	}
	link_temp->blue_card = blue;
	if(head_temp->next == NULL)
	{
			head_temp->next = link_temp;
	}
	else
	{
		p = head_temp->next;
		q = p->next;

		link_temp->next = p;
		head_temp->next = link_temp;
	}


	return head_temp;
}
#if 0
LINK_LIST *link_del(LINK_LIST *head, int num)
{
	LINK_LIST *p = NULL, *q = NULL;
	LINK_LIST *head_temp = head;

	if(head_temp == NULL)
	{
		printf("link head is NULL\n");
		return NULL;
	}

	p = head_temp;

	while(p->next != NULL)
	{
		if(p->next->number == num)
		{
			q = p->next;
			p->next = p->next->next;

			break;
		}

		p = p->next;
	}

	if(q != NULL)
	{
		printf("del data: %d\n", num);
		free(q);

		return head_temp;
	}

	printf("not find this data\n");
	return NULL;
}

void link_print(LINK_LIST *head)
{
		LINK_LIST *p = head;
		if(p == NULL)
		{
			printf("Link list head is NULL\n");
			return ;
		}
		p = p->next;
		if(p == NULL)
		{
			printf("Link list is empty\n");
			return ;
		}
		
		while(p)
		{
			printf("number: %d\n", p->number);
			p = p->next;
		}
}
#endif
