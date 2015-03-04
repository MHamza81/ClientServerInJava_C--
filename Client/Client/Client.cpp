#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

    int socket_fd = 0;
int main(void)
{
    int bytes_Recvd = 0;
    char recv_Buffer[256];
    memset(recv_Buffer, '0', sizeof(recv_Buffer));
    struct sockaddr_in server_address;
	 WSADATA wsa_Data;
    int socket_fd;

    if (WSAStartup(MAKEWORD(1,1), &wsa_Data) == SOCKET_ERROR) {
        printf ("Error initialising WSA.\n");
        return -1;
    }

    socket_fd= socket(AF_INET, SOCK_STREAM, 0);
	
   if(socket_fd < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2000); 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

    FILE *fp;
    fp = fopen("RecievedFile.txt","ab"); 
    if(NULL == fp)
    {
        printf("There is an error in opening file");
        return 1;
    }

	while((bytes_Recvd = recv(socket_fd, recv_Buffer, 256,0)) > 0)
    {
        printf("%d Bytes have been received from server \n",bytes_Recvd);    
 
        fwrite(recv_Buffer, 1,bytes_Recvd,fp);
   
    }

	getchar();

    if(bytes_Recvd < 0)
    {
        printf("\n Read Error \n");
    }

	
    return 0;
}