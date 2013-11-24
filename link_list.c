#include <stdio.h>
#include <stdlib.h>
#include "link_list.h"

#define RED_CNT 6

#define FIRST_AWARD 100000
#define SECOND_AWARD 10000
#define THIRD_AWARD  1000
#define FORTH_AWARD 100
#define FIFTH_AWARD 10
#define SIXTH_AWARD 1
#define NULL_AWARD 0

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

LINK_LIST *link_insert(LINK_LIST *head, int *card, int length)
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
		link_temp->red_card[i] = card[i];
	}
	link_temp->blue_card = card[i];
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
#endif

int link_compare(LINK_LIST *head, int *card, int length)
{
	int flag = 0;
	int award = 0;
	int i, j;

	LINK_LIST *p = head;

	if(p == NULL)
	{
		printf("link head is NULL\n");
		return 0;
	}
	if(p->next == NULL)
	{
		printf("link is empty\n");
		return 0;
	}
	
	p = p->next;

	while(p)
	{
		flag = 0;
		for(i=0; i<RED_CNT; i++)
		{
			for(j=0; j<RED_CNT; j++)
			{
			
				if(p->red_card[j] == card[i])
				{
						flag++;
				}
			}
		}
		if(p->blue_card == card[i])
		{
				flag += 10;
		}
		award += award_get(flag);

		p = p->next;
	}

	printf("award_get is %d\n", award);

	return 0;
}

int award_get(int flag)
{
	int award = 0;

	switch(flag)
	{
		case 0:
		case 1:
		case 2:
		case 3:
					award += NULL_AWARD;
					break;
		case 4:
					award += FIFTH_AWARD;
					break;
		case 5:
					award += FORTH_AWARD;
					break;
		case 6:
					award += SECOND_AWARD;
					break;
		case 10:
		case 11:
		case 12:
					award += SIXTH_AWARD;
					break;

		case 13:
					award += FIFTH_AWARD;
					break;
		case 14:
					award += FORTH_AWARD;
					break;
		case 15:
					award += THIRD_AWARD;
					break;
		case 16:
					award += FIRST_AWARD;
					break;

		default:
		break;
	}

	return award;
}

void link_print(LINK_LIST *head)
{
		LINK_LIST *p = head;
		int i;

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
		printf("red card:                               blue: \n");
		while(p)
		{
			for(i=0; i<RED_CNT; i++)
				printf("%5d", p->red_card[i]);
			printf("        %5d\n", p->blue_card);
			p = p->next;
		}
}
