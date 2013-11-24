#include <stdio.h>
#include "link_list.h"
#define STR_SIZE 100

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
