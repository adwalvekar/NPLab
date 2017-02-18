#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

#define MAXSIZE 90

int main()
{ struct sockaddr_in server;
	char buff[MAXSIZE];\
	int n,r,s;
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(7891);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");

	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");
	
  
 while ( (n = recv(s, buff, MAXSIZE,0)) > 0) {
      buff[n] = 0;        /* null terminate */
     if (fputs(buff, stdout) == EOF)
     printf("fputs error");
   }
   
   
   if (n < 0)
        printf("read error");


}

