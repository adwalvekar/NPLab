#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 90 

main()
{
int sockfd,retval;
int recedbytes,sentbytes;
struct sockaddr_in serveraddr;
char buff[MAXSIZE], buff2[MAXSIZE],rpword[MAXSIZE],y[100];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
printf("\nSocket Creation Error");

}
printf("%i",sockfd);
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(3388);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
if(retval==-1)
{
printf("Connection error");

}

printf("enter the string\n");

scanf("%[^\n]s" ,buff);



sentbytes=send(sockfd,buff,sizeof(buff),0);

if(!sentbytes==-1)
{
printf("!!");
close(sockfd);
}
printf("enter word to replace\n");

scanf("%s",buff2);


sentbytes=send(sockfd,buff2,sizeof(buff2),0);

printf("Enter word to replce with\n");

scanf("%s", rpword);
	


sentbytes=send(sockfd,rpword,sizeof(rpword),0);



recedbytes=recv(sockfd,y,sizeof(y),0);

puts(y);

printf("\n");


close(sockfd);
}
