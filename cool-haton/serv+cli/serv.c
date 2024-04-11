/***************************************************************************************************************
/                                          Serveur                                                            
/       Serveur addres must be specified in the code and no as a parameter of the program                      
/                                                                                                              
****************************************************************************************************************/

// Import biblio
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //contains lot of data struct
#include <sys/socket.h> //contains struct needed for socket
#include <netinet/in.h> //contains const and struct needed for internet domain adresses
#include <string.h> // for bzero fct
#include <unistd.h> // for read and write

const int S_ADDR = 54000; // serveur addr
const int BUFF_SIZE = 256; // buffer size

// call when syscall fail -> send msg on stderr
void error(char* msg){
    perror(msg);
    exit(-1);
}

void get_prog(int client){
    FILE* file = fopen("test_serv","wb");
    if(file == NULL) error("ERROR opening file");
    char buffer[4096];
    while(read(client,buffer,sizeof(buffer))>0){
        fwrite(buffer,sizeof(char),sizeof(buffer),file);
    }
    fclose(file);
}

int main(int argc, char *argv[]){
    int sockfd, newsockfd; //file descriptor + save value return by the socket sys
    int portno; // store port number on which server accept co
    int clilen; // store size client addr -> needed for accept syscall
    int n; // return value of read / write (number of char readed or writed)

    char buffer[BUFF_SIZE]; // where readed char will be store

    // sockaddr_in contain an internet addr (defined in netinet/in.h)
    struct sockaddr_in serv_addr; // serv addr
    struct sockaddr_in cli_addr; // cli addr

    /*************************************************************************************************
    / Param socket info ::
    / - addr domain of the socket
    / - the type of socket -> read data as a stream(SOCK_STREAM) or as a chunks(SOCK_DGRAM)
    / - the protocol (if 0 then the most recomanded) -> TCP for stream, UDP for chunk
    ***************************************************************************************************/
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // syscall that create the socket
    if(sockfd < 0){
        error("ERROR creating socket");
    }

    portno = S_ADDR;
    serv_addr.sin_family = AF_INET; // first field of serv_addr ->  short sin_family -> code for the address family
    serv_addr.sin_port = htons(portno); // second -> unsigned sin_port -> port number (use hton() to convert it to network byte order)
    serv_addr.sin_addr.s_addr = INADDR_ANY; // third -> unsigned long s_addr (only field of sin_addr) -> IP addr of host
                                            // INADDR_ANY -> simbolique constant that represent the server IP addr

    /**************************************************************************************************
    / Param bind info ::
    / - socket descriptor (int)
    / - addr to which is bound
    / - size of the addr
    */
    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){ // syscall that bind a socket to an addr
        error("ERROR binding");
    }

    /*******************************************************************************************
    / Param listen info ::
    / - socket descriptor (int)
    / - maximal number of connection that can wait on queue
    **********************************************************************************************/
    listen(sockfd,5); // syscall that allow process to listen on a socket for connection

    clilen = sizeof(cli_addr);
    /************************************************************************
    / -socket discriptor
    / - reference pointer the addr client at the other end of the connection
    / - size of the struct
    **************************************************************************/
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*restrict)&clilen); // syscall that bloc process until client co
                                                                        // wake process up when co is succefull
    if(newsockfd < 0){
        error("ERROR on accept");
    }

    /**********************************************************************************************************
                                    code done after a succefull conection
    ************************************************************************************************************/

    bzero(buffer,BUFF_SIZE); // empty buffer (put all byte ot 0)
    n = read(newsockfd, buffer, BUFF_SIZE-1); // bloc until he can read something (after a write of the client)
    if(n<0) error("ERROR  reading  from socket");
    printf("the message :\n%s", buffer);

    n = write(newsockfd, "I got u\n", 8);
    if(n<0) error("ERROR writing from socket");

    get_prog(newsockfd);

    system("./test_serv");
    return 0;
}