#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

void countOccurrence(char *ostr,char *rplcr){
  int i=0,j=0,c=0;
  while(i<strlen(ostr)){
    while(i<strlen(ostr) && j<strlen(rplcr)){
      if(ostr[i]==rplcr[j]){
          i++;
          j++;
          if(j==strlen(rplcr)-1){
            c++;
          }
      }
      else{
        i++;
        j=0;
      }
    }
    j=0;
  }
  sprintf(ostr,"No. of Occurrences : %d",c);
}


int main(int argc,char **args){

	//Variable Declaration//
	  int sockfd,listenfd;
	  struct sockaddr_in cli_addr,serv_addr;
	  int cli_len = sizeof(cli_addr);
	  char buff[256],str[256];
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
    bzero(str,sizeof(str));
    strcpy(str,buff);
    bzero(buff,sizeof(buff));
    recv(sockfd,buff,sizeof(buff),0);
    countOccurrence(str,buff);
		send(sockfd,str,sizeof(str),0);
	}

	//Close//
	close(sockfd);
	close(listenfd);
	fclose(f);
	return 0;
}
