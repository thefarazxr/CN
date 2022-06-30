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
int sockfd;
struct sockaddr_in serv_addr;
char a[50],a1[50], *pos;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
printf("socket failed\n");
exit(0);
}
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 //Change address to server's IPv4 address, dont change if on same machine

 serv_addr.sin_port=htons(3100);
if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
{
printf("Connection failed\n");
exit(0);
}
memset(a, 0, sizeof(a));
while(1)
{
printf("Enter the msg :\n");
fgets(a,sizeof(a), stdin); // read entire line into a[]
//This blocks removes trailing newline character (if present) left form fgets
if( (pos = strchr(a, '\n'))!= NULL)
*pos = '\0';
write(sockfd,a,50);
read(sockfd,a1,50);
printf("Client Received the msg: %s\n",a1);
if(!strcmp(a, "exit"))
{
printf("Closing connection\n");
break;
}
}
close(sockfd);
if(!strcmp(a1,"exit"))
printf("Closing client program\n");
return 0;
}