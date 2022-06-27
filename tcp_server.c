#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void handle_message(int connfd)
{
    char buff[MAX];
    int n;

    char pleasant_message[MAX] = "Hello";

    //infinite loop for messages
    for (;;)
    {
        bzero(buff, MAX);

        //read message from client and copy it into buffer
        read(connfd, buff, sizeof(buff));

        //print buffer which contains the client contents
        printf("%s\n", buff);
        bzero(buff, MAX);
        n = 0;

        //send message to client
        write(connfd, pleasant_message, sizeof(pleasant_message));

    }
}

int main (void)
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creating failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created...\n");

    bzero(&servaddr, sizeof(servaddr));


    //assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    //binding socket to given IP & verification
   if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0)
   {
       printf("Socket bind failed...\n");
       exit(0);
   }
   else
        printf("Socket successfully binded...\n");

   //server is now ready to listen
   if ((listen(sockfd, 5)) != 0)
   {
       printf("Listen failed...\n");
       exit(0);
   }
   else
       printf("Server listening...\n");

   len = sizeof(cli);

   //accept data packet from client & verification
   if((connfd = accept(sockfd, (SA*)&cli, &len)) < 0)
   {
       printf("Server accept failed...\n");
   }
   else
       printf("Server accepted the client...\n");

   handle_message(connfd);

   close(sockfd);
}



