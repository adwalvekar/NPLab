#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 90

void ChildProcess(int);
void ParentProcess(int);

void main()
{

	struct sockaddr_in serv_addr;

	int sockfd= socket(AF_INET, SOCK_STREAM,0);
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(3388);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int retval= bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

	retval=connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	
	pid_t pid;
	pid = fork();
	if (pid == 0)
		ChildProcess(sockfd);
	else
		ParentProcess(sockfd);

}

void ChildProcess(int sockfd) 
{	
	
	int recd;
	char buff[MAXSIZE];
	
	while(1)
	{

	recd= recv(sockfd, buff, sizeof(buff),0);

	//printf("Received Message:");	
	printf("\t%s\n",buff);

	if(strcmp(buff,"bye")==0)
		break;	
	}

	printf("%s","SERVER DISCONNECTED");
	close(sockfd);
	exit(0);
}


void ParentProcess(int sockfd) 
{
	int sentbytes;
	char buff[MAXSIZE];

	while(1)
	{

	//printf("%s","Sent Message: ");
	//scanf("%s",buff);
	scanf ("%[^\n]%*c", buff);

	//printf("\n");
	sentbytes=send(sockfd,buff,sizeof(buff),0);

	if(strcmp(buff,"bye")==0)
		break;	

	}

	
	close(sockfd);

}



























