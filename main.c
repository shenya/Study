#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "link_list.h"
#include "card_file.h"

#define DATA_FILE "card.txt"
#define OBJ_FILE "obj_file"

int fd;
int main(void)
{
	int red[7] = {1, 3, 10, 20, 21, 26, 15};
	int fd;

	fd = open(OBJ_FILE, O_WRONLY|O_CREAT, 0666);
	if(fd < 0)
	{
		perror("fail to open");
		exit(1);
	}
	//write_file(fd, red, 7, 10010);
//	link_init(&link_head);

	//link_print(link_head);

	//read_file(DATA_FILE);

	//link_print(link_head);

//	link_compare(link_head, red, 7);

	//card_generate(red, 7);
	
	close(fd);

	return 0;
}
