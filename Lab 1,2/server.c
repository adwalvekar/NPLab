#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define MAXSIZE 90

main()
{
int sockfd,newsockfd,retval;
socklen_t actuallen;

int recedbytes,sentbytes, j, i,k, flag=0;
struct sockaddr_in serveraddr,clientaddr;

char buff[MAXSIZE],buff2[MAXSIZE], k1;
int a=0;
sockfd=socket(AF_INET,SOCK_STREAM,0);

if(sockfd==-1)
{
printf("\nSocket creation error");
}

serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
retval=bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
if(retval==-1)
{
printf("Binding error");
close(sockfd);
}

retval=listen(sockfd,1);
if(retval==-1)
{
close(sockfd);
}

actuallen=sizeof(clientaddr);
newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);


if(newsockfd==-1)
{
close(sockfd);
}




	recedbytes=recv(newsockfd,buff,sizeof(buff),0);
	if(recedbytes==-1)
	{
		close(sockfd);
		close(newsockfd);
	}
	
	
	


	
		for(i=0; buff[i] !='\0'; i++){
		k = 0;
		
		k = (int)buff[i];
		k1 = k- '0'+ 64;
			
		buff2[i] = k1 ;
		
		//printf("%d  \t %c \n", k,k);
	}
	puts(buff);
	printf("\n");
	puts(buff2);
	printf("\n");

 recedbytes=send(newsockfd,buff2,sizeof(buff2),0);



close(sockfd);
close(newsockfd);
}

