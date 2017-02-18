#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 90

void ChildProcess(int,int);
void ParentProcess(int,int);

void main()
{

	struct sockaddr_in serv_addr,cli_addr;

	int sockfd= socket(AF_INET, SOCK_STREAM,0);
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(3388);
	serv_addr.sin_addr.s_addr=htons(INADDR_ANY);

	int retval= bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

	retval=listen(sockfd,5);
	
	socklen_t actuallen=sizeof(cli_addr);
	int newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&actuallen);


	pid_t pid;
	pid = fork();
	if (pid == 0)
		ChildProcess(sockfd,newsockfd);
	else
		ParentProcess(sockfd,newsockfd);

}

void ChildProcess(int sockfd,int newsockfd) 
{	
	
	int recd;
	char buff[MAXSIZE];
	
	while(1)
	{

	recd= recv(newsockfd, buff, sizeof(buff),0);

	//printf("%s","Received Message:");	
	printf("\t%s\n",buff);

	if(strcmp(buff,"exit")==0)
		break;	
	}

	printf("%s","CLIENT DISCONNECTED");
	close(sockfd);
	close(newsockfd);
	exit(0);
}


void ParentProcess(int sockfd,int newsockfd) 
{
	int sentbytes;
	char buff[MAXSIZE];

	while(1)
	{

	//scanf("%s",buff);
	scanf ("%[^\n]%*c", buff);

	//printf("\n");
	sentbytes=send(newsockfd,buff,sizeof(buff),0);

	if(strcmp(buff,"exit")==0)
		break;	

	}

	
	close(sockfd);
	close(newsockfd);

}



























