#include "headers.h"
#include "declarations.h"

int main(int argc, char * argv[]) 
{
   struct sockaddr_un name; 
/**
Create a new socket of type TYPE in domain DOMAIN, using
   protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
   Returns a file descriptor for the new socket, or -1 for errors. 

extern int socket (int __domain, int __type, int __protocol) __THROW;
***/

//struct sockaddr_un {
  //  sa_family_t sun_family;     /* AF_UNIX */
    //char        sun_path[108];  /* pathname */
//};

int ret;
int connection_socket;
int data_socket;
int result;
int data;
char buffer[BUFFERSIZE];

//if there exists a program which has same socket , then this program destroys the other socket and takes the ownership creating new socket here
unlink(SOCKET_NAME);
//Create the master socket 
connection_socket = socket(AF_UNIX,SOCK_STREAM,0);
if(connection_socket == -1)
{
    perror("socket");
    exit(EXIT_FAILURE);
}
printf("Master socket created\n");

memset(&name,0,sizeof(struct sockaddr_un));

name.sun_family = AF_UNIX;
strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
//name.sun_path[sizeof(name.sun_path) - 1] = '\0';  // Ensure null-termination


//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
//
//purpose of bind : it dictates the OS , criteria for receiving the data
// if the sender application sends the data to "address passed here" , then the data needs to be delivered to this process
//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

ret = bind(connection_socket,(const struct sockaddr *)&name,sizeof(struct sockaddr_un));
if (ret == -1)
{
    perror("bind");
    exit(EXIT_FAILURE);
}
printf("bind() call succeded \n");

//int listen(int sockfd, int backlog);
//socket that will be used to accept incoming connection requests 
//

ret = listen(connection_socket,20);
if (ret == -1)
{
    perror("listen");
    exit(EXIT_FAILURE);
}

printf("Socket is in listening mode , ready to accept connection\n");

for(;;)//infinte loop so that the server runs infinitely
{
    printf("waiting on accept() syscall \n");

    data_socket = accept(connection_socket,NULL,NULL);
    //why NULL

    if(data_socket==-1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted from the clinet\n");
    result =0 ;
    for(;;) // server purpose of summation till recieves zero as input from client
    {
        //clear the buffer
        memset(buffer,0,BUFFERSIZE); 
        // read the data from client 
        printf("waiting for data from client\n");

        ret = read(data_socket,buffer,BUFFERSIZE);

        if (ret==-1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        memcpy(&data,buffer,sizeof(int));
        if(data == 0 )
        break;
        result+= data;
    }

    //send data back to the client 

    memset(buffer,0,BUFFERSIZE);
    sprintf(buffer,"Result = %d",result);

    printf("'sending final result back to the client\n");
    
    ret = write(data_socket,buffer,BUFFERSIZE);
    if (ret == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(data_socket);
}
close(connection_socket);
printf("Connection closed\n");

unlink(SOCKET_NAME);
exit(EXIT_SUCCESS);

}