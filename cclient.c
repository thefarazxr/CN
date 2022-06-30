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
int sockfd, servlen;
struct sockaddr_in serv_addr;
char a[50],a1[50], *pos;
servlen = sizeof(serv_addr);
sockfd=socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
{
printf("socket failed\n");

exit(0);
}
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 //Change address to server's IPv4 address, dont change if on same machine
serv_addr.sin_port=htons(3100);
memset(a, 0, sizeof(a));
printf("Enter the msg :\n");
fgets(a,sizeof(a), stdin); // read entire line into a[]
//This blocks removes trailing newline character (if present) left form fgets
if( (pos = strchr(a, '\n'))!= NULL)
*pos = '\0';
if(sendto(sockfd, a, 50, 0, (struct sockaddr *)&serv_addr, (socklen_t) servlen) < 0)
{
printf("UDP client : Message sending failed\nExiting...");
close(sockfd);
exit(1);
}
if(recvfrom(sockfd, a1, 50, 0, (struct sockaddr *)&serv_addr,(socklen_t *) &servlen) < 0)
{
printf("UDP client : Message receiveing failed\nExiting...");
close(sockfd);
exit(1);
}
printf("Client Received the msg: %s\n",a1);
close(sockfd);
return 0;
}