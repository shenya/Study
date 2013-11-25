#include <stdio.h>
#include <string.h>

#include "link_list.h"


#define VALUE_MIN 150

#define STR_SIZE 100
#define RED_MAX 33
#define BLUE_MAX 16

#define RANGE 0

int times[] = {1, 5, 30, 50, 10, 3 , 1};
extern int fd;

int read_file(const char *file)
{
	FILE *fp;
	char str[STR_SIZE];
	int card_data[7];

	fp = fopen(file, "r");
	while(fgets(str, STR_SIZE, fp) != NULL)
	{

		printf("%s\n", str);

		get_data_from_str(card_data, 7, str);
		link_insert(link_head, card_data, 7);
#if 0
		int i;
		for(i=0; i<7; i++)
		{
			printf("%5d", card_data[i]);
		}
		printf("\n");
#endif
	}

	return 0;	
}
int write_file(int fd, int *data, int length, int flag, int value_sum)
{
	int i;
	char num_str[32];
	char str_space[] = " ";
	char str_enter[] = "\n";
	char *F_end;

	for(i=0; i<length; i++)
	{
			if(i != 6)
			{
				sprintf(num_str, "  %d", data[i]);
			}
			else
			{
				
				sprintf(num_str, "---%d   ", data[i]);
			}
			write(fd, num_str, strlen(num_str));
	}
	sprintf(num_str, "Value::%d value_sum: %d", flag, value_sum);
	F_end = num_str + strlen(num_str);
	*F_end++ = '\n';
	*F_end = '\0';
	write(fd, num_str, strlen(num_str));

	return 0;
}
int get_data_from_str(int *card_data, int length,  const char *str)
{
	int i;
	char temp[3];
	int pos = 8;

	for(i=0; i<length; i++)
	{
		temp[0] = *(str + pos);
		temp[1] = *(str + pos + 1);
		temp[2] = '\0';
#if 0
		printf("str%s\n", temp);
		printf("strtoi: %d\n", atoi(temp));
#endif
		card_data[i] = atoi(temp);

		pos += 3;
	}


	return 0;

}

int card_flag_parse(int flag)
{
	int value_sum = 0;
	int cnt  = 0;

	while(flag > 0)
	{
		value_sum += (flag%10) * times[cnt++];
		flag = flag/10;	
	}

	return value_sum;
}
int card_generate(int *data, int length)
{
	int i, j, k, m, n, s, t;
	int r = 0;
	int flag = 0;
	int value_sum;

	for(i=1; i<RED_MAX-4; i++)  //max red is 28
	{
		data[0] = i;
		for(j=i+1; j<RED_MAX-3; j++)
		{
		  data[1] = j;
			for(k=j+1; k<RED_MAX-2; k++)
			{
			  data[2] = k;
				for(m=k+1; m<RED_MAX-1; m++)
				{
					data[3] = m;
					for(n=m+1; n<RED_MAX-0; n++)
					{
						data[4] = n;
						for(s=n+1; s<RED_MAX+1; s++)
						{
							data[5] = s;
							
							for(t=1; t<17; t++)
							{
							  data[6] = t;

							 flag =	link_compare(link_head, data, 7);
							 if(flag != 0)
							 {
							 		//printf("flag = %d\n", flag);

								 value_sum = card_flag_parse(flag);
								 if(value_sum > VALUE_MIN)
										write_file(fd, data, 7, flag, value_sum);
#if 0
							for(r=0; r<7; r++)
							printf("%5d", data[r]);
							printf("\n");
							sleep(1);
#endif
							 }
							}

							//if(r == 7)
								//r = 0;
						}
					}
				}
			}
		}
	}


	return 0;
}
