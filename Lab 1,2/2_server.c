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

int recedbytes,sentbytes, j, i, k , flag=0;
struct sockaddr_in serveraddr,clientaddr;

char buff[MAXSIZE], stri[MAXSIZE], str[MAXSIZE][MAXSIZE], rp[MAXSIZE], buff3[MAXSIZE];
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
	
	
	puts(buff);
	printf("\n");
	
	recedbytes=recv(newsockfd,stri,sizeof(stri),0);
	
	
	printf("%s",stri);
	printf("\n");
	
	
	recedbytes=recv(newsockfd,rp,sizeof(rp),0);
	
	
	printf("%s",rp);
	printf("\n");
	

	
	
	
	for (k=0; k<strlen(buff); k++)
	{
 
	   if (buff[k]!=' ')
	     {
	       str[i][j] = buff[k];
	       j++;
	     }
	   else
	     {
	       str[i][j]='\0';
	       j=0; i++;
	     }
	}
	str[i][j]='\0';

	
       for (k=0; k<=i; k++)
	{
	    if(strcmp(str[k],stri)==0)
	       strcpy(str[k],rp);
	       strcat(buff3,str[k]);
	       strcat(buff3," ");	
	      
	      
       }
	
	//printf("%s",buff3);
	

	sentbytes=send(newsockfd,buff3,sizeof(buff3),0);
	
	
	
	if(sentbytes==-1)
	{       printf("sending error");
		close(sockfd);
		close(newsockfd);
	}	





close(sockfd);
close(newsockfd);
}

