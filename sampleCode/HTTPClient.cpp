#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    char *address = argv[1];

   // create a socket
   int client_socket = socket(AF_INET, SOCK_STREAM, 0);

   // specify an address for the socket
   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(9002);
   inet_aton(address, (in_addr *)&server_address.sin_addr.s_addr);

   int connection_status = connect(client_socket, 
                                   (struct sockaddr *) &server_address, 
                                   sizeof(server_address));
   if(connection_status == -1)
   {
      printf("There was an error making a connection to the remote socket \n\n");
      return -1;
   }

   // send data to the server
   char request[4096] = "GET / HTTP/1.1\r\n\n";
   send(client_socket, request, sizeof(request), 0);

   // reveive data from the server
   char server_response[4096];
   recv(client_socket, server_response, sizeof(server_response), 0);

   // print out the server's response
   printf("The server sent the data: %s \n", server_response);

   // close the socket
   close(client_socket);
   
   return 0;
}