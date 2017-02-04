#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define MAXSIZE 50

main()
{
int sockfd,retval;
int recedbytes,sentbytes, i,j, k;
struct sockaddr_in serveraddr;
char buff[MAXSIZE], buff2[MAXSIZE];
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

scanf("%s",buff);


for(i=0; buff[i] !='\0'; i++){
		k = 0;
		if(buff[i] >= 65 && buff[i] <= 90){
			k = buff[i];
			k = k-64;
			buff2[i] = k + '0';
		}
		if(buff[i] >= 97 && buff[i] <= 122){
			k = buff[i];
			k = k-96;
			buff2[i] = k+'0';
		}
		//printf("%d  \t %c \n", k,k);
	}
	
	

sentbytes=send(sockfd,buff2,sizeof(buff2),0);

if(!sentbytes==-1)
{
printf("!!");
close(sockfd);
}


recedbytes=recv(sockfd,buff,sizeof(buff),0);
puts(buff);
printf("\n");


close(sockfd);
}
