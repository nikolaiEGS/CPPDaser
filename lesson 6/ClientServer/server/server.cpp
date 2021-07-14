#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write
#include <iostream>
#include <string>

int main(int argc , char *argv[]) {
	int s, client_sock, c;
	std::size_t read_size;
	std::size_t read_counter = 0;
	sockaddr_in server, client;

	char client_message[2000] = {0};
	
	
	if (((s = socket(AF_INET , SOCK_STREAM , 0)) < 0)) {
		std::cout << "Could not create socket" << std::endl;
		std::cout << strerror(errno);
		return -1;
	}

	std::cout << "Socket created" << std::endl;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("192.168.58.130");
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
	
	char lenOfIm[100]= {0};

	if( (read_size = recv(client_sock , lenOfIm, 100 , 0)) > 0 ) {
		write(client_sock , (std::string("waiting for message of len ") + lenOfIm).c_str(), 1000);
		std::cout << "client message len: " << lenOfIm << std::endl;
		read_size = 0;
        }
	
	std::size_t bufImageLen = atoi(lenOfIm);
	char imageBuff[bufImageLen+1] = {0};

	while( (read_size = recv(client_sock , &imageBuff[read_counter], bufImageLen-read_counter , 0)) > 0 ) {
		read_counter += read_size;
		std::cout << "client message len: " << read_counter << std::endl;

		if (read_counter == bufImageLen) {
			break;
		}
	}
	
	
	send(client_sock , (std::string("Got your message of len: ") + std::to_string(read_counter)).c_str(), 1000, 0);
	
	if(read_size == 0) {
		std::cout << "Client disconnected" <<std::endl;
	}
	else if(read_size == -1) {
		std::cout << "recv failed" << std::endl;
	}
	
	return 0;
}
