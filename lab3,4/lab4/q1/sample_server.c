#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define MAXSIZE 90

int main()
{

	struct sockaddr_in serv_addr, cli_addr;
	char buff[MAXSIZE];
int sentbytes;


	int sockfd= socket(AF_INET, SOCK_STREAM,0);
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(3388);
	serv_addr.sin_addr.s_addr=htons(INADDR_ANY);

	int retval= bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));

	retval=listen(sockfd,5);
	
	socklen_t actuallen=sizeof(cli_addr);
	int newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&actuallen);

	int recd= recv(newsockfd, buff, sizeof(buff),0);

	puts(buff);
	printf("\n");

	pid_t pid=fork();

	if(pid==0)
	{

	sprintf(buff, "%d", getpid());
	sentbytes=send(newsockfd,buff,sizeof(buff),0);
	printf("Parent PID: %s",buff);

	//strcpy(buff,"");

	sprintf(buff, "%d", getppid());
	sentbytes=send(newsockfd,buff,sizeof(buff),0);
	printf("\nParent PPID: %s\n\n",buff);

	}	

	else if(pid>0)
	{

	sprintf(buff, "%d", getpid());
	sentbytes=send(newsockfd,buff,sizeof(buff),0);
	printf("Child PID: %s",buff);

	//strcpy(buff,"");

	sprintf(buff, "%d", getppid());
	sentbytes=send(newsockfd,buff,sizeof(buff),0);
	printf("\nChild PPID: %s\n\n",buff);

	}	


	close(sockfd);
	close(newsockfd);

}







