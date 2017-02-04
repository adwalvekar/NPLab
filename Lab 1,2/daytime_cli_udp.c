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

main()
{
	int s,r,recb,sntb,x;
	int sa;
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(7891);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	len=sizeof(server);

while(1){
	

	sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr *)&server, len);

	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr *)&server,&sa);
	if(recb==-1)
	{
		printf("\nMessage Recieving Failed");	
		close(s);
		exit(0);
	}
	
	printf("\nDate and time received  ");
	printf("%s", buff);

	if(!strcmp(buff,"stop"))
		break;
}
	close(s);

}
