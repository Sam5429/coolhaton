#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h> 
#include <unistd.h>


const int S_ADDR = 54000; // serveur addr
const int BUFF_SIZE = 256;

void error(char *msg)
{
  perror(msg);
  exit(0);
}

void send_file(int serv){
  FILE* file = fopen("code/fonction.c","r");
  if(file==NULL) 
    error("ERROR opening file\n");
  char c;
  int n;
  while((c=fgetc(file))!=EOF){
    n = write(serv,&c,sizeof(c));
    if(n<0)
      error("ERROR writing to socket\n");
  }
  if(c!=EOF)
    error("ERROR sending file\n");
  fclose(file);
}

int main(int argc, char *argv[])
{
  int sockfd, portno;
  struct sockaddr_in serv_addr;

  //char buffer[BUFF_SIZE];
  portno = S_ADDR;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("ERROR opening socket\n");
  portno = S_ADDR;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY; 
  serv_addr.sin_family = AF_INET;
  if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) {
    error("ERROR connecting\n");
  }
  else{
    printf("connected\n");
  }
  send_file(sockfd);
  return 0;
}
