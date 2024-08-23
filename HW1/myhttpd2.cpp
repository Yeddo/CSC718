
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

///-----------------------------------------------------------------
///   Name:		JB
///   Class:		CSC 718
///   Professor:	Dr. Yong Wang
///   Assignment:	#1
///   Due Date:	30 September 2021 
///   File Name: 	myhttpd2
///   Description:	simple http server w/threading
///   Notes:		<Notes>
///-----------------------------------------------------------------

int host_port = 8080;

void usage()
{
	printf("myhttpd, a simple webserver\n");
	printf("ver 1.0, 2014\n");
	printf("Usage Summary: myhttpd -h -p portno \n");
	printf("	-h: display the summary\n");
	printf("	-p: change default port number for example: -p 8080\n\n");
}

void * httpHandler(void *p_socketfd)
{
	int socketfd = *((int*)p_socketfd); // cast void pointer to int pointer and copy pointer value to local int
	free(p_socketfd); // Free pointer because it's not needed anymore
	char buffer[1024];
	int buffer_len = 1024;
	int bytecount;
	
	memset(buffer, 0, buffer_len);
	if ((bytecount = recv(socketfd, buffer, buffer_len, 0))== -1) //Handles receiving data from the client
	{
		fprintf(stderr, "Error receiving data %d\n", errno);
		return NULL;
	}

	printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);

	strcpy(buffer, "HTTP/1.1 200 OK\nServer: demo\nContent-Length: 37\nConnection: close\nContent-Type: html\n\n<html><body>Welcome to my first page!</body></html>");

	if ((bytecount = send(socketfd, buffer, strlen(buffer), 0))== -1) //Handles sending data to the client
	{
		fprintf(stderr, "Error sending data %d\n", errno);
		return NULL;
	}

	printf("Sent bytes %d\n", bytecount);
	
	sleep(1); // To put a small delay in to test the threading compared to not threaded more realisticly.
	
	close(socketfd); // Close socket
	return NULL;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in my_addr;

	int hsock;
	int * p_int ;
	//int err;
	int socketfd;

	socklen_t addr_size = 0;
	//int* csock;
	sockaddr_in sadr;
	pthread_t thread_id=0;

	int opt = 0;
	opt = getopt( argc, argv,"dhl:p:r:t:n:s:" );

	while (opt != -1)
	{
		switch (opt)
		{
			case 'h':
                		usage();
                		exit(0);

			case 'p':
				host_port = atoi(optarg);
                  		break;

			case 'r':
				break;
		}

		opt = getopt( argc, argv, "dhl:p:r:t:n:s:" );
	}

	hsock = socket(AF_INET, SOCK_STREAM, 0); //Create socket
	if (hsock == -1) // Could not create socket
	{
		printf("Error initializing socket %d\n", errno);
		exit(-1);
	}
	
	p_int = (int*)malloc(sizeof(int)); //allocate space on heap
	*p_int = 1; // store 1 in pointer

	if ((setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) )
	{
		printf("Error setting options %d\n", errno);
		free(p_int); // free memory
		exit(-1);
	}
	free(p_int); // free memory

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);

	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY ;

	if (bind(hsock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 )
	{
		fprintf(stderr,"Error binding to socket, make sure nothing else is listening on this port %d\n",errno);
		exit(-1);
	}

	if (listen(hsock, 10) == -1 )
	{
		fprintf(stderr, "Error listening %d\n",errno);
		exit(-1);
	}

	//Now lets do the server stuff
	printf("myhttpd server listening on port %d\n", host_port);

	addr_size = sizeof(sockaddr_in);

	while (true)
	{
		printf("waiting for a connection\n");
		if ((socketfd = accept( hsock, (sockaddr*)&sadr, &addr_size))!= -1)
		{
			//httpHandler(socketfd); // call data receive handler httpHandler()
			printf("Received connection from %s\n",inet_ntoa(sadr.sin_addr));
			
			// Threading ...
			int *pclient = (int*)malloc(sizeof(int)); //Allocate some space on heap
			*pclient = socketfd; //Assigning fd# to pointer
			pthread_create(&thread_id, NULL, httpHandler, pclient); // Create the thread and call httpHandler. pclient/argument needs to be a pointer!
		}
		else
		{
			fprintf(stderr, "Error accepting %d\n", errno);
		}
	}
}


