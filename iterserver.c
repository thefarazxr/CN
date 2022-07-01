#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>  
int main()
{
 int sockfd,newsockfd,clilen;
 struct sockaddr_in serv_addr,cli_addr;
 char msg[50];
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 if(sockfd<0)
 {
 printf("\n Socket Failed");
 exit(0);
 }
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 serv_addr.sin_port=htons(3456);
 if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
 {
 printf("\n Bind Failed");
 exit(0);
 }
 clilen=sizeof(cli_addr);
 recvfrom(sockfd,msg,80,0,(struct sockaddr *)&cli_addr,&clilen);
 printf("Server Received: %s",msg);
 sendto(sockfd,msg,80,0,(struct sockaddr *) &cli_addr,clilen);
 write(sockfd);
 close(sockfd);
 }