#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <iostream>

int main(int argc , char *argv[]) {
	int s, client_sock, c, read_size;
	sockaddr_in server, client;
	char client_message[2000];
	
	
	if (((s = socket(AF_INET , SOCK_STREAM , 0)) < 0)) {
		std::cout << "Could not create socket" << std::endl;
		std::cout << strerror(errno);
		return -1;
	}

	std::cout << "Socket created" << std::endl;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if (bind(s, (sockaddr *)&server, sizeof(server)) < 0) {
		std::cout << "bind failed. Error" << std::endl;
		std::cout << strerror(errno);
		return -1;
	}

	std::cout << "bind done" << std::endl;
	
	//Listen
	listen(s, 3);
	
	//Accept and incoming connection
	std::cout << "Waiting for incoming connections..." << std::endl;
	c = sizeof(sockaddr_in);
	
	//accept connection from an incoming client
	if ((client_sock = accept(s, (sockaddr *)&client, (socklen_t*)&c)) < 0) {
		std::cout << "accept failed" << std::endl;
		std::cout << strerror(errno);
		return -1;
	}

	std::cout << "Connection accepted" << std::endl;
	
	//Receive a message from client
	while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 ) {
		//Send the message back to client
		write(client_sock , client_message , strlen(client_message));
	}
	
	if(read_size == 0) {
		std::cout << "Client disconnected" <<std::endl;
	}
	else if(read_size == -1) {
		std::cout << "recv failed" << std::endl;
	}
	
	return 0;
}
