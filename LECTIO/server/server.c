
/*
최초작성자 : 한도경

최초작성일 : 2019-05-24

최초변경일 : 2019-05-24

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-24) UDP로 작성
(2019-06-01) TCP로 바꿈

저작권 : 5조
*/

#include "header.h"
#define PORT 50000  // 포트번호
#define BUFSIZE 1024

int shmid;

int main(void){
    int sockfd;
    int server_fd, client_fd;
    int clntLen;
    int recvLen;
    char recvBuffer[BUFSIZE+1];
    char temp[20];
    struct sockaddr_in servAddr, clntAddr;
    pid_t pid;

    memset(&roomList, 0, sizeof(struct roomList));

    // 소켓 생성
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("server: can't open stream socket\n");
        exit(0);
    }

    // servAddr를 0으로 초기화 
    memset(&servAddr, 0, sizeof(servAddr));

    // servAddr에 IP 주소와 포트 번호를 저장
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);

    if (connectDB() < 0) {
      printf("DB Connect fail\n");
      return -1;
    }
    // bind
    if(bind(server_fd, (struct sockaddr *)&servAddr, sizeof(servAddr))<0){
        printf("Server : Can't bind local address.\n");
        exit(0);
    }

    // listen  
    if(listen(server_fd, 5) < 0){
        printf("Server : Can't listening connect.\n");
        exit(0);
    }

    while(1)
    {
        // clntAddr 길이
        clntLen = sizeof(clntAddr);

        // accept
        client_fd = accept(server_fd, (struct sockaddr *)&clntAddr, &clntLen);
        if(client_fd < 0){
            printf("Server: accept failed.\n");
            exit(0);
        }
        s1.sock = client_fd;
        s1.clntAddr = clntAddr;

        // fork
        pid = fork();
        if(pid == 0){
            inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, temp, sizeof(temp));
            printf("Server : %s client connected.\n", temp);
            while(1){
                memset(recvBuffer, 0, BUFSIZE+1);
                read(s1.sock, recvBuffer, BUFSIZE);
                receive_packet(recvBuffer);
            }
            close(client_fd);
            printf("Server : %s client closed.\n", temp);
        }
    }
    closeDB();
    printf("DB Closing.\n");
}



