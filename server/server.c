
/*
최초작성자 : 한도경

최초작성일 : 2019-05-24

최초변경일 : 2019-05-24

프로그램 목적 : 프로젝트

개정이력 :
(2019-05-24) 

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

                // memset(recvBuffer, 0, BUFSIZE+1);
                // read(s1.sock, recvBuffer, BUFSIZE);
                // printf("%d\n", recvBuffer[0]);
                // receive_packet(recvBuffer);

                // memset(recvBuffer, 0, BUFSIZE+1);
                // read(s1.sock, recvBuffer, BUFSIZE);
                // printf("%d\n", recvBuffer[0]);
                // receive_packet(recvBuffer);

                // memset(recvBuffer, 0, BUFSIZE+1);
		        // recvfrom(s1.sock, recvBuffer, BUFSIZE, 0 , (struct sockaddr*)&s1.clntAddr, &clntLen);
                // printf("%d\n", recvBuffer[0]);
                // receive_packet(recvBuffer);
            }
            close(client_fd);
            printf("Server : %s client closed.\n", temp);
        }
    }
    closeDB();
    printf("DB Closing.\n");

    // UDP
    // // 소켓 생성
    // if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))== -1){
    //     perror("socket failed");
    //     exit(1);
    // }

    // // servAddr를 0으로 초기화 
    // memset(&servAddr, 0, sizeof(servAddr));

    // // servAddr에 IP 주소와 포트 번호를 저장
    // servAddr.sin_family = AF_INET;
    // servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servAddr.sin_port = htons(PORT);

    // // sockfd 소켓에 주소 정보 연결
    // if(bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
    //    perror("bind failed");
    //    exit(1);
    // }

    // // 자식 프로세스에서 처리
    // pid = fork();
    
    // while(1) {
    //     if(pid == 0) {
    //         clntLen = sizeof(clntAddr);
    //         memset(recvBuffer, 0, BUFSIZE+1);

    //         /* sockfd 소켓으로 들어오는 데이터를 받아 recvBuffer에 저장하고
    //         클라이언트 주소 정보를 clntAddr에 저장 */
    //         if((recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE-1, 0, (struct sockaddr*)&clntAddr, &clntLen)) == -1) {
    //             perror("recvfrom failed");
    //             exit(1);
    //         }
    //         recvBuffer[recvLen] = '\0';
    //         s1.clntAddr = clntAddr;
    //         s1.sockfd = sockfd;

    //         // 패킷 처리
    //         receive_packet(recvBuffer);
    //     }
    // }
    // return 0;
}



