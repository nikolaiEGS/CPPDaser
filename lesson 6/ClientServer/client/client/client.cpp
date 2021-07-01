#include <string.h>
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <iostream>

int main(int argc , char *argv[])
{
	int s;
	sockaddr_in server;
	char server_reply[2000];
	std::string message; 

	if (((s = socket(AF_INET , SOCK_STREAM , 0)) < 0)) {
		std::cout << "couldn't create a socket! Exiting" << std::endl;	
		std::cout << strerror(errno) <<std::endl;
		return -1;
	}

	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server , sizeof(server)) < 0) {
		std::cout << "connect failed. Error" << std::endl;
		std::cout << strerror(errno) <<std::endl;
		return -1;
	}
	
	std::cout << "connected!" << std::endl;
	
	
	for (;;) {
		std::cout << "Enter message : " << std::endl;
		std::cin >> message;
		

		//Send some data
		if(send(s, message.c_str(), message.size() , 0) < 0) {
			std::cout << "Send failed" << std::endl;
			std::cout << strerror(errno) <<std::endl;
			return -1;
		}
		
		//Receive a reply from the server
		if (recv(s, server_reply , 2000 , 0) < 0) {
			std::cout << "recv failed" << std::endl;
			std::cout << strerror(errno) <<std::endl;
			break;
		}
		
		std::cout <<"server reply:\n" << server_reply << std::endl;
	}
	
	close(s);
	return 0;
}
