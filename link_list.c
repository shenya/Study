#include <stdio.h>
#include <stdlib.h>
#include "link_list.h"

LINK_LIST *link_head;

LINK_LIST *link_insert(LINK_LIST **head, int num)
{
	LINK_LIST *link_temp;
	LINK_LIST *head_temp = *head;
	LINK_LIST *p, *q;

	link_temp = (LINK_LIST *)malloc(sizeof(LINK_LIST));
	if(link_temp == NULL)
	{
			perror("fail to malloc");
			exit(1);
	}
	link_temp->next = NULL;
	link_temp->number = num;
	if(head_temp == NULL)
	{
			*head = link_temp;

	}
	else
	{
		p = head_temp;
		q = p->next;

		if(p->number <= head_temp->number)
		{
			link_temp->next = p;
			head_temp = link_temp;
		}
		else
		{
			if(q == NULL)
			{
				p->next = link_temp;
			}
			else
			{
				while(q != NULL)
				{
					if(q->number >= link_temp->number)
					{
						break;
					}
					p = p->next;
					q = q->next;
				}
				
				p->next = link_temp;
				link_temp->next = q;

			}
		}
	}

	return head_temp;
}

void link_print(LINK_LIST *head)
{
		LINK_LIST *p = head;

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
