// Server side C/C++ program to demonstrate Socket programming

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 80
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[102] = {0};
    char *hello = "Hello from server";
    printf("UID: %d\n", getuid());

    pid_t pid;   // new added element 
    printf("execve=0x%p\n", execve);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to port 80
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 80
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    // assignment 1: a part that sets up the socket(bind,listen, accept) and a separate part that processes the data from the client. ( read data)
    pid=fork();
    if (pid < 0)
        printf("error in fork!");
    else if (pid == 0)
	{
		printf("In child process, the process id is %d\n",getpid());
        	if(setuid(65534)== -1)
       	 	{
            		printf("fail to drop privilege\n");
            		exit(EXIT_FAILURE);
        	}
        	printf("UID: %d\n", getuid());
		valread = read(new_socket , buffer, 1024);
   		printf("%s\n", buffer);
    		send(new_socket , hello , strlen(hello) , 0);
     		printf("Hello message sent\n");
		printf("end of child process\n");	
     		exit(0);
	}
        // child process will end above, below two codes are in parent process
    wait(); 
    printf("end of parent process\n");
    
    	
}
