
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


int main(void){
    int sockfd;
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    char recvBuffer[BUFSIZE];
    int clntLen;
    int recvLen;
    pid_t pid;


    memset(&roomList, 0x00, sizeof(struct roomList));
    
    // 소켓 생성
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))== -1){
        perror("socket failed");
        exit(1);
    }

    // servAddr를 0으로 초기화 
    memset(&servAddr, 0, sizeof(servAddr));

    // servAddr에 IP 주소와 포트 번호를 저장
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(PORT);

    // sockfd 소켓에 주소 정보 연결
    if(bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
       perror("bind failed");
       exit(1);
    }

    pid = fork();

    // socket 연결 오면 프로세스 생성해서 연결
    while(1) {
        if(pid == 0) {
            clntLen = sizeof(clntAddr);
            memset(recvBuffer, 0, BUFSIZE+1);

            /* sockfd 소켓으로 들어오는 데이터를 받아 recvBuffer에 저장하고
            클라이언트 주소 정보를 clntAddr에 저장 */
            if((recvLen=recvfrom(sockfd, recvBuffer, BUFSIZE-1, 0, (struct sockaddr*)&clntAddr, &clntLen)) == -1) {
                perror("recvfrom failed");
                exit(1);
            }
            recvBuffer[recvLen] = '\0';

            s1.clntAddr = clntAddr;
            s1.sockfd = sockfd;
            
            // 요청 패킷 출력
            printf("Recevied: %d\n clntaddr: %d\n", recvBuffer[4], clntAddr.sin_addr.s_addr);

            // 패킷 처리
            receive_packet(recvBuffer);

            // 응답 패킷을 클라이언트에게 보냄
            // send_packet(sockfd, recvBuffer, clntAddr);
        }
    }

    
    return 0;
}