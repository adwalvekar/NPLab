#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

void ascendOrder(char *ostr){
    char buff[256];
    strcpy(buff,ostr);
    int n= strlen(buff);
  	for(int i=0;i<n;i++){
  		for(int j=i+1;j<n;j++){
  			if(buff[i]>buff[j]){
  				char temp=buff[i];
  				buff[i]=buff[j];
  				buff[j]=temp;
  			}
  		}
  	}
  sprintf(ostr,"Ascending Order : %s",buff);
}


int main(int argc,char **args){

	//Variable Declaration//
	  int sockfd,listenfd;
	  struct sockaddr_in cli_addr,serv_addr;
	  int cli_len = sizeof(cli_addr);
	  char buff[256];
	  int port = 9999;
	  char *host = "127.0.0.1";
	  FILE *f;

	  //Socket Creation//
	  listenfd=socket(AF_INET,SOCK_STREAM,0);
	  if(listenfd<0){
	    perror("Error Creating Sockets");
	    exit(0);
	  }

	  //Server address specification//
	  serv_addr.sin_family=AF_INET;
	  serv_addr.sin_port=htons(port);
	  serv_addr.sin_addr.s_addr=inet_addr(host);
	  bzero(serv_addr.sin_zero,sizeof(serv_addr.sin_zero));

	  //Socket Binding//
	  if(bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
	    perror("Error Binding Socket");
	    close(listenfd);
	    exit(0);
	  }

	  //Socket listen//
	  listen(listenfd,5);

	  //Socket Accept
	  sockfd=accept(listenfd,(struct sockaddr*)&cli_addr,&cli_len);
	  if(sockfd<0){
	    perror("Error Accepting Connection");
	  }


	//Server Process//
	while(1){
		bzero(buff,sizeof(buff));
		recv(sockfd,buff,sizeof(buff),0);
		printf("%s\n",buff);
		if(!strcmp(buff,"stop"))break;
		f=fopen(buff,"r");
		if(f==NULL){
			bzero(buff,sizeof(buff));
			strcpy(buff,"File Not Found\n");
			send(sockfd,buff,sizeof(buff),0);
			continue;
		}
    bzero(buff,sizeof(buff));
    strcpy(buff,"File Found\n");
    send(sockfd,buff,sizeof(buff),0);
		bzero(buff,sizeof(buff));
		int c,i=0;
		while((c=getc(f))!=EOF) buff[i++]=c;
    ascendOrder(buff);
		send(sockfd,buff,sizeof(buff),0);
	}

	//Close//
	close(sockfd);
	close(listenfd);
	fclose(f);
	return 0;
}
