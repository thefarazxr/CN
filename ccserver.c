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
 int sockfd,newsockfd,clilen, pid;
 struct sockaddr_in serv_addr,cli_addr;
 char a[50];
 sockfd=socket(AF_INET,SOCK_STREAM,0); //create a socket for communication
//AF_INET for IPv4 addresses
//SOCK_STREAM provides reliable, two-way, connection-based byte streams
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
 if(listen(sockfd,5)<0)
 {
printf("Listen failed\n");
exit(0);
 }
 clilen=sizeof(cli_addr);
 printf("Waiting for clients\n");
 while(1)
 {
 //Accept connection from clients
 newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr, (socklen_t *) &clilen);
pid = fork(); //create a new process to serve each request
if(pid==0)
{
//Child process serving requests will execute this block
while(1)
{
memset(a, 0, sizeof(a));
read(newsockfd,a,50);//Read message from client
//Also print the process id of the instance to check if concurrency works
printf("Instance : %d \n\tServer Recieved: %s\n",(int)getpid(),a);
write(newsockfd,a,50); //Return the same message to the client
if(!strcmp(a, "exit"))
{
printf("Closing connection : Instance %d\n", (int)getpid());
break;
}
}
close(newsockfd); //Close the connection
break; //Break the loop to end the process (serving process)
}
}
 return 0;
}