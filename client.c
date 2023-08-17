#include "headers.h"
#include "declarations.h"

int main(int argc , char *argv[])
{
    struct sockaddr_un name;
    int data_socket;
    int ret;
    int i;
    char buffer[BUFFERSIZE];


    data_socket = socket(AF_UNIX,SOCK_STREAM,0);
    if (data_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    printf("Client Socket created \n");
    memset(&name, 0,sizeof(struct sockaddr_un));
    name.sun_family=AF_UNIX;
  strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
//name.sun_path[sizeof(name.sun_path) - 1] = '\0';  // Ensure null-termination


    ret = connect(data_socket,(const struct sockaddr *)&name,sizeof(struct sockaddr_un));

    if(ret == -1)
    {
        fprintf(stderr,"The server is down \n");
        exit(EXIT_FAILURE);
    }

    //send data to the server 

    do {
    printf("Enter the data to send to the server \n");
    scanf("%d",&i);
    ret = write(data_socket,&i,sizeof(int));
    if (ret == -1 )
    {
        perror("write");
        break;
    }
    printf("Number of bytes sent %d\t Data sent %d\n",ret,i);
    }while(i);

    //request result 

    memset(buffer,0,BUFFERSIZE);

    ret = read(data_socket,buffer,BUFFERSIZE);
    if (ret ==-1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Received from server : %s\n",buffer);

    close(data_socket);

    exit(EXIT_SUCCESS);
}