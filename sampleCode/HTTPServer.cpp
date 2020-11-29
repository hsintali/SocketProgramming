#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
    // open a file to serve
    FILE *html_data = fopen("index.html", "r");

    char response_data[4096];
    fgets(response_data, 4096, html_data);

    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);

    // create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;
    while(1)
    {
        client_socket = accept(server_socket, NULL, NULL);

        // reveive data from the client
        char client_requeat[4096];
        recv(client_socket, client_requeat, sizeof(client_requeat), 0);

        // print out the client's requeat
        printf("The client sent the data: %s \n", client_requeat);

        // send the message
        send(client_socket, http_header, sizeof(http_header), 0);

        // print out the server's response
        printf("The server sent the data: %s \n", http_header);
        printf("\n\n");

        // close the socket
        close(client_socket);
    }

    close(server_socket);

    return 0;
}