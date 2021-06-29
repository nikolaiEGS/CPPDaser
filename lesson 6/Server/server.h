#pragma once
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

class ServerAPI {
	const int portNumber = 8080;

public:

	bool prepareServerSocket() {

	}
	
	void waitForClient() {

	}
};