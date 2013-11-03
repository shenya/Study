//date : 2013-11-09
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024


int cannot_do(int fd)
{
	FILE *fp = fdopen(fd, "w");
	fprintf(fp, "HTTP/1.1 501 Not Implemented\r\n");
	fprintf(fp, "Content-type: text/plain\r\n");
	fprintf(fp, "\r\n");
	fprintf(fp, "That command is not yet implemented\r\n");
	fclose(fp);

	return 0;
}
int start_server(int portnum)
{
	struct sockaddr_in server_sockaddr, client_sockaddr;
	int sin_size, recvbytes;
	int sockfd, client_fd;
	char buf[BUFFER_SIZE];

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
				perror("fail to socket");
				exit(-1);
	}

	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(1234);		
	//server_sockaddr.sin_port = htons(portnum);		
	server_sockaddr.sin_addr.s_addr = INADDR_ANY;

	bzero(&(server_sockaddr.sin_zero), 8);

	int i = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
	
	if(bind(sockfd, (struct sockaddr *)&server_sockaddr,sizeof(struct sockaddr)) == -1)
	{
		perror("fail to bin");
		exit(-1);
	}

	if(listen(sockfd, 20) == -1)
	{
		perror("fail to listen");
		exit(1);
	}

	return sockfd;															
	
}

int process_request(char *rq, int fd)
{
	char cmd[BUFSIZ], arg[BUFSIZ];

	if(fork() != 0)
	{
					return 1;
	}
	strcpy(arg, "./");
	if(sscanf(rq, "%s %s", cmd, arg+2) != 2)
		return 1;

	if(strcmp(cmd, "GET") != 0)
	{
		cannot_do(fd);
	}
	else
	{
			printf("this is get\n");
			printf("cmd %s\n", cmd);
			printf("arg %s\n", arg);
		cannot_do(fd);
	}


		return 0;
}
int main(int argc, char *argv[])
{
	
	int fd;
	FILE * fpin;
	int sock;
	char request[BUFSIZ];


	sock = start_server(0);

  printf("Hello world\n");
	while(1){
					printf("wait...\n");
		fd = accept(sock, NULL, NULL);
		printf("fd\n");
		fpin = fdopen(fd, "r");
		fgets(request, BUFSIZ, fpin);
		printf("request %s\n", request);

		process_request(request, fd);
	
		fclose(fpin);


	}



	return 0;

}
