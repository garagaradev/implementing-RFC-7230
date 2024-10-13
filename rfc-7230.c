/*
 * The `Host` header field indicates the host and port number of the server
 * to which the request is sent. If the request is for a specific resource, the server
 * must be able to provide that resource under the specified host.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 80
#define MAXLINE 1024

int main(){
  int sockfd;
  struct sockaddr_in server_addr;
  char *hostname = "www.example.com"; // change to a desired hostname
  char request[MAXLINE];

  // created a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }
  // provide a server address
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, "93.184.216.34", &server_addr.sin_addr); // ip address belongs to example.com
  
  //connect to the server 
  if (connect(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
    perror("Connection failed");
    close(sockfd);
    exit(EXIT_FAILURE);
  }

  // create HTTP request
  snprintf(request, sizeof(request),
           "GET / HTTP/1.1\r\n"
           "Host: %s\r\n"
           "Connection: close\r\n"
           "\r\n",hostname);
//send a request to a server 
  send(sockfd,request,strlen(request),0);
  printf("Request sent:\n%s", request);
  //accept a response from the server
  char response[MAXLINE];
  while(recv(sockfd, response, sizeof(response)-1,0)>0){
    printf("%s", response);
  }
  close(sockfd);
  return 0;
}
