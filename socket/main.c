#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main()
{
    char buff[256] = {'\0'};
    char msgs[3][256];
    //Para windows
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,0), &wsa);

    struct sockaddr_in caddr;

    struct sockaddr_in saddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port = htons(5000)
    };

    int server = socket(AF_INET, SOCK_STREAM, 0);
    int client, x;

    int csize = sizeof caddr;

    bind(server, (struct sockaddr *)&saddr, sizeof saddr);

    listen(server, 5);
    int num_mensagem = 0;
    while(1){
        client = accept(server, (struct sockaddr *) &caddr, &csize);
        x = recv(client, buff, sizeof buff, 0);
        send(client, buff, x, 0);
        puts(buff);
        strcpy(msgs[num_mensagem++], buff);
        fflush(stdout);
        system("cls");
        int i=0;
        printf("Mensagens recebidas ate o momento: \n");
        for(i=0; i<num_mensagem; i++){
            printf("Mensagem %d => %s \n", i+1, msgs[i]);
        }
        if(num_mensagem==3){
            break;
        }
        //no windows não usa o close
        closesocket(client);
    }
    closesocket(server);
    return 0;
}
