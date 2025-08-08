#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

int main()
{
	WSADATA wsaData;
	int result;
	result = WSAStartup(MAKEWORD(2, 2), &result); 
	if (result != 0)
	{
		printf("Server could not start with error: %d\n", result);
		return 0;
	}
	else {
		printf("Server established connection to WinSock successfully\n");
	}
	SOCKET server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0); 
	if (server_socket == INVALID_SOCKET) {
		printf("Socket creation failed. Error code: %d\n", WSAGetLastError());
		WSACleanup(); 
		return 1;
	}
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY; 
	server_address.sin_port = htons(80); 
	if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		printf("Socket binding failed. Error code: %d\n", WSAGetLastError());
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}
	if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Socket listen failed. Error code: %d\n", WSAGetLastError());
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}
	printf("Web server successfully bound to port 80.\n");
	SOCKET client_socket;
	struct sockaddr_in client_address;
	int client_address_len = sizeof(client_address);
	while ((client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len)) != INVALID_SOCKET) { 
		printf("Client connected. \n");
		char request[1024];
		int bytes_received = recv(client_socket, request, 1024, 0); 
		if (bytes_received == SOCKET_ERROR) {
			printf("Error receiving client request. Error code: %d\n", WSAGetLastError());
			closesocket(client_socket);
			continue;
		}
		printf("Received request: %s\n", request);
		FILE *file = fopen("index.html", "r");
		if (file == NULL) {
			printf("Error opening file. Error code: %d\n", WSAGetLastError());
			closesocket(client_socket);
			continue;
		}
		char buffer[1024];
		fread(buffer, sizeof(char), 1024, file);
		char response[1024];
		sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n%s", strlen(buffer), buffer);
		int bytes_sent = send(client_socket, response, sizeof(response), 0); 
		if (bytes_sent == SOCKET_ERROR) {
			printf("Error sending response to client. Error code: %d\n", WSAGetLastError());
			closesocket(client_socket);
			continue;
		}
		closesocket(client_socket);
	}
	closesocket(server_socket);
	WSACleanup();
	return 0;
}
