#include "header.h"
#define BUFF_SIZE 1024

// 패킷 받으면 확인해서 타입별로 처리
void receive_packet(char *packet){

}

// data 앞에 type과 mode를 붙임
void create_packet(char type, char mode, char *data ,char *buf){
	strncat(buf, &type, 1); // type 붙여주고
	strncat(buf, &mode, 1); // mode 붙여주고
    strcat(buf, data); // data 붙여주고
}

void send_packet(int sockfd, char *buf, struct sockaddr_in clntAddr){
    if(!sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &clntAddr, sizeof(clntAddr))) {
        perror("sendto failed");
        exit(1);
    }
}