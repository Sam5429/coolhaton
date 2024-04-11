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

void send_prog(int serv){
    FILE* file = fopen("test_cli","rb");
    if(file==NULL) error("ERROR opening file");
    char buffer[4096] = "";
    // fread -> buffer, size of 1 block, number of block, file
    while(feof(file)==0){
        fread(buffer,sizeof(char),sizeof(buffer),file);
        write(serv, buffer, sizeof(buffer));
    }
    fclose(file);
}

int main(int argc, char *argv[])
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;

  //char buffer[BUFF_SIZE];
  portno = S_ADDR;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("ERROR opening socket");
  portno = S_ADDR;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY; 
  serv_addr.sin_family = AF_INET;
  if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");

  //bzero(buffer,256);
  char buffer[] = "hello world\n";
  n = write(sockfd,buffer,strlen(buffer));
  if (n < 0)
    error("ERROR writing to socket");
  bzero(buffer,strlen(buffer));
  n = read(sockfd,buffer,13);
  if (n < 0)
    error("ERROR reading from socket");
  printf("%s",buffer);

  send_prog(sockfd);
  return 0;
}
