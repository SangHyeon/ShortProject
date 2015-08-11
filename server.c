#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/time.h>
#include "tcp.h"

int     Sockfd, flag;

void CloseServer()
{
        close(Sockfd);
        printf("\nTCP Server exit.....\n");

        exit(0);
}

main(int argc, char *argv[])
{
        int                                     newSockfd, cliAddrLen, n;
        struct sockaddr_in      cliAddr, servAddr;
        MsgType                         msg;

        pid_t pid;      

        signal(SIGINT, CloseServer);

//===============Template============================
        if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
                perror("socket");
                exit(1);
        }

        bzero((char *)&servAddr, sizeof(servAddr));
        servAddr.sin_family = PF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(SERV_TCP_PORT);

        if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
                perror("bind");
                exit(1);
        }

        listen(Sockfd, 5);
//=====================================================

        printf("TCP Server started.....\n");

        cliAddrLen = sizeof(cliAddr);
        while (1)  {
                newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
                if (newSockfd < 0)  {
                        perror("accept");
                        exit(1);
                }
        //=======create process ==============
                if( (pid = fork()) < 0){
                        perror("fork");
                        exit(1);
                }               
                //Child process
                else if( pid == 0 ){

                        close(Sockfd);  //child process not requried Sockfd

                        if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
                                perror("read");
                                exit(1);
                        }

//FIXME
                        FILE *src;
                        struct timeval mytime;
                        char time[256];

                        gettimeofday(&mytime, NULL);

                        if( (src = fopen(msg.data, "at")) == NULL){
                                perror("fopen");
                                exit(1);
                        }
                        
                        sprintf(time, "%d\n", mytime.tv_sec);   
                        fputs(time, src);

                        printf("Received request: %s.....", msg.data);
                        //코드 작성

                        msg.type = MSG_REPLY;
                        sprintf(msg.data, "This is a reply from %d.", getpid());

                        if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
                                perror("write");
                                exit(1);
                        }

                        printf("Replied.\n");


                        fclose(src);

                        close(newSockfd);
                        exit(0);
                }                       
                //parent process
                close(newSockfd);       // parent process not required newSockfd. 
        }
}
