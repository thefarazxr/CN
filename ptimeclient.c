#include<stdio.h> 
#include<stdlib.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<sys/types.h> 
#include<string.h>
#include<unistd.h>
#include<time.h> 

int main()
{
int sockfd;
struct sockaddr_in serv_addr; time_t now;
char timestr[100];
char a[50],a1[50];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
printf("\n Socket Failed");
exit(0);
}
serv_addr.sin_family=AF_INET; 
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); 
serv_addr.sin_port=htons(13);
if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) 
{
printf("\n Connection Failed");
exit(0);
}
time(&now);
sprintf(timestr,"%s",ctime(&now));  //timestr= valueof(ctime(&now));

printf("%s",timestr);   //prints the O/P
close(sockfd);
}