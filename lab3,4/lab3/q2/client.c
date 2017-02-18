#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int main(int argc,char **args){

	//Variable Declaration//
	int sockfd;
	struct sockaddr_in serv_addr;
	char buff[256];
	int port = 9999;
	char *host="127.0.0.1";

	//Socket Creation//
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("Error creatng sockets");
		exit(0);
	}

	//Server Variable Specification//
	serv_addr.sin_port=htons(port);
	serv_addr.sin_addr.s_addr=inet_addr(host);
	serv_addr.sin_family=AF_INET;
	bzero(serv_addr.sin_zero,sizeof(serv_addr.sin_zero));

	//Socket Connect
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
		perror("Error connecting to the server");
		exit(0);
	}

	//Client Process//
	while(1){
		bzero(buff,sizeof(buff));
		printf("File Name => ");
		scanf("%s",buff);
		send(sockfd,buff,sizeof(buff),0);
		if(!strcmp(buff,"stop")) break;
		bzero(buff,sizeof(buff));
		recv(sockfd,buff,sizeof(buff),0);
		printf("%s",buff);
    if(!strcmp(buff,"File Not Found\n")) continue;
    printf("Word => ");
    bzero(buff,sizeof(buff));
    scanf("%s",buff);
    send(sockfd,buff,sizeof(buff),0);
    bzero(buff,sizeof(buff));
    recv(sockfd,buff,sizeof(buff),0);
    printf("%s\n",buff);
	}

	//Close //
	close(sockfd);

	return 0;
}
