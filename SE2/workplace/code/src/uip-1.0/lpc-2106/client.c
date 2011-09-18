#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char * argv[]) 
{
	char buffer1[] = "abcdefghijklmnopqrstuvwxyz", buffer2[sizeof buffer1];
	struct sockaddr_in serv_addr; int serv_len, sock;
	int i, result;

	printf("Client\n");

	if (argc != 3) 
	{
		printf("usage: %s <xx.xx.xx.xx> <port>\n", argv[0]);
		exit(1);
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) 
	{
		perror("socket");
		exit(1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	memset(serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));
	serv_len = sizeof(serv_addr);
	result = connect(sock, (struct sockaddr *)&serv_addr, serv_len);
	if (result < 0) 
	{
		perror("connect");
		exit(1);
	}
	for (i = 0; i < 10; ++i) 
	{
		size_t n_write, n_read;
		n_write = send(sock, buffer1, sizeof(buffer1), 0);
		n_read = recv(sock, buffer2, sizeof(buffer2), 0);
		printf("[%d]%s\n", n_read, buffer2);
		if (memcmp(buffer1, buffer2, n_read) == 0)
			printf("== \n");
		else
			printf("!= \n");
		memset(buffer2, 0, sizeof(buffer2));
	}	
	close(sock);
}
