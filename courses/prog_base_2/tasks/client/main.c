#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

void getIP (struct hostent * remoteHost, const char * host_name, char ** ip)
{
    remoteHost = gethostbyname(host_name);
	(*ip) = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n\n", *ip);
}

void createSocket (SOCKADDR_IN * recvSockAddr, SOCKET * recvSocket, char * ip)
{
    memset(recvSockAddr, 0, sizeof(*recvSockAddr));

    recvSockAddr->sin_port = htons(PORT);
    recvSockAddr->sin_family = AF_INET;
    recvSockAddr->sin_addr.s_addr = inet_addr(ip);

	(*recvSocket) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void request(SOCKET recvSocket,const char * host_name)
{
    char request[200];
    sprintf(request, "GET /var/7 HTTP/1.1\r\nHost: %s\r\n\r\n", host_name);
    send(recvSocket, request, strlen(request), 0);
}

void secretRequest(SOCKET recvSocket,const char * host_name, char * buff)
{
    char request[200];
    char * secret = malloc(50 *sizeof(char));
    strcpy(secret, strstr(buff, "secret"));
    sprintf(request, "GET /var/7?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
    send(recvSocket, request, strlen(request), 0);
    free(secret);
}

void postRequest(SOCKET recvSocket,const char * host_name, int cnt)
{
    char request[200];
    char tmp[50];
    sprintf(tmp, "result=%i", cnt);
    sprintf(request, "POST /var/7 HTTP/1.1\r\nHost: %s\r\n"
            "Content-length:%d\r\n\r\n%s\r\n", host_name,strlen(tmp),tmp);
    send(recvSocket, request, strlen(request), 0);
}

void receive(char * buffer, SOCKET * recvSocket) {
    memset (buffer, 0, MAXBUFLEN);
    recv (*recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    printf ("%s\n\n", buffer);
}

int calcVowels(char * buffer)
{
    int cnt = 0;
    char let[6] = "aeyuio";
    char let2[6] = "AEYUIO";
    for(int i = 0; i < 6; i++)
    {
        if(buffer[0] == let2[i])
            cnt++;
    }

    for(int i = 1; i < strlen(buffer) - 1; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(buffer[i] == ' ' && buffer[i + 1] == let[j])
                cnt++;
        }
    }
    return cnt;
}

int main () {
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int cnt = 0;

    struct hostent * remoteHost;
    char * ip;
    const char *  host_name = "pb-homework.appspot.com";

    char * buffer = malloc(MAXBUFLEN * sizeof(char));

    WSAStartup(MAKEWORD(2, 2), &Data);

	getIP (remoteHost, host_name, &ip);
	createSocket (&recvSockAddr, &recvSocket, ip);
    connect (recvSocket,(SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN));

    request(recvSocket, host_name);
    receive(buffer, &recvSocket);

    secretRequest(recvSocket,host_name,buffer);
    receive(buffer, &recvSocket);
    cnt = calcVowels(buffer);

    postRequest(recvSocket,host_name,cnt);
    receive(buffer, &recvSocket);

    free(buffer);

    closesocket(recvSocket);
    WSACleanup();

    return 0;
}
