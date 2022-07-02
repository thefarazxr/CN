#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main()
{
 int sockfd, n,clilen, pid;
 struct sockaddr_in serv_addr,cli_addr;
 char a[50];
 sockfd=socket(AF_INET,SOCK_DGRAM,0); //create a socket for communication
 //AF_INET for IPv4 addresses
//Communication with Datagrams (UDP - Connectionless, non-reliable)
//0 for default protocol for the socket
 if(sockfd<0)
 {
 printf("socket failed\n");
 exit(0);
 }
 serv_addr.sin_family = AF_INET;
 //Set address to accept connection from any client with any IP address
 serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 //INADDR_ANY - Accept connections from any address (client)
//change address to the client IPv4 Address to accept only on client
 if(serv_addr.sin_addr.s_addr < 0)
 {
printf("Invalid IP address: Unable to decode\n");

exit(0);
}
 serv_addr.sin_port = htons(3100);
 if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
 {
printf("Bind failed\n");
exit(1);
 }
 clilen=sizeof(cli_addr);
 printf("Waiting for clients\n");
 while(1)
 {
memset(a, 0, sizeof(a));
//Read messages from clients (without connection) into a[]; type "man 2 recvfrom" in terminal
//for details
n = recvfrom(sockfd, a, 50, 0, (struct sockaddr *)&cli_addr, (socklen_t *) &clilen);
if(n>0)
{
pid = fork(); //create a new process to serve each request
if(pid==0)
{
//Child process serving requests will execute this block
//read(newsockfd,a,50); //Read message from client
//Also print the process id of the instance to check if concurrency works
printf("Instance : %d \n\tServer Recieved: %s\n",(int)getpid(),a);
if( sendto(sockfd, a, 50, 0, (struct sockaddr *)&cli_addr, (socklen_t) clilen) < 0)
//Return the same message to the client
{
printf("UDP sending failed\nExiting... \n");
close(sockfd);
 exit(1);
}
 close(sockfd); //Close the connection
 break; //Break the loop to end the process (serving process)
}
}
else
{
printf("UDP receiving failed\nExiting... \n");
close(sockfd);
exit(1);
}
}
 return 0;
}
