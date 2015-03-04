#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include<fstream>
#include<iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")
int lis_fd = 0;

int main(void)
{
    
    int conn_fd = 0;
    struct sockaddr_in server_address;
    char send_Buffer[1025];
    int number_rv;
	WSADATA wsa_Data;
    int listen_Fd;

    if (WSAStartup(MAKEWORD(1,1), &wsa_Data) == SOCKET_ERROR) {
        printf ("Error initialising WSA.\n");
        return -1;
    }

    lis_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket retrieve success\n"); 

    memset(&server_address, '0', sizeof(server_address));
    memset(send_Buffer, '0', sizeof(send_Buffer));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(55554);

    if(bind(lis_fd, (struct sockaddr*)&server_address,sizeof(server_address)== SOCKET_ERROR))
	{
		return false;
	}

    if(listen(lis_fd,1) == -1)
	{
		printf("Error in listening\n");
	}

    while(1)
    {
        conn_fd = accept(lis_fd, (struct sockaddr*)NULL ,NULL);

        FILE *fp = fopen("sendingFile.txt","rb");
        if(fp==NULL)
        {
            printf("Error in opnening File");
            return 1;   
        }   

        while(1)
        {
            char * buffer=new char [256];
            int byte_read = fread(buffer,1,256,fp);
            printf("%d Bytes read  \n", byte_read);        

            if(byte_read > 0)
            {
                printf("Sending File \n");
                send(conn_fd, buffer, byte_read,0);
            }

            if (byte_read < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }


        }

        shutdown(lis_fd,SD_SEND);
		getchar();
    }


    return 0;
}