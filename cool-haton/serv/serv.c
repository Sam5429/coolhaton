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
#include <string.h>

const int S_ADDR = 54000; // serveur addr
const int BUFF_SIZE = 256; // buffer size

// call when syscall fail -> send msg on stderr
void error(char* msg){
    perror(msg);
    exit(-1);
}

void get_file(int client){
    FILE* file = fopen("codeCli/fonction.c","w");
    if(file==NULL)
        error("ERROR opening file\n");
    char buffer;
    int n;
    while(read(client,&buffer,sizeof(buffer))>0){
        n = fputc(buffer,file);
        if(n <= 0)
            error("ERROR writing in file\n");
    }
    printf("c'est fait\n");
    fclose(file);
}

// return false if file is corrupted
int analyse_file(FILE* file){
    char buffer[100];
    // test if there is syscall
    while(fgets(buffer,sizeof(buffer),file)){
        if(strstr(buffer,"system")!=NULL){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
    int sockfd, newsockfd; //file descriptor + save value return by the socket sys
    int portno; // store port number on which server accept co
    int clilen; // store size client addr -> needed for accept syscall
    //int n; // return value of read / write (number of char readed or writed)

    //char buffer[BUFF_SIZE]; // where readed char will be store

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
        error("ERROR creating socket\n");
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
        error("ERROR binding\n");
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
    while(1){
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*restrict)&clilen); // syscall that bloc process until client co
                                                                        // wake process up when co is succefull
    if(newsockfd < 0){
        error("ERROR on accept\n");
    }
    else{
        printf("client accepted\n");
    }

    /**********************************************************************************************************
                                    code done after a succefull conection
    ************************************************************************************************************/

    get_file(newsockfd);

    FILE* file = fopen("codeCli/fonction.c","r");
    if(file==NULL)
        error("ERROR opening file\n");
    if(analyse_file(file)){
        system("make");
        system("./main");
    }
    else{
        system("make clean");
        error("file corrupted");
    }
    fclose(file);

    return 0;
    }
}